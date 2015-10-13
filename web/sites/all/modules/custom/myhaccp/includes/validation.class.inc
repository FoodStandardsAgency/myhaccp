<?php

/**
 * @file
 * Validation handler class.
 */

/**
 * Class validator.
 *
 * A stage validation used to validate multiple elements and set or clear
 * messages.
 */
class Validator {

  /**
   * Sets the form state within the validator.
   *
   * @param array $form_state
   *   The form state array.
   */
  public function setFormState($form_state) {
    $this->formState = $form_state;
  }

  /**
   * Sets the IID of the study.
   *
   * @param int $iid
   *   The IID to store.
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
    return $this->iid;
  }

  /**
   * Returns the form state.
   */
  public function getFormState() {
    return $this->formState;
  }

  /**
   * Sets the given stage.
   */
  public function setStage(Stage $stage) {
    $this->stage = $stage;
  }

  /**
   * Gets the form.
   */
  public function getForm() {
    return $this->form;
  }

  /**
   * Sets the form.
   */
  public function setForm($form) {
    $this->form = $form;
  }

  /**
   * Gets the stage.
   */
  public function getStage() {
    return $this->stage;
  }

  /**
   * Gets the status of the validation.
   *
   * @param bool $stored
   *   Whether to use the stored database values.
   *
   * @return bool
   *   TRUE if passed validation, FALSE if not.
   */
  public function getStatus($stored = FALSE) {
    // If we have a status return it.
    if (isset($this->status)) {
      return $this->status;
    }

    // Check whether the stored database value is the one being requested.
    if ($stored) {
      // Get the validation from the database.
      $stage = $this->getStage();
      $validation_name = $stage->name . '_validation';
      $validation = $this->getValidation($stage);
      // Check if there is any validation stored.
      if (is_array($validation) && isset($validation[$validation_name])) {
        $validation = $validation[$validation_name];
        // If the array is empty it means validation has passed.
        if (empty($validation)) {
          $status = VALID;
        }
        else {
          $status = INVALID;
        }
      }
      else {
        // There is no validation which means the stage hasn't been started.
        $status = NOT_STARTED;
      }
      // Set the status.
      $this->setStatus($status);
      return $this->getStatus();
    }

    // Check for results from a validation.
    if (is_array($this->getResults())) {
      if (in_array(INVALID, $this->getResults())) {
        $status = INVALID;
      }
      else {
        $status = VALID;
      }
    }
    // Set the status.
    $this->setStatus($status);
    return $this->getStatus();
  }

  /**
   * Sets the status of the validation.
   *
   * @param bool $status
   *   TRUE if passed validation, FALSE if not.
   */
  public function setStatus($status) {
    $this->status = $status;
  }

  /**
   * Gets all the results for this validation.
   *
   * @return array
   *   An array of targets and booleans.
   */
  public function getResults() {
    return isset($this->results) ? $this->results : array();
  }

  /**
   * Gets the validation from the db for the current stage.
   */
  public function getValidation($stage) {
    $data = FALSE;
    $iid = $this->getIID();
    $key = $stage->name . '_validation';
    $query = db_select('mforms_storage', 'm');
    $query->join('mforms_storage_steps', 's', 's.iid = m.iid');
    $query->fields('s', array('store_data'))
      ->condition('m.iid', $iid)
      ->condition('s.store_key', $key);
    $result = $query->execute()->fetchField();
    if ($result) {
      $data = unserialize($result);
    }
    return $data;
  }

  /**
   * Sets the result.
   */
  public function setResult($target, $result) {
    $this->results[$target] = $result;
  }

  /**
   * Gets the result.
   */
  public function getResult($target) {
    return isset($this->results[$target]) ? $this->results[$target] : FALSE;
  }

  /**
   * Sets the validation up in form_state.
   *
   * @param array $form_state
   *   The form state to modify.
   *
   * @return array
   *   THe form state array.
   */
  public function addValidationtoFormState($form_state) {
    // Only do this for the myhaccp forms.
    if (is_array($form_state) && $form_state['build_info']['form_id'] == 'myhaccp_study_resume') {
      $data = $this->getValidation($this->getStage());
      if ($data) {
        $form_state['values']['validate'] = $this->getValidation($this->getStage());
      }
    }
    return $form_state;
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
      $validation = new Validation($this->getForm(), $this->getFormState(), $target);
      // Get the valid boolean indicating pass (TRUE) or fail (FALSE).
      $valid[] = $validation->$method();
    }
    // Check all results of validation on this target. If any of them are FALSE
    // then add a FALSE entry to results and set the status to FALSE.
    if (in_array(FALSE, $valid)) {
      $this->setStatus(INVALID);
      $this->setResult($target, INVALID);
    }
    else {
      // This set has passed so add TRUE to the results.
      $this->setResult($target, VALID);
    }
    return $this->getResult($target);
  }

  /**
   * Sets up the error messages for each form element.
   *
   * @param array $messages
   *   An array of key value pairs where the key is the dot notation target to
   *   display the error message in and the value is the message.
   */
  public function setErrorMessages($messages = array()) {
    $data = array();
    // First of all check if we've passed all validation.
    if ($this->getStatus() == VALID) {
      $this->clearValidation();
      return;
    }
    // Set up the stage name.
    $stage_name = $this->getStage()->getName();
    $key = $stage_name . '_validation';
    // If we have any failures store them in the db to be picked up later.
    foreach ($this->getResults() as $target => $valid) {
      if ($valid == INVALID) {
        // This field has failed validation and needs to have a message
        // displayed.
        $message = array_get($this->getForm(), $target . '.#attributes.data-parsley-error-message', '');
        $form_state = $this->getFormState();
        $form_state['values']['validate'][$stage_name][$target] = $message;
        $this->setFormState($form_state);
        $data[$key][$target] = $message;
      }
    }

    // It's possible to explicitly pass in error messages to be shown.
    foreach ($messages as $target => $message) {
      $form_state = $this->getFormState();
      $form_state['values']['validate'][$this->stage->name][$target] = $message;
      $this->setFormState($form_state);
      $data[$key][$target] = $message;
    }

    // If the validation has passed then data will be empty so store it in the
    // database for future validation checking.
    if (empty($data)) {
      $data = array(
        $key => array(),
      );
    }
    // Store the validation data in the db.
    $store = MformsDatabaseStore::getInstance('myhaccp');
    $store->setStore($key, $data);
  }

  /**
   * Clears the form_state and post of validation messages.
   */
  public function clearValidation() {
    $form_state = $this->getFormState();
    if (isset($form_state['values']['validate'])) {
      unset($form_state['values']['validate']);
      // Update the local form state.
      $this->setFormState($form_state);
    }
    if (isset($_POST['validate'])) {
      unset($_POST['validate']);
    }

    $key = $this->stage->name . '_validation';
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
    $iterator = new RecursiveArrayIterator($this->formState['values'][$this->getStage()->getName()]);
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
    if (isset($this->formState['clicked_button'])) {
      $button = $this->formState['clicked_button'];
      if ($button['#submit'][0] == 'myhaccp_pager_submit') {
        return TRUE;
      }
    }
    return FALSE;
  }

}

/**
 * Class validation.
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
   *   Only radio types are allowed.
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
