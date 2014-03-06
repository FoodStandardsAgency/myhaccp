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

}

class Study implements StudyInterface {

  protected $phases = array();

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
    $store = MformsDatabaseStore::getInstance('myhaccp');
    $stage_name = $store->getStore('curr_step');
    if ($stage = $this->getStage($stage_name)) {
      // Set the stage for future checks.
      $this->setCurrentStage($stage);
      return $this->getCurrentStage();
    }
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

}
