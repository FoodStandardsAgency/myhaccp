<?php

function preparatory_h(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_1_question_1';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  drupal_set_title('Preparatory Stage H: On-site confirmation of flow diagram', PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'prep-f';

  // Wrap the form section in a fieldset.
  $form['prep_h'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // 1. Name of person(s) confirming flow diagram is correct:
  $form['prep_h']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('1. Name of person(s) confirming flow diagram is correct: !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'prep_h.name', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm the name of person(s) confirming flow diagram is correct.'),
    ),
  );

  // 2. Is every process step identified on the flow diagram? .
  $form['prep_h']['identified'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('2. Is every process step identified on the flow diagram? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'prep_h.identified', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm if every process step identified on the flow diagram.'),
    ),
  );

  // 3. Is the flow diagram an accurate representation of the process from
  // start to finish?
  $form['prep_h']['accurate'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('3. Is the flow diagram an accurate representation of the process from start to finish? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'prep_h.accurate', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm if the flow diagram is an accurate representation of the process from start to finish.'),
    ),
  );

  // 4. Is the process flow diagram correct for all shifts (e.g. days, nights
  // and weekend)?
  $form['prep_h']['shifts'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('4. Is the process flow diagram correct for all shifts (e.g. days, nights and weekend)? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'prep_h.shifts', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm if the process flow diagram correct for all shifts (e.g. days, nights and weekend).'),
    ),
  );

  // 5. Is the flow diagram correct during all seasonal variations?
  $form['prep_h']['seasonal'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('5. Is the flow diagram correct during all seasonal variations? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'prep_h.seasonal', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm if the flow diagram correct during all seasonal variations.'),
    ),
  );

  // 6. Has the team leader signed off and dated the flow diagram as being
  // correct?
  $form['prep_h']['leader'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('6. Has the team leader signed off and dated the flow diagram as being correct? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'prep_h.leader', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm if the team leader has signed off and dated the flow diagram as being correct.'),
    ),
  );

  // 7. Who in your organisation is aware that any changes to the process will require changes to the flow diagram?
  $form['prep_h']['changes'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('7. Who in your organisation is aware that any changes to the process will require changes to the flow diagram? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'prep_h.changes', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm the name of at least one person in your organisation who is aware that any changes to the process will require changes to the flow diagram.'),
    ),
  );

  // 8. Who in your organisation is responsible for storing all out-of-date versions of the flow diagram?
  $form['prep_h']['storing'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('8. Who in your organisation is responsible for storing all out-of-date versions of the flow diagram? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'prep_h.storing', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm the name of at least one person in your organisation who is responsible for storing all out-of-date versions of the flow diagram.'),
    ),
  );

  $form['#validate'][] = 'preparatory_h_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_h_validate($form, &$form_state) {
  $invalid = array();

  // Checks is an array with the key being the element being targeted (in dot
  // notation) and the value being the callback to use to check whether the
  // field is empty.
  $checks = array(
    'prep_h.name' => '_text_field_is_empty',
    'prep_h.identified' => '_radios_field_is_empty',
    'prep_h.accurate' => '_radios_field_is_empty',
    'prep_h.shifts' => '_radios_field_is_empty',
    'prep_h.seasonal' => '_radios_field_is_empty',
    'prep_h.leader' => '_radios_field_is_empty',
    'prep_h.changes' => '_text_field_is_empty',
    'prep_h.storing' => '_text_field_is_empty',
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