<?php
/**
 * @file
 * Stages class to make getting stage information easier.
 */

define('NOT_STARTED', 0);
define('INVALID', 1);
define('VALID', 2);

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
    $stages = $this->removeIntroReview($stages);
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
    $stages = $this->removeIntroReview($stages);
    return $stages;
  }

  /**
   * Removes intro and review stages from an array of stages.
   *
   * @param array $stages
   *   The stages to iterate over.
   * @return array
   *   The array without intro or review.
   */
  protected function removeIntroReview($stages) {
    foreach ($stages as $key => $stage) {
      if (strpos($stage->name, 'review') || strpos($stage->name, 'intro')) {
        unset($stages[$key]);
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
      'preparatory_intro' => 'preparatory',
      'preparatory_a' => 'preparatory',
      'preparatory_b' => 'preparatory',
      'preparatory_c_1' => 'preparatory',
      'preparatory_c_2' => 'preparatory',
      'preparatory_d' => 'preparatory',
      'preparatory_e' => 'preparatory',
      'preparatory_f' => 'preparatory',
      'preparatory_g' => 'preparatory',
      'preparatory_h' => 'preparatory',
      'preparatory_review' => 'preparatory',
      'principle_intro' => 'principle',
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
      'principle_review' => 'principle',
    );
    return $stages;
  }

  /**
   * Given a stage machine name returns it's URL.
   *
   * @param string $stage
   *   The stage machine name.
   *
   * @return string
   *   The url, made of two segments, the type and the stage.
   */
  public function getUrl($stage) {
    $stage = $this->allStages[$stage];
    $all = $this->getUrls();
    if ($all[$stage->name]) {
      return $all[$stage->name];
    }
  }

  /**
   * Gets the title of a stage.
   *
   * @param string $stage
   *   The stage machine name.
   *
   * @return string
   *   The title if found.
   */
  public function getTitle($stage) {
    $stage = $this->allStages[$stage];
    $all = $this->getAllTitles();
    if ($all[$stage->name]) {
      return $all[$stage->name];
    }
  }

  /**
   * An array of key names matching a value of urls.
   *
   * @return array
   *   The key is the function/machine name of a stage and the value is the
   *   url for that stage.
   */
  public function getUrls() {
    return array(
      'preparatory_intro' => 'preparatory/introduction',
      'preparatory_a' => 'preparatory/a',
      'preparatory_b' => 'preparatory/b',
      'preparatory_c_1' => 'preparatory/c-1',
      'preparatory_c_2' => 'preparatory/c-2',
      'preparatory_d' => 'preparatory/d',
      'preparatory_e' => 'preparatory/e',
      'preparatory_f' => 'preparatory/f',
      'preparatory_g' => 'preparatory/g',
      'preparatory_h' => 'preparatory/h',
      'preparatory_review' => 'preparatory/review',
      'principle_intro' => 'principle/introduction',
      'principle_1_1' => 'principle/1-1',
      'principle_1_2' => 'principle/1-2',
      'principle_1_3' => 'principle/1-3',
      'principle_2_1' => 'principle/2-1',
      'principle_2_2' => 'principle/2-2',
      'principle_3' => 'principle/3',
      'principle_4' => 'principle/4',
      'principle_5' => 'principle/5',
      'principle_6' => 'principle/6',
      'principle_7' => 'principle/7',
      'principle_review' => 'principle/review',
    );
  }

  /**
   * Returns an array of function/machine names matching to stage titles.
   *
   * @return array
   *   The key is the function/machine name and the value is the stage title.
   */
  protected function getAllTitles() {
    return array(
      'preparatory_intro' => 'Preparatory: Intro',
      'preparatory_a' => 'Preparatory Stage A: Prerequisites',
      'preparatory_b' => 'Preparatory Stage B: Management Commitment',
      'preparatory_c_1' => 'Preparatory Stage C: Define scope of the study, <br/>Questions 1-3',
      'preparatory_c_2' => 'Preparatory Stage C: Define scope of the study, <br/>Question 4',
      'preparatory_d' => 'Preparatory Stage D: Select the team',
      'preparatory_e' => 'Preparatory Stage E: Describe the product',
      'preparatory_f' => 'Preparatory Stage F: Identify intended use of the product',
      'preparatory_g' => 'Preparatory Stage G: Construct a flow diagram',
      'preparatory_h' => 'Preparatory Stage H: On-site confirmation of flow diagram',
      'preparatory_review' => 'Preparatory: Review',
      'principle_intro' => 'Principles: Intro',
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
      'principle_review' => 'Principles: Review',
    );
  }

  /**
   * Helper method which gets the machine name of a stage given the url.
   *
   * @param string $type
   *   The first part of the url, the stage type.
   * @param string $url
   *   The stage url to match.
   *
   * @return string|bool
   *   The machine name of the stage or FALSE if no match.
   */
  public function getNameFromUrl($type, $url) {
    $all = $this->getUrls();
    $all = array_flip($all);
    return isset($all[$type . '/' . $url]) ? $all[$type . '/' . $url] : FALSE;
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

//class Stage {
//
//  public $type;
//  public $name;
//  public $url;
//
//  /**
//   * Constructor method.
//   */
//  public function __construct($stage, $type) {
//    // Populate the stage information.
//    $this->type = $type;
//    $this->name = $stage;
//    $this->validation = $this->getValidationData();
//    $this->status = $this->getStatus();
//  }
//
//  public function getStatus() {
//    // Check if there is any validation stored.
//    if (is_array($this->validation)) {
//      // If the array is empty it means validation has passed.
//      if (empty($this->validation)) {
//        return VALID;
//      }
//      else {
//        return INVALID;
//      }
//    }
//    // There is no validation which means the stage hasn't been started.
//    return NOT_STARTED;
//  }
//
//  public function getValidationData() {
//    $data = FALSE;
//    $iid = $_SESSION['iid'];
//    $key = $this->name . '_validation';
//    $query = db_select('mforms_storage', 'm');
//    $query->join('mforms_storage_steps', 's', 's.iid = m.iid');
//    $query->fields('s', array('store_data'))
//      ->condition('m.iid', $iid)
//      ->condition('s.store_key', $key);
//    $result = $query->execute()->fetchField();
//    if ($result) {
//      $data = unserialize($result);
//    }
//    return $data;
//  }
//
//}
