<?php
/**
 * @file
 * CCP and hazard information class.
 */

/**
 * Class hazards.
 *
 * Gets current CCPs and hazards and provides methods of querying their status.
 */
class Hazards {

  private static $instances = array();
  public $steps;
  public $hazards = array();
  public $threshold;

  /**
   * Constructor method.
   */
  public function __construct() {
    // Ensure the mforms object exists. This is needed for output of stages.
    $this->getAllHazards();
    $this->populateSignificance();
    $this->populateControlMeasure();
    $this->populateCCPs();
    $this->addCCPnumbers();
    $this->threshold = $this->getThreshold();
  }

  /**
   * Init hazards object and get its singleton.
   *
   * @param int $iid
   *   The unique id of the form instance.
   *
   * @return Hazards
   *   Singleton object.
   */
  public static function getInstance($iid = NULL) {
    if (is_null($iid)) {
      $iid = $_SESSION['iid'];
    }
    // If singleton instance is NULL, instantiate the Hazard.
    if (empty(self::$instances[$iid])) {
      myhaccp_myhaccp_mforms_init();
      $class = get_called_class();
      self::$instances[$iid] = new $class();
    }

    // Return instantiated and set Hazard object.
    return self::$instances[$iid];
  }

  /**
   * Gets the threshold over which hazards can become ccps.
   *
   * @return int
   *   A threshold integer or 0 if it hasn't yet been set.
   */
  protected function getThreshold() {
    $data = mforms_get_vals('myhaccp', 'principle_1_2');
    $threshold = array_get($data, 'principle_1_2.threshold', 0);
    if (empty($threshold)) {
      // If no threshold has been set then return a higher number so that no
      // CCPs can be returned later in the stages.
      return 10;
    }
    return $threshold;
  }

  /**
   * Gets and populates the hazards element of the object.
   */
  protected function getAllHazards() {
    $data = mforms_get_vals('myhaccp', 'principle_1_1');
    if (!$data) {
      return;
    }
    // Don't need the add more buttons.
    unset($data['principle_1_1']['controls']);
    // Iterate over each step. Each step can contain multiple hazards.
    foreach ($data['principle_1_1'] as $instance) {
      $step_key = drupal_html_id($instance['wrapper']['step_name']);
      $step_name = $instance['wrapper']['step_name'];
      $step_no = $instance['wrapper']['step_no'];
      $step_hazards = $this->getHazardsFromCategories($instance['hazards_wrapper']);
      // Create a new hazard object for each one in step_hazards.
      foreach ($step_hazards as $hazard_key => $hazard_name) {
        $hazard = new Hazard($hazard_key);
        $hazard->name = $hazard_name;
        $hazard->key = $hazard_key;
        $hazard->step->name = $step_name;
        $hazard->step->no = $step_no;
        $hazard->step->key = $step_key;
        $this->hazards[$hazard_key] = $hazard;
      }
    }
  }

  /**
   * Populates the hazards objects with significance and description data.
   */
  protected function populateSignificance() {
    $data = mforms_get_vals('myhaccp', 'principle_1_2');
    if (!$data) {
      return;
    }
    // Get all the steps and match them up with our hazard data.
    foreach ($this->getHazardsByStep() as $step_key => $step) {
      // Each hazard in the step table.
      if (isset($data['principle_1_2'][$step_key])) {
        foreach ($data['principle_1_2'][$step_key]['instance_table'] as $hazard_key => $hazard_data) {
          // Check it exists.
          if (isset($this->hazards[$hazard_key])) {
            // Add the description.
            $this->hazards[$hazard_key]->description = $hazard_data['description'];
            // Add the significance.
            $this->hazards[$hazard_key]->significance = !empty($hazard_data['significance']) ? $hazard_data['significance'] : 0;
          }
        }
      }
    }
  }

  /**
   * Populates the hazards objects with significance and description data.
   */
  protected function populateControlMeasure() {
    $data = mforms_get_vals('myhaccp', 'principle_1_3');
    if (!$data) {
      return;
    }
    // Match up the data with the hazards and populate the control measures.
    foreach ($data['principle_1_3']['instance_table'] as $hazard_key => $measure) {
      if (isset($this->hazards[$hazard_key])) {
        $this->hazards[$hazard_key]->controlMeasure = $measure['control_measure'];
      }
    }
  }

  /**
   * Returns an array of hazards keyed by the step they belong to.
   */
  public function getHazardsByStep() {
    $steps = array();
    // Prepare the hazards by step.
    foreach ($this->hazards as $hazard_key => $hazard) {
      $steps[$hazard->step->key]['hazards'][$hazard_key] = $hazard;
      $steps[$hazard->step->key]['name'] = $hazard->step->name;
      $steps[$hazard->step->key]['no'] = $hazard->step->no;
    }
    return $steps;
  }

  /**
   * Extracts all hazards from their categories and returns an array.
   *
   * @param array $categories
   *   The containing array with the categories in it.
   *
   * @return array
   *   All the hazards as an array of key value pairs.
   */
  protected function getHazardsFromCategories($categories) {
    // Process the hazards within each category.
    $hazards = array();
    // Iterate over the categories.
    foreach ($categories as $category) {
      if (!empty($category)) {
        // Split the hazard items listed in the category text area into an
        // array, one item per line in the text area.
        $hazard_items = explode("\r\n", trim($category));
        // Iterate over each hazard item in this category.
        foreach ($hazard_items as $item) {
          // If the item isn't empty add the hazard.
          if ($item != '') {
            // Create a unique id for this item.
            $key = drupal_html_id($item);
            $hazards[$key] = $item;
          }
        }
      }
    }
    return $hazards;
  }

  /**
   * Checks to make sure hazard data exists.
   *
   * This is used by principle steps to check that previous steps have been filled
   * in correctly, or at least enough to progress to a stage in the form.
   *
   * @return int
   *   Return an instance count.
   */
  public function countHazards() {
    return count($this->hazards);
  }

  /**
   * Gets all hazards over the specified threshold in principle 1 question 2.
   *
   * @return array
   *   An array of each hazard.
   */
  public function getHazardsOverTheshold() {
    $hazards = array();
    foreach ($this->hazards as $hazard) {
      if ($hazard->significance >= $this->threshold) {
        $hazards[$hazard->key] = $hazard;
      }
    }
    return $hazards;
  }

  /**
   * Ensure there are hazards over the set threshold in principle 1 question 2.
   *
   * @return int
   *   The count of hazards over the threshold.
   */
  public function countHazardsOverThreshold() {
    return count($this->getHazardsOverTheshold());
  }

  /**
   * Gets all hazards which are a CCP.
   *
   * @return array
   *   Returns all CCP items.
   */
  public function populateCCPs() {
    $data = mforms_get_vals('myhaccp', 'principle_2_2');
    $rows = array_get($data, 'principle_2_2.instance_table', array());
    // Iterate through the data and populate the CCPs.
    foreach ($rows as $hazard_key => $item) {
      if (is_array($item)) {
        // Determine the critical control point.
        if (!empty($item['ccp'])) {
          if (isset($this->hazards[$hazard_key])) {
            $this->hazards[$hazard_key]->ccp = $item['ccp'] == 'yes' ? TRUE : FALSE;
          }
        }
      }
    }
  }

  /**
   * Gets all hazards marked as a CCP.
   *
   * @return array
   *   An array of CCPs.
   */
  public function getCCPs() {
    $items = array();
    foreach ($this->hazards as $hazard) {
      if ($hazard->ccp) {
        $items[$hazard->key] = $hazard;
      }
    }
    return $items;
  }

  /**
   * Returns the CCP count.
   *
   * @return int
   *   The count of ccp items found.
   */
  public function CCPsExist() {
    $items = $this->getCCPs();
    return count($items);
  }

  /**
   * Add a CCP number for each hazard which is a CCP.
   */
  protected function addCCPnumbers() {
    $count = 1;
    foreach ($this->hazards as $hazard) {
      if ($hazard->ccp) {
        $hazard->ccpNo = $count;
        $count++;
      }
    }
  }

}

class Hazard {

  public $name;
  public $description;
  public $controlMeasure;
  public $key;
  public $significance = 0;
  public $ccpNo = 0;
  public $ccp = FALSE;

  /**
   * Constructor method.
   */
  public function __construct() {
    $this->step = new Step();
  }

  public function getHeader() {
    $ccp_number_text = '<div class="ccp-number"><span class="label">' . t('Critical Control Point (CCP) Number') . ':</span> ' . $this->ccpNo . '</div>';
    // Prepare the text.
    $process_step_text = '<div class="process-step"><span class="label">' . t('Process Step') . ':</span> ' . '(' . $this->step->no . ') ' . $this->step->name . '</div>';
    // The hazard text.
    $hazard_text = '<div class="hazard"><span class="label">' . t('Hazard') . ':</span> ' . $this->name . '<div class="hazard-description">' . nl2br($this->description) . '</div></div>';
    $control_text = '<div class="control-measure"><span class="label">' . t('Control Measure') . ':</span> ' . nl2br($this->controlMeasure) . '</div>';

    // Prepare the form segments to return.
    $form['header'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'header',
        ),
      ),
    );

    $form['header']['process_step'] = array(
      '#markup' => $process_step_text,
    );

    $form['header']['hazard'] = array(
      '#markup' => $hazard_text,
    );

    $form['header']['control_measure'] = array(
      '#markup' => $control_text,
    );

    $form['header']['ccp'] = array(
      '#markup' => $ccp_number_text,
    );

    return $form;
  }

}

class Step {

  public $key;
  public $name;
  public $number;

}
