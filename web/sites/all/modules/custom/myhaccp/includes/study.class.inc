<?php

interface StudyInterface {

  public function getCurrentStudy();

  public function setCurrentStudy($iid);

  public function addPhase(Phase $phase);

  public function getPhase($phase);

  public function getPhases();

  public function getStage($name);

  public function getCurrentStage();

  public function setCurrentStage($stage);

  public function getValidationStatus();

  public function setValidationStatus($status);

  public function setStatus($status);

  public function getStatus();

  public function cloneStudy($iid);

  public function getCurrentStudyOwner();
}

class Study implements StudyInterface {

  protected $phases = array();

  /**
   * Tries to determine the IID from the URL.
   */
  public function getIIDFromURL() {
    $url = $_GET['q'];
    $parts = explode('/', $url);
    if (isset($parts[2]) && $parts[0] == 'tool' && $parts[1] == 'study' && is_numeric($parts[2])) {
      return $parts[2];
    }
    return FALSE;
  }

  /**
   * Returns the sessions's IID.
   *
   * @return int
   *   Returns the session iid or sends the user to their study overview page.
   */
  public function getCurrentStudy() {
    // Try to determine which study is active by looking at the $_SESSION.
    if (isset($_SESSION['iid'])) {
      return $_SESSION['iid'];
    }
    else {
      // There is no set IID so return the user to their studies overview page.
      drupal_goto('tool');
    }
  }

  /**
   * Sets the IID for the session.
   *
   * @param int $iid
   *   The study ID being used.
   */
  public function setCurrentStudy($iid) {
    $_SESSION['iid'] = $iid;
    $this->setIID($iid);
  }

  /**
   * Sets the IID of the study.
   *
   * @param int $iid
   */
  public function setIID($iid) {
    $this->iid = $iid;
  }

  /**
   * Gets the study's IID.
   *
   * @return int
   *   The IID of the study.
   */
  public function getIID() {
    if (isset($this->iid)) {
      return $this->iid;
    }
    if (isset($_SESSION['iid'])) {
      $this->setIID($_SESSION['iid']);
      return $this->getIID();
    }
  }

  /**
   * Gets the study name.
   *
   * Fetches it from the db if not set locally.
   *
   * @return string
   *   The name of the study.
   */
  public function getName() {
    if (!empty($this->name)) {
      return $this->name;
    }
    else {
      // Try to determine the name from the intro stage.
      $intro = $this->getStage('preparatory_intro');
      $data = $intro->getData();
      if ($data && !empty($data['preparatory_intro']['study_name'])) {
        $this->setName($data['preparatory_intro']['study_name']);
      }
      else {
        // There is no set name yet so give the study a temporary name.
        $this->setName('Unnamed study');
      }
      return $this->getName();
    }
  }

  /**
   * Sets the study name (only in the object, not in the db).
   *
   * @param string $name
   *   The study name.
   */
  public function setName($name) {
    $this->name = $name;
  }

  /**
   * Adds a phase to a study.
   *
   * @param Phase $phase
   *   The phase added.
   */
  public function addPhase(Phase $phase) {
    $this->phases[$phase->getName()] = $phase;
  }

  /**
   * Returns a phase object.
   *
   * @param string $phase
   *   The name of the phase.
   *
   * @return Phase|bool
   *   The phase object or FALSE if not found.
   */
  public function getPhase($phase) {
    if (isset($this->phases[$phase])) {
      return $this->phases[$phase];
    }
    return FALSE;
  }

  public function getPhases() {
    return $this->phases;
  }

  /**
   * Helper function to locate a stage, given a url.
   *
   * @param string $phase
   *   The phase part of the url.
   * @param string $url
   *   The stage part of the url.
   *
   * @throws Exception
   * @return Stage stage
   *   Returns the stage if found.
   */
  public function getStageFromUrl($phase, $url) {
    // Iterate through the stages of the given phase.
    foreach ($this->phases[$phase]->stages as $stage) {
      if ($stage->getUrl() == $phase . '/' . $url) {
        return $stage;
      }
    }
    return FALSE;
//    throw new Exception('Stage not found for url' . $phase . '/' . $url);
  }

  /**
   * Gets a specific stage.
   *
   * @param string $name
   *   The stage name to find the stage for.
   *
   * @throws Exception
   * @return Stage
   *   The stage if found.
   */
  public function getStage($name) {
    foreach ($this->getPhases() as $phase) {
      foreach ($phase->getStages() as $stage) {
        if ($stage->getName() == $name) {
          return $stage;
        }
      }
    }
    // If the stage wasn't found (doesn't exist) then throw an exception.
    throw new Exception(t('Stage %stage not found. This could mean the stage used to exist but no longer exists.', array('%stage', $name)));
  }

  /**
   * Gets the current stage.
   *
   * @throws exception
   * @return Stage
   *   The stage to be returned.
   */
  public function getCurrentStage() {
    // If we have the current stage then return it.
    if (isset($this->currentStage)) {
      return $this->currentStage;
    }

    // Try to figure out the stage from the url.
    $url = $_GET['q'];
    $parts = explode('/', $url);
    // Ensure this is a phase, not an ajax callback.
    if (isset($parts[3]) && isset($parts[4]) && $this->getPhase($parts[3])) {
      if ($stage = $this->getStageFromUrl($parts[3], $parts[4])) {
        // Set the stage for future checks.
        $this->setCurrentStage($stage);
        return $this->getCurrentStage();
      }
    }

    // Fallback is to get the current stage from the database.
    $data = db_select('mforms_storage', 'm');
    $data->join('mforms_storage_steps', 's', 's.iid = m.iid');
    $data->fields('s', array('store_data'))
      ->condition('m.iid', $this->getIID())
      ->condition('s.store_key', 'curr_step');
    $result = $data->execute()->fetchField();
    if ($result) {
      $stage_name = unserialize($result);
      if ($stage = $this->getStage($stage_name)) {
        // Set the stage for future checks.
        $this->setCurrentStage($stage);
        return $this->getCurrentStage();
      }
    }

    // Final fallback is the preparatory intro stage.
    if ($stage = $this->getStage('preparatory_intro')) {
      $this->setCurrentStage($stage);
      return $this->getCurrentStage();
    }

    // If we weren't able to get the current stage then throw
    // an exception.
    throw new Exception('Unable to get the current stage.');
  }

  /**
   * Sets the current stage the user is on.
   *
   * @param Stage $stage
   *   The stage to set.
   *
   * @see MformsDatabaseStore::getStore()
   */
  public function setCurrentStage($stage) {
    $this->currentStage = $stage;
  }

  /**
   * Gets the completion status of the study.
   */
  public function getValidationStatus() {
    if (isset($this->validationStatus)) {
      return $this->validationStatus;
    }
    else {
      // Iterate through each stage.
      foreach ($this->getPhases() as $phase) {
        foreach ($phase->getStages() as $stage) {
          $results[$stage->getName()] = $stage->getStatus();
        }
      }
      // Remove the intro and review stages.
      $remove = array(
        'preparatory_intro',
        'preparatory_review',
        'principle_intro',
        'principle_review',
      );
      foreach ($remove as $key) {
        unset($results[$key]);
      }
      // Check for any invalid results.
      if (in_array(INVALID, $results)) {
        $this->setValidationStatus(INVALID);
        return $this->getValidationStatus();
      }
      // Check all the results are valid.
      if (count(array_keys($results, VALID)) == count($results)) {
        $this->setValidationStatus(VALID);
        return $this->getValidationStatus();
      }
      // Fall back to not started.
      $this->setValidationStatus(NOT_STARTED);
      return $this->getValidationStatus();
    }
  }

  /**
   * Sets the completion status of the study.
   *
   * @param int $status
   * @throws exception
   */
  public function setValidationStatus($status) {
    if (!is_int($status)) {
      throw new exception('Only integer values allowed.');
    }
    $this->validationStatus = $status;
  }

  /**
   * Sets the status of the study in the database.
   *
   * @param int $status
   *   The integer to store, 0 for incomplete, 1 for complete.
   * @throws exception
   */
  public function setStatus($status) {
    if (!is_int($status)) {
      throw new exception('The status must be an integer.');
    }
    db_update('mforms_storage')
      ->fields(array('status' => $status))
      ->condition('iid', $this->getIID())
      ->execute();
  }

  /**
   * Gets the current status of the study from the database.
   *
   * @return int
   *   The status integer (0 for incomplete, 1 for complete).
   */
  public function getStatus() {
    // Attempt to load the status from the database.
    $query = db_select('mforms_storage', 'm')
      ->fields('m', array('status'))
      ->condition('m.iid', $this->getIID());
    $status = $query->execute()->fetchField();
    return $status;
  }

  /**
   * Clones a study.
   */
  public function cloneStudy($iid) {
    $record = $this->createStudy($iid);
    $new_iid = $record['iid'];
    $this->cloneMformsStorageSteps($iid, $new_iid);
    return $new_iid;
  }

  /**
   * Creates a new study.
   *
   * @param int $iid
   *   The unique IID of the study.
   */
  public function createStudy($iid) {
    $user = $this->getStudyOwner($iid);
    $record = array(
      'uid' => $user->uid,
      'created' => time(),
    );
    // Write the new record.
    drupal_write_record('mforms_storage', $record);
    // Return the record.
    return $record;
  }

  /**
   * Copies all the rows related to the iid into new rows referencing new_iid.
   *
   * @param $iid
   *   The IID of the study steps to be cloned.
   * @param $new_iid
   *   The IID of the new study being cloned into.
   */
  protected function cloneMformsStorageSteps($iid, $new_iid) {
    // Fetch all the steps of the current IID.
    $steps = db_select('mforms_storage_steps', 's')
      ->fields('s', array('store_key', 'store_data'))
      ->condition('s.iid', $iid)
      ->execute()->fetchAllKeyed();
    // Iterate over each step.
    foreach($steps as $store_key => $store_data) {
      $record = array(
        'iid' => $new_iid,
        'store_key' => $store_key,
        'store_data' => $store_data,
      );
      // Store the step data against the new_iid.
      drupal_write_record('mforms_storage_steps', $record);
    }
  }

  /**
   * Returns the user object of the owner of this study.
   *
   * @return object
   *   The user object representing the study owner.
   */
  public function getCurrentStudyOwner() {
    $iid = $this->getIID();
    return $this->getStudyOwner($iid);
  }

  /**
   * Returns the user object of the owner of the given study.
   *
   * @param int $iid
   *   The IID of the study of which the owner is to be fetched.
   *
   * @return object
   *   The user object representing the study owner.
   */
  public function getStudyOwner($iid) {
    $uid = db_select('mforms_storage', 'ms')
      ->fields('ms', array('uid'))
      ->condition('ms.iid', $iid)
      ->execute()
      ->fetchField();
    return user_load($uid);
  }
}
