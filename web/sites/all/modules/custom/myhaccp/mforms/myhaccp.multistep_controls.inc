<?php

/**
 * @file
 * Single class that is an implementation of controls.
 * This implementation provides advanced controls for multistep form
 * where each step gets own button.
 */

/**
 * Provides functionality for forms with more than two steps where you
 * can navigate between individual steps.
 */
class MyHACCPMultiStepControls extends MformsControls {

  private static $instances = array();

  protected $steps_definition = array();

  protected $label_back;
  protected $label_continue;
  protected $label_submit;
  protected $label_delete;
  protected $label_save;

  protected $weight_back = 10;
  protected $weight_continue = 20;
  protected $weight_submit = 20;
  protected $weight_delete = 12;
  protected $weight_save = 15;

  protected $attributes_back = array();
  protected $attributes_continue = array();
  protected $attributes_submit = array();
  protected $attributes_delete = array();
  protected $attributes_save = array();

  protected $steps_label;


  public static function getInstance(MformsIstore $store, MformsSteps $steps, $steps_definition = NULL) {
    if (empty(self::$instances[$store->getKey()])) {
      $class = get_called_class();
      self::$instances[$store->getKey()] = new $class($store, $steps, $steps_definition);
    }

    return self::$instances[$store->getKey()];
  }

  protected function __construct(MformsIstore $store, MformsSteps $steps, $steps_definition) {
    $this->store = $store;
    $this->steps = $steps;
    $this->steps_definition = $steps_definition;

    // Init default labels.
    $this->label_continue = t('Next');
    $this->label_back = t('Previous');
    $this->label_save = t('Save');
    $this->label_submit = t('Submit');
    $this->label_delete = t('Reset');
  }

  function getControls($form) {
    $form_controls = array();

    if ($this->isSingleStep()) {
      return $form_controls;
    }

    $wrapper_id = $form['mforms_info']['#value']['wrapper_id'];

    // The form steps are displayed above the form. Create a wrapper for them.
    $form_controls['steps_btns_wrapper'] = array(
      '#type' => 'container',
      '#weight' => -1000,
      '#attributes' => array(
        'class' => array('pager-wrapper'),
      ),
    );

    $form_controls['steps_btns_wrapper']['preparatory'] = array(
      '#type' => 'container',
      '#prefix' => '<h3>' . t('Preparatory') . '</h3>',
      '#title' => $this->getStepsLabel(),
      '#attributes' => array(
        'class' => array('preparatory-wrapper'),
      ),
    );
    $form_controls['steps_btns_wrapper']['preparatory']['pager_controls'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('pager-controls'),
      ),
    );
    $form_controls['steps_btns_wrapper']['principles'] = array(
      '#type' => 'container',
      '#prefix' => '<h3>' . t('Principles') . '</h3>',
      '#title' => $this->getStepsLabel(),
      '#attributes' => array(
        'class' => array('principles-wrapper'),
      ),
    );
    $form_controls['steps_btns_wrapper']['principles']['pager_controls'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('pager-controls'),
      ),
    );

    $is_highlightable = TRUE;

    // Iterate through all the form steps and display them one after another.
    foreach ($this->steps_definition as $id => $definition) {
      $disabled = FALSE;
      if ($this->store->getStore($id) && !$this->isSingleStep()) {
        // $disabled = FALSE;
      }

      $class = '';
      if ($this->steps->getCurr() == $id || $is_highlightable) {
        $class = 'higlighted-step';
      }

      if ($this->steps->getCurr() == $id) {
        $class .= ' current-step';
        $is_highlightable = FALSE;
      }
      elseif ($disabled) {
        $class .= ' disabled-step';
      }
      elseif (in_array($id, $this->steps->getSteps())) {
        $class .= ' active-step';
      }

      // Show the step button.
      $form_controls['steps_btns_wrapper'][$definition['stage']]['pager_controls']['callback_' . $id] = array(
        '#type' => 'submit',
        '#value' => $definition['value'],
        '#weight' => $definition['weight'],
        '#disabled' => $disabled,
        '#attributes' => array('class' => array($class)),
        '#limit_validation_errors' => array(),
        '#submit' => array('_mforms_back_submit'),
        '#store_key' => $this->store->getKey(),
        '#mforms_step' => $id,
      );

      if ($this->ajaxified) {
        $form_controls['steps_btns_wrapper'][$definition['stage']]['pager_controls']['callback_' . $id]['#ajax'] = array(
          'callback' => '_mforms_ajax_get_form',
          'wrapper' => $wrapper_id,
          'method' => 'replace',
          'effect' => 'fade',
        );
      }
    }

    // Check if there is a next step (screen).
    if ($this->steps->getNext() != NULL) {
      $form_controls['continue'] = array(
        '#type' => 'submit',
        '#value' => $this->label_continue,
        '#weight' => $this->weight_continue,
        '#attributes' => $this->attributes_continue,
        '#submit' => array('_mforms_back_submit'),
        '#store_key' => $this->store->getKey(),
      );

      if ($this->ajaxified) {
        $form_controls['continue']['#ajax'] = array(
          'callback' => '_mforms_ajax_get_form',
          'wrapper' => $wrapper_id,
          'method' => 'replace',
          'effect' => 'fade',
        );
      }
    }
    // todo: Add the final submit back in.
//    else {
//      // If there is no next step then show the final submit button.
//      $form_controls['submit'] = array(
//        '#type' => 'submit',
//        '#value' => $this->label_submit,
//        '#weight' => $this->weight_submit,
//        '#attributes' => $this->attributes_submit,
//      );
//    }

    // Add a save button. This button simply saves the form state, much as the
    // previous and next buttons do.
    $form_controls['save'] = array(
      '#type' => 'submit',
      '#value' => $this->label_save,
      '#weight' => $this->weight_save,
      '#attributes' => $this->attributes_save,
      '#store_key' => $this->store->getKey(),
      '#mforms_step' => $this->steps->getCurr(),
      '#submit' => array('_mforms_back_submit'),
    );

    if ($this->steps->getPrev() != NULL) {
      $form_controls['test'] = array(
        '#type' => 'submit',
        '#value' => $this->label_back,
        '#weight' => $this->weight_back,
        '#attributes' => $this->attributes_back,
        '#store_key' => $this->store->getKey(),
        '#mforms_step' => $this->steps->getPrev(),
        '#submit' => array('_mforms_back_submit'),
      );
    }

    $form_controls['message'] = array(
      '#markup' => '<div class="help">Clicking \'Next\' or \'Previous\' will also Save this page.</div>',
      '#weight' => 100,
    );

    return $form_controls;
  }

  function doSubmitOnClickedAction() {
    $step_definition = $this->steps_definition[$this->steps->getCurr()];
    return isset($step_definition['submit']) ? $step_definition['submit'] : FALSE;
  }

  /**
   * Sets custom attributes for controls.
   *
   * @param array $back
   *   Back button attributes.
   * @param array $continue
   *   Continue button attributes.
   * @param array $submit
   *   Submit button attributes.
   * @param array $delete
   *   Delete/reset button attributes.
   */
  function setControlsAttributes($back, $continue, $submit, $delete) {
    if (is_array($back)) {
      $this->attributes_back = $back;
    }
    if (is_array($continue)) {
      $this->attributes_continue = $continue;
    }
    if (is_array($submit)) {
      $this->attributes_submit = $submit;
    }
    if (is_array($delete)) {
      $this->attributes_delete = $delete;
    }
  }

  /**
   * Sets custom labels for form controls.
   *
   * @param string $back
   *   Back button label.
   * @param string $continue
   *   Continue button label.
   * @param string $submit
   *   Submit button label.
   * @param string $delete
   *   Delete/reset button label.
   */
  function setControlsLabels($back, $continue, $submit, $delete) {
    if ($back != NULL && trim($back) != "") {
      $this->label_back = $back;
    }
    if ($continue != NULL && trim($continue) != "") {
      $this->label_continue = $continue;
    }
    if ($submit != NULL && trim($submit) != "") {
      $this->label_submit = $submit;
    }
    if ($delete != NULL && trim($delete) != "") {
      $this->label_delete = $delete;
    }
  }

  /**
   * Sets weights for form control elements.
   *
   * @param int $back
   *   Back button weight.
   * @param int $continue
   *   Continue button weight.
   * @param int $submit
   *   Submit button weight.
   * @param int $delete
   *   Delete/reset button weight.
   */
  function setControlsWeights($back, $continue, $submit, $delete) {
    $this->weight_back = $back;
    $this->weight_continue = $continue;
    $this->weight_submit = $submit;
    $this->weight_delete = $delete;
  }

  /**
   * Sets label displayed above steps buttons.
   *
   * @param string $steps_label
   *   Label text.
   */
  function setStepsLabel($steps_label) {
    $this->steps_label = $steps_label;
  }

  /**
   * Gets steps buttons label.
   *
   * @return string
   *   Label text.
   */
  function getStepsLabel() {
    return $this->steps_label;
  }
}
