<?php

function preparatory_h(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_1_question_1';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'preparatory_h');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  drupal_set_title('Preparatory Stage H: On-site confirmation of flow diagram', PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'prep-f';

  // Wrap the form section in a fieldset.
  $form['preparatory_h'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // 1. Name of person(s) confirming flow diagram is correct:
  $form['preparatory_h']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('1. Name of person(s) confirming flow diagram is correct: !tip', array(
      '!tip' => _help_tip(22),
    )),
    '#help_link' => 22,
    '#help_text' => t('Name of person with overall responsibility for confirming it is correct and up-to-date.'),
    '#default_value' => array_get($values, 'preparatory_h.name', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm the name of person(s) confirming flow diagram is correct.'),
    ),
  );

  // 2. Is every process step identified on the flow diagram? .
  $form['preparatory_h']['identified'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('2. Is every process step identified on the flow diagram? !tip', array(
      '!tip' => _help_tip(22),
    )),
    '#help_link' => 22,
    '#help_text' => t('It is <strong>vital</strong> that every step is identified. This is a key stage.  Steps are often overlooked. If this occurs the potential to compromise food safety significantly increases. It is strongly recommended that you read the guidance notes on this.'),
    '#default_value' => array_get($values, 'preparatory_h.identified', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm if every process step identified on the flow diagram.'),
    ),
  );

  // 3. Is the flow diagram an accurate representation of the process from
  // start to finish?
  $form['preparatory_h']['accurate'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('3. Is the flow diagram an accurate representation of the process from start to finish? !tip', array(
      '!tip' => _help_tip(22),
    )),
    '#help_link' => 22,
    '#help_text' => t('Is the flow (shown by use of arrows) correct? Does the diagram go right from the start to the end of the process?'),
    '#default_value' => array_get($values, 'preparatory_h.accurate', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm if the flow diagram is an accurate representation of the process from start to finish.'),
    ),
  );

  // 4. Is the process flow diagram correct for all shifts (e.g. days, nights
  // and weekend)?
  $form['preparatory_h']['shifts'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('4. Is the process flow diagram correct for all shifts (e.g. days, nights and weekend)? !tip', array(
      '!tip' => _help_tip(22),
    )),
    '#help_link' => 22,
    '#help_text' => t('Does the process flow change at all depending on which shift is working?  Someone (preferably not on the shift) should check that this is the case for all shifts.'),
    '#default_value' => array_get($values, 'preparatory_h.shifts', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm if the process flow diagram correct for all shifts (e.g. days, nights and weekend).'),
    ),
  );

  // 5. Is the flow diagram correct during all seasonal variations?
  $form['preparatory_h']['seasonal'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('5. Is the flow diagram correct during all seasonal variations? !tip', array(
      '!tip' => _help_tip(22),
    )),
    '#help_link' => 22,
    '#help_text' => t('Consider high, standard and low  production times?'),
    '#default_value' => array_get($values, 'preparatory_h.seasonal', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm if the flow diagram correct during all seasonal variations.'),
    ),
  );

  // 6. Has the team leader signed off and dated the flow diagram as being
  // correct?
  $form['preparatory_h']['leader'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('6. Has the team leader signed off and dated the flow diagram as being correct? !tip', array(
      '!tip' => _help_tip(22),
    )),
    '#help_link' => 22,
    '#help_text' => t('The leader for HACCP should do this as they have ultimate responsibility to ensure it is correct.'),
    '#default_value' => array_get($values, 'preparatory_h.leader', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm if the team leader has signed off and dated the flow diagram as being correct.'),
    ),
  );

  // 7. Who in your organisation is aware that any changes to the process will require changes to the flow diagram?
  $form['preparatory_h']['changes'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('7. Who in your organisation is aware that any changes to the process will require changes to the flow diagram? !tip', array(
      '!tip' => _help_tip(22),
    )),
    '#help_link' => 22,
    '#help_text' => t('The flow diagram must be up-to-date at all times.  This should be all those involved in the HACCP study as a minimum.  For larger companies systems should be in place to ensure that a future planned or unplanned change to the process (equipment, product etc) will  trigger a change to the flow diagram.'),
    '#default_value' => array_get($values, 'preparatory_h.changes', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm the name of at least one person in your organisation who is aware that any changes to the process will require changes to the flow diagram.'),
    ),
  );

  // 8. Who in your organisation is responsible for storing all out-of-date versions of the flow diagram?
  $form['preparatory_h']['storing'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('8. Who in your organisation is responsible for storing all out-of-date versions of the flow diagram? !tip', array(
      '!tip' => _help_tip(22),
    )),
    '#help_link' => 22,
    '#help_text' => t('Name of person responsible for this.'),
    '#default_value' => array_get($values, 'preparatory_h.storing', FALSE),
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
    'preparatory_h.name' => '_text_field_is_empty',
    'preparatory_h.identified' => '_radios_field_is_empty',
    'preparatory_h.accurate' => '_radios_field_is_empty',
    'preparatory_h.shifts' => '_radios_field_is_empty',
    'preparatory_h.seasonal' => '_radios_field_is_empty',
    'preparatory_h.leader' => '_radios_field_is_empty',
    'preparatory_h.changes' => '_text_field_is_empty',
    'preparatory_h.storing' => '_text_field_is_empty',
  );

  foreach ($checks as $target => $callback) {
    if ($callback == '_radios_field_is_empty') {
      $value = array_get($form_state['values'], $target, FALSE);
      if (!$value || $value == 'no') {
        $invalid[] = TRUE;
        $message = array_get($form, $target . '.#attributes.data-parsley-error-message', NULL);
        myhacpp_prepare_validation($target, $message, $form_state);
      }
      else {
        $invalid[] = FALSE;
      }
    }
    else {
      if ($callback($form_state['values'], $target)) {
        $invalid[] = TRUE;
        $message = array_get($form, $target . '.#attributes.data-parsley-error-message', NULL);
        myhacpp_prepare_validation($target, $message, $form_state);
      }
      else {
        $invalid[] = FALSE;
      }
    }
  }

  // Check to see whether we have failed validation and therefore should store
  // it in the database or whether we have passed and therefore clear validation
  // errors.
  if (!in_array(TRUE, $invalid)) {
    // Remove any stored validation.
    myhaccp_clear_validation($form_state);
  }
}
