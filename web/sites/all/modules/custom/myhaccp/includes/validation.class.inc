<?php
/**
 * @file
 * Validation handler class.
 */

/**
 * Class validator
 *
 * A stage validation used to validate multiple elements and set or clear
 * messages.
 */
class Validator {

  private static $instances = array();
  public $results = array();
  public $passed = TRUE;

  /**
   * Constructor method.
   */
  public function __construct($stage = NULL) {
    $this->stage = $this->getCurrentStage($stage);
    $store = MformsDatabaseStore::getInstance('myhaccp');
    $steps = MformsSteps::getInstance($store);
    $controls = mforms_controls_get('myhaccp');
    // Get instance of Mform.
    $this->state = $store->getFormState();
    $mform = Mform::getInstance($store, $steps, $controls, $this->stage);
    // Get the form definition for the provided step.
    $this->form = $mform->call('build', array(), $this->state, array());
  }

  /**
   * Init validator object and get its singleton.
   *
   * @param int $iid
   *   The unique id of the form instance.
   *
   * @return Validator
   *   Singleton object.
   */
  public static function getInstance($iid = NULL) {
    if (is_null($iid)) {
      $iid = $_SESSION['iid'];
    }
    // If singleton instance is NULL, instantiate the Validator.
    if (empty(self::$instances[$iid])) {
      myhaccp_myhaccp_mforms_init();
      $class = get_called_class();
      self::$instances[$iid] = new $class();
    }

    // Return instantiated and set Validator object.
    return self::$instances[$iid];
  }

  /**
   * Sets the form state within the validator.
   *
   * @param array $form_state
   *   The form state array.
   */
  public function setFormState($form_state) {
    $this->state = $form_state;
  }

  /**
   * Returns the current stage.
   *
   * @param string $stage
   *   The stage if specified.
   *
   * @return string
   *   The current stage from the curr_step stored or the passed in stage.
   */
  private function getCurrentStage($stage) {
    if (empty($stage)) {
      $store = MformsDatabaseStore::getInstance('myhaccp');
      $stage = $store->getStore('curr_step');
    }
    return $stage;
  }

  /**
   * Gets the validation from the db for the current stage.
   */
  public function getValidation() {
    $data = mforms_get_vals('myhaccp', $this->stage . '_validation');
    if (empty($data)) {
      return NULL;
    }
    return $data;
  }

  /**
   * Sets the validation up in form_state.
   *
   * @param array $form_state
   *   The form state to modify.
   */
  public function setFormStateValidation(&$form_state) {
    // Only do this for the myhaccp forms.
    if (is_array($form_state) && $form_state['build_info']['form_id'] == 'myhaccp_study_resume') {
      $form_state['values']['validate'] = $this->getValidation();
    }
  }

  /**
   * Validates a single element.
   *
   * Creates a new instance of a validation object and passes in the method
   * and target. It stores the result for later use.
   *
   * @param string|array $methods
   *   The method to be used. Must exist in validation class. If a string will
   *   be converted to an array for iteration.
   *
   * @param string $target
   *   The element array target in dot notation.
   *
   * @return bool
   *   A pass or fail boolean.
   */
  public function validate($methods, $target) {
    // Convert a string method to an array.
    if (!is_array($methods)) {
      $methods = array($methods);
    }
    // Iterate over every method passed to check validation against.
    foreach ($methods as $method) {
      $validation = new Validation($this->form, $this->state, $target);
      // Get the valid boolean indicating pass (TRUE) or fail (FALSE).
      $valid[] = $validation->$method();
    }
    // Check all results of validation on this target. If any of them are FALSE
    // then add a FALSE entry to results.
    if (in_array(FALSE, $valid)) {
      $this->passed = FALSE;
      $this->results[$target] = FALSE;
    }
    else {
      $this->results[$target] = TRUE;
    }
    return $this->results[$target];
  }

  /**
   * Sets up the error messages for each form element.
   *
   * @param array $messages
   *   An array of key value pairs where the key is the dot notation target to
   *   display the error message in and the value is the message.
   */
  public function setErrorMessages($messages = array()) {
    // First of all check if we've passed all validation.
    if ($this->passed == TRUE) {
      $this->clearValidation();
      return;
    }

    $key = $this->stage . '_validation';
    // If we have any failures store them in the db to be picked up later.
    foreach ($this->results as $target => $valid) {
      if (!$valid) {
        // This field has failed validation and needs to have a message
        // displayed.
        $message = array_get($this->form, $target . '.#attributes.data-parsley-error-message', FALSE);
        if ($message) {
          $this->state['values']['validate'][$this->stage][$target] = $message;
          $data[$key][$target] = $message;
        }
      }
    }

    // It's possible to explicitly pass in error messages to be shown.
    foreach ($messages as $target => $message) {
      $this->state['values']['validate'][$this->stage][$target] = $message;
      $data[$key][$target] = $message;
    }

    // Store the validation data in the db.
    $store = MformsDatabaseStore::getInstance('myhaccp');
    $store->setStore($key, $data);
  }

  /**
   * Clears the form_state and post of validation messages.
   */
  public function clearValidation() {
    if (isset($this->state['values']['validate'])) {
      unset($this->state['values']['validate']);
    }
    if (isset($_POST['validate'])) {
      unset($_POST['validate']);
    }

    $key = $this->stage . '_validation';
    $data = array(
      $key => array(),
    );

    // Unset the validation from the db.
    $store = MformsDatabaseStore::getInstance('myhaccp');
    $store->setStore($key, $data);
  }

  /**
   * Checks if all fields are empty on a stage.
   *
   * Used to bail out of validation if fields have no values at all.
   *
   * @return bool
   *   TRUE if all fields are empty, FALSE otherwise.
   */
  public function allFieldsAreEmpty() {
    // Iterate over all the form_state values.
    $iterator = new RecursiveArrayIterator($this->state['values'][$this->stage]);
    // Prepare a new standard class so we can pass through items found from the
    // iterator.
    $found = new stdClass();
    $found->items = array();
    // Apply an iterator callback to each element of the array.
    iterator_apply($iterator, 'myhaccp_find_values', array($iterator, $found));
    // Check if there are any found items.
    if (!empty($found->items)) {
      // We have one of more values so return FALSE.
      return FALSE;
    }
    // Nothing found so return TRUE.
    return TRUE;
  }

  /**
   * Returns a boolean based on whether the save buttons have been used.
   *
   * @return bool
   *   If the pager was used it will return FALSE, otherwise TRUE.
   */
  public function saveButtonUsed() {
    if (isset($this->state['clicked_button'])) {
      $button = $this->state['clicked_button'];
      if ($button['#submit'] != 'myhaccp_pager_submit') {
        return TRUE;
      }
    }
    return FALSE;
  }

  /**
   * Returns a boolean based on whether the pager is used to save the form.
   *
   * @return bool
   *   If the pager was used it will return FALSE, otherwise TRUE.
   */
  public function pagerButtonUsed() {
    if (isset($this->state['clicked_button'])) {
      $button = $this->state['clicked_button'];
      if ($button['#submit'][0] == 'myhaccp_pager_submit') {
        return TRUE;
      }
    }
    return FALSE;
  }

}

/**
 * Class validation
 *
 * A single validation element to be tested for validity.
 */
class Validation {

  /**
   * Constructor method.
   *
   * Defines the type.
   */
  public function __construct($form, $form_state, $target) {
    $this->form = $form;
    $this->state = $form_state;
    $this->target = $target;
    $this->setType();
  }

  /**
   * Gets the form array element type and adds it as a property.
   */
  private function setType() {
    $element = $this->getElement($this->target);
    $this->type = isset($element['#type']) ? $element['#type'] : FALSE;
  }

  /**
   * Gets an element from the form array.
   *
   * @param string $target
   *   The target in dot notation.
   *
   * @return array
   *   The element or an empty array.
   */
  private function getElement($target) {
    $element = array_get($this->form, $target, array());
    return $element;
  }

  /**
   * Checks an element is valid and returns the result.
   */
  public function checkValid() {
    // Determine the method needed.
    $method = $this->getValidationMethod($this->type);
    // Check the validation.
    return $this->$method();
  }

  /**
   * Checks the field is not empty.
   *
   * @return bool
   *   FALSE if the field is emtpy. TRUE if there is content in the field.
   */
  public function fieldIsNotEmpty() {
    // We only have two methods of checking fields for empty values, checkboxes
    // and everything else.
    if ($this->type == 'checkboxes') {
      $options = array_get($this->state['values'], $this->target, array());
      foreach ($options as $option) {
        if ($option !== 0) {
          return TRUE;
        }
      }
    }
    else {
      // This will be a textarea, textfield, checkbox or radios type field.
      $value = array_get($this->state['values'], $this->target, FALSE);
      if ($value) {
        return TRUE;
      }
    }
    // We have found nothing.
    return FALSE;
  }

  /**
   * Ensures a radio field is not set to a value of 'no'.
   *
   * @return bool
   *   TRUE if option 'no' is not chosen, FALSE if it has been chosen.
   *
   * @throws Exception
   */
  public function radioIsNotNo() {
    if ($this->type != 'radios') {
      throw new Exception('Not a radios type field.');
    }
    $value = array_get($this->state['values'], $this->target, FALSE);
    if ($value == 'no') {
      return FALSE;
    }
    return TRUE;
  }

}
