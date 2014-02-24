<?php
/**
 * @file
 * Validation handler class.
 */

/**
 * Class validateStages
 *
 * Used to check the status of validation for all stages.
 */
class ValidateStages {

  public $stages;
  protected $iid;

  /**
   * Constructor method.
   */
  public function __construct() {
    // Get all the stages for later use.
    $this->stages = new Stages();
    // Get the IID from the session.
    $this->iid = $_SESSION['iid'];
  }

  /**
   * Gets the data for a specific stage from the database.
   *
   * @param Stage $stage
   *   The stage to query for data.
   *
   * @return array
   *   The stage data from the database or empty array if not found.
   */
  protected function getStageData(Stage $stage) {
    $data = array();
    // Get the stage from the db.
    $query = db_select('mforms_storage_steps', 'mss')
      ->fields('mss', array('store_data'))
      ->condition('mss.store_key', $stage->name)
      ->condition('mss.iid', $this->iid);
    $result = $query->execute()->fetchField(0);
    if ($result) {
      // Unpack the data into an array keyed by the stage name.
      $data = unserialize($result);
    }
    return $data;
  }

  /**
   * Returns the form_state data stored in the database for all the stages.
   *
   * @param string $type
   *   If a type is provided it will return that type's data only.
   *
   * @return array
   *   An array keyed by stage name of form_state data.
   */
  protected function getAllStageData($type = 'all') {
    $data = array();
    foreach ($this->stages->allStages as $key => $stage_type) {
      if ($type !== 'all' && $stage_type == $type) {
        $data[$key] = getStageData($key);
      }
    }
    return $data;
  }

  /**
   * Gets the validation messages for a specific stage.
   *
   * @param string $stage
   *   The stage to get the validation messages for.
   *
   * @return array
   *   An array of validation messages or an empty array if none found.
   */
  public function getStageMessages($stage) {
    $messages = array();
    $data = $this->getStageData($stage);
    if (!empty($data)) {
      if (isset($data['validate'])) {
        $messages = $data['validate'][$stage->name];
      }
    }
    return $messages;
  }

  /**
   * Gets all the validation messages for all the stages.
   */
  public function getAllStagesMessages() {

  }

  /**
   * Gets the preparatory stages messages.
   *
   * @return array
   *   An array of stages with sub arrays of the messages.
   */
  public function getPreparatoryStagesMessages() {
    $messages = array();
    foreach ($this->stages->allStages as $stage => $type) {
      if ($type == 'preparatory') {
        // Get the messages for this stage.
        $stage_messages = $this->getStageMessages($stage);
        $messages[$stage] = $stage_messages;
      }
    }
    return $messages;
  }

  public function getPrincipleStagesMessages() {

  }

  /**
   * Gets the preparatory stages validation statuses.
   *
   * @return array
   *   An array of stages with boolean values showing pass or fail.
   */
  public function getPreparatoryStagesStatuses() {
    $statuses = array();
    foreach ($this->stages->allStages as $stage) {
      if ($stage->type == 'preparatory') {
        // Get the messages for this stage.
        $statuses[$stage->name] = $this->stageHasPassed($stage);
      }
    }
    return $statuses;
  }

  /**
   * Gets the principle stages validation statuses.
   *
   * @return array
   *   An array of stages and whether they are 'OK' or 'Needs review'.
   */
  public function getPrincipleStagesStatuses() {
    $statuses = array();
    foreach ($this->stages->allStages as $stage) {
      if ($stage->type == 'principle') {
        // Get the messages for this stage.
        $statuses[$stage->name] = $this->stageHasPassed($stage);
      }
    }
    return $statuses;
  }

  /**
   * Gets the validation status of a stage, a pass or fail.
   */
  public function stageHasPassed($stage) {
    // Assume the stage has failed.
    $passed = FALSE;
    $messages = $this->getStageMessages($stage);
    if (empty($messages)) {
      $passed = TRUE;
    }
    return $passed;
  }

}
