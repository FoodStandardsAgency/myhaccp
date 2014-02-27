<?php

interface StudyInterface {

  public function getCurrentStudy();

  public function setCurrentStudy($iid);

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
   * @return Phase
   *   The phase object.
   */
  public function getPhase($phase) {
    return $this->phases[$phase];
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
    throw new Exception('Stage not found for url' . $phase . '/' . $url);
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
    throw new Exception('Stage not found for requested ' . $name);
  }

  /**
   * Gets the current stage.
   *
   * @throws exception
   * @return Stage
   *   The stage to be returned.
   */
  public function getCurrentStage() {
    if (isset($this->currentStage)) {
      return $this->currentStage;
    }
    // Try to figure out the stage from the url.
    $url = $_GET['q'];
    $parts = explode('/', $url);
    if (isset($parts[3]) && isset($parts[4])) {
      if ($stage = $this->getStageFromUrl($parts[3], $parts[4])) {
        // Set the stage for future checks.
        $this->setCurrentStage($stage);
        return $stage;
      }
    }
    else if (!isset($parts[3])) {
      // Reset the stage to preparatory_a as this may occur when creating a
      // new study and the url hasn't been set yet.
      $stage = $this->getStage('preparatory_a');
      $this->setCurrentStage($stage);
      return $stage;
    }
    throw new exception('No current stage was found in the study object.');
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
