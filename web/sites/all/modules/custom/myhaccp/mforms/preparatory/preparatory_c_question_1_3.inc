<?php

function preparatory_c_question_1_3(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_c_question_4';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  drupal_set_title('Preparatory Stage C: Define scope of the study, <br/>Questions 1-3', PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'prep-c-1';

  // Wrap the form section in a fieldset.
  $form['prep_c_1_3'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $form['prep_c_1_3']['type'] = array(
    '#type' => 'select',
    '#title' => t('1. What type of HACCP plan are you producing? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#options' => array(
      'none' => t('-- Select --'),
      'linear' => t('Linear'),
      'modular' => t('Modular'),
      'linear_modular' => t('Linear / Modular'),
      'generic' => t('Generic'),
    ),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-notequal' => 'none',
      'data-parsley-error-message' => t('Please select the type of HACCP plan you are producing.'),
    ),
    '#default_value' => array_get($values, 'prep_c_1_3.prep_c_q1', array()),
  );

  $form['prep_c_1_3']['product'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('2. State the type of product you are producing and briefly how it is going to be packed: !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'prep_c_1_3.prep_c_q2', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state the type of product you are producing and how it will be packed.'),
    ),
  );

  $form['prep_c_1_3']['q3'] = array(
    '#type' => 'container',
  );

  $form['prep_c_1_3']['q3']['title'] = array(
    '#markup' => '<div class="label">' . t('3. State start and end points of the HACCP plan: !tip', array(
      '!tip' => _help_tip(),
      )
    ) . '</div>',
  );

  $form['prep_c_1_3']['q3']['start'] = array(
    '#type' => 'textfield',
    '#title' => t('It will start at '),
    '#default_value' => array_get($values, 'prep_c_1_3.prep_c_q3.start', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please add a start date.'),
    ),
  );

  $form['prep_c_1_3']['q3']['end'] = array(
    '#type' => 'textfield',
    '#title' => t('Through to '),
    '#default_value' => array_get($values, 'prep_c_1_3.prep_c_q3.end', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please add an end date.'),
    ),
  );

  $form['#validate'][] = 'preparatory_c_question_1_3_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_c_question_1_3_validate($form, &$form_state) {
  $invalid = array();

  // Validation: Some content.
  $checks = array(
    'prep_c_1_3.type' => '_select_field_is_empty',
    'prep_c_1_3.product' => '_text_field_is_empty',
    'prep_c_1_3.q3.start' => '_text_field_is_empty',
    'prep_c_1_3.q3.end' => '_text_field_is_empty',
  );

  foreach ($checks as $target => $callback) {
    $invalid[] = _check_validation($callback, $target, $form, $form_state);
  }

  // Check to see whether we have failed validation and therefore should store
  // it in the database or whether we have passed and therefore clear validation
  // errors.
  if (!in_array(TRUE, $invalid)) {
    // Remove any stored validation.
    myhaccp_clear_validation($form_state);
  }
}
