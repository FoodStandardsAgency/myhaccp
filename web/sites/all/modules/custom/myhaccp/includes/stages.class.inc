<?php
/**
 * @file
 * Stages class to make getting stage information easier.
 */

/**
 * Class stages
 */
class Stages {

  public $allStages = array();

  /**
   * Constructor method.
   */
  public function __construct() {
    // Populate the stage information.
    $stages = $this->getAll();
    foreach ($stages as $stage => $type) {
      $this->allStages[$stage] = new Stage($stage, $type);
      $this->allStages[$stage]->url = $this->getUrl($stage);
      $this->allStages[$stage]->title = $this->getTitle($stage);
    }
  }

  /**
   * Returns a stage object.
   *
   * @param string $stage
   *   The key name of the stage.
   *
   * @return bool|object
   *   The stage object or FALSE if not found.
   */
  public function getStage($stage) {
    return isset($this->allStages[$stage]) ? $this->allStages[$stage] : FALSE;
  }

  /**
   * Returns an array of stage objects which are preparatory stages.
   *
   * @return array
   *   Array of stage objects.
   */
  public function getPreparatories() {
    $stages = array();
    foreach ($this->allStages as $stage) {
      if ($stage->type == 'preparatory') {
        $stages[$stage->name] = $stage;
      }
    }
    return $stages;
  }

  /**
   * Returns an array of stage objects which are principle stages.
   *
   * @return array
   *   Array of stage objects.
   */
  public function getPrinciples() {
    $stages = array();
    foreach ($this->allStages as $stage) {
      if ($stage->type == 'principle') {
        $stages[$stage->name] = $stage;
      }
    }
    return $stages;
  }

  /**
   * Given a stage key (function name) returns the stage type.
   *
   * @param string $stage
   *   The stage key or function name.
   *
   * @return bool|string
   *   Returns the stage type, principle or preparatory, or FALSE if not found.
   */
  public function getStageType($stage) {
    return isset($this->allStages[$stage]) ? $this->allStages[$stage]->type : FALSE;
  }

  /**
   * Returns an array of key value pairs with the key the stage name.
   *
   * @return array
   *   Array keyed by the stage name and the value being the stage type.
   */
  public function getAll() {
    $stages = array(
      'preparatory_a' => 'preparatory',
      'preparatory_b' => 'preparatory',
      'preparatory_c_1' => 'preparatory',
      'preparatory_c_2' => 'preparatory',
      'preparatory_d' => 'preparatory',
      'preparatory_e' => 'preparatory',
      'preparatory_f' => 'preparatory',
      'preparatory_g' => 'preparatory',
      'preparatory_h' => 'preparatory',
      'preparatory_summary' => 'preparatory',
      'principle_1_1' => 'principle',
      'principle_1_2' => 'principle',
      'principle_1_3' => 'principle',
      'principle_2_1' => 'principle',
      'principle_2_2' => 'principle',
      'principle_3' => 'principle',
      'principle_4' => 'principle',
      'principle_5' => 'principle',
      'principle_6' => 'principle',
      'principle_7' => 'principle',
    );
    return $stages;
  }

  public function getUrl($stage) {
    $stage = $this->allStages[$stage];
    $all = $this->getUrls();
    $type = $stage->type;
    if ($all[$stage->name]) {
      return $type . '/' . $all[$stage->name];
    }
  }

  public function getTitle($stage) {
    $stage = $this->allStages[$stage];
    $all = $this->getAllTitles();
    if ($all[$stage->name]) {
      return $all[$stage->name];
    }
  }

  public function getUrls() {
    return array(
      'preparatory_a' => 'stage-a',
      'preparatory_b' => 'stage-b',
      'preparatory_c_1' => 'stage-c-1',
      'preparatory_c_2' => 'stage-c-2',
      'preparatory_d' => 'stage-d',
      'preparatory_e' => 'stage-e',
      'preparatory_f' => 'stage-f',
      'preparatory_g' => 'stage-g',
      'preparatory_h' => 'stage-h',
      'preparatory_summary' => 'preparatory-summary',
      'principle_1_1' => 'stage-1-1',
      'principle_1_2' => 'stage-1-2',
      'principle_1_3' => 'stage-1-3',
      'principle_2_1' => 'stage-2-1',
      'principle_2_2' => 'stage-2-2',
      'principle_3' => 'stage-3',
      'principle_4' => 'stage-4',
      'principle_5' => 'stage-5',
      'principle_6' => 'stage-6',
      'principle_7' => 'stage-7',
    );
  }

  protected function getAllTitles() {
    return array(
      'preparatory_a' => 'Preparatory Stage A: Prerequisites',
      'preparatory_b' => 'Preparatory Stage B: Management Commitment',
      'preparatory_c_1' => 'Preparatory Stage C: Define scope of the study, <br/>Questions 1-3',
      'preparatory_c_2' => 'Preparatory Stage C: Define scope of the study, <br/>Question 4',
      'preparatory_d' => 'Preparatory Stage D: Select the team',
      'preparatory_e' => 'Preparatory Stage E: Describe the product',
      'preparatory_f' => 'Preparatory Stage F: Identify intended use of the product',
      'preparatory_g' => 'Preparatory Stage G: Construct a flow diagram',
      'preparatory_h' => 'Preparatory Stage H: On-site confirmation of flow diagram',
      'preparatory_summary' => 'Preparatory Summary',
      'principle_1_1' => 'Principle 1, Question 1: Identify and list potential hazards.',
      'principle_1_2' => 'Principle 1, Question 2: Conduct a hazard analysis.',
      'principle_1_3' => 'Principle 1, Question 3: Specify control measures.',
      'principle_2_1' => 'Principle 2, Questions 1-3: Determine Critical Control Points (CCPs)',
      'principle_2_2' => 'Principle 2, Question 4: Specify control measures.',
      'principle_3' => 'Principle 3: Establish Critical Limits',
      'principle_4' => 'Principle 4: Establish a monitoring system for each CCP',
      'principle_5' => 'Principle 5: Establish a corrective action plan',
      'principle_6' => 'Principle 6: Verification',
      'principle_7' => 'Principle 7: Establish documentation and record keeping',
    );
  }

  public function getNameFromUrl($url) {
    $all = $this->getUrls();
    $all = array_flip($all);
    return isset($all[$url]) ? $all[$url] : FALSE;
  }

  /**
   * Fetches the current stage for a given IID.
   *
   * @param int $iid
   *   The unique ID of the study.
   *
   * @return string
   *   The current stage.
   */
  public function getCurrentStage($iid) {
    $data = db_select('mforms_storage', 'm');
    $data->join('mforms_storage_steps', 's', 's.iid = m.iid');
    $data->fields('s', array('store_data'))
      ->condition('m.iid', $iid)
      ->condition('s.store_key', 'curr_step');
    $result = $data->execute()->fetchField();
    if ($result) {
      $data = unserialize($result);
      return $data;
    }
    return '';
  }

}

class Stage {

  public $type;
  public $name;
  public $url;

  /**
   * Constructor method.
   */
  public function __construct($stage, $type) {
    // Populate the stage information.
    $this->type = $type;
    $this->name = $stage;
  }

}
