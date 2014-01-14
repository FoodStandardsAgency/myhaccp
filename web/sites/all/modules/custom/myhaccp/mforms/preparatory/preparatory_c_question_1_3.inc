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

  drupal_set_title('Preparatory Stage C: Define scope of the study, Questions 1-3');

  $form = array();
  $form['#attributes']['class'][] = 'pcq13';

  // Wrap the form section in a fieldset.
  $form['container'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $form['container']['prep_c_q1'] = array(
    '#type' => 'select',
    '#title' => t('1. What type of HACCP plan are you producing? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#options' => drupal_map_assoc(
      array(
        t('Linear'),
        t('Modular'),
        t('Linear / Modular'),
        t('Generic'),
      )
    ),
    '#default_value' => array_get($values, 'container.prep_c_q1', array()),
  );

  $form['container']['prep_c_q2'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('2. State the type of product you are producing and briefly how it is going to be packed: !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.prep_c_q2', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please add some content.'),
    ),
  );

  $form['container']['prep_c_q3'] = array(
    '#type' => 'container',
  );

  $form['container']['prep_c_q3']['title'] = array(
    '#markup' => '<div class="label">' . t('3. State start and end points of the HACCP plan: !tip', array(
      '!tip' => _help_tip(),
      )
    ) . '</div>',
  );

  $form['container']['prep_c_q3']['start'] = array(
    '#type' => 'textfield',
    '#title' => t('It will start at '),
    '#default_value' => array_get($values, 'container.prep_c_q3.start', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please add a start date.'),
    ),
  );

  $form['container']['prep_c_q3']['end'] = array(
    '#type' => 'textfield',
    '#title' => t('Through to '),
    '#default_value' => array_get($values, 'container.prep_c_q3.end', FALSE),
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
  // Set a default of the form being valid.
  $invalid = FALSE;
  $values = $form_state['values'];

  // Validation: prep_c_q1 = At least one option should be selected.
//  if (_select_validation_options($values['container']['prep_c_q1'])) {
//    $message = t('Question 1: At least one option should be selected.');
//    myhacpp_prepare_validation('container[prep_c_q1]', $message, $form_state);
//    // Ensure validation errors aren't cleared.
//    $valid = FALSE;
//  }

  // Validation: prep_c_q2 = Has content.
  if ($invalid = _text_field_is_empty($values, 'container.prep_c_q2')) {
    $message = $form['container']['prep_c_q2']['#attributes']['data-parsley-error-message'];
    myhacpp_prepare_validation('container[prep_c_q2]', $message, $form_state);
  }

  // Validation: prep_c_q3 = Has a start and end date.
  if ($invalid = _text_field_is_empty($values, 'container.prep_c_q3.start')) {
    $message = $form['container']['prep_c_q3']['start']['#attributes']['data-parsley-error-message'];
    myhacpp_prepare_validation('container[prep_c_q3][start]', $message, $form_state);
  }
  if ($invalid = _text_field_is_empty($values, 'container.prep_c_q3.end')) {
    $message = $form['container']['prep_c_q3']['end']['#attributes']['data-parsley-error-message'];
    myhacpp_prepare_validation('container[prep_c_q3][end]', $message, $form_state);
  }

  // Check to see whether we have failed validation and therefore should store
  // it in the database or whether we have passed and therefore clear validation
  // errors.
  if ($invalid == FALSE) {
    // Remove any stored validation.
    myhaccp_clear_validation($form_state);
  }
}
