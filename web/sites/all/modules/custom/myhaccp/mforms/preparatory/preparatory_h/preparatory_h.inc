<?php

function preparatory_h(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_summary';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'preparatory_h');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  $stages = new Stages();
  $stage = $stages->getStage(__FUNCTION__);
  drupal_set_title($stage->title, PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'prep-h';

  // Wrap the form section in a fieldset.
  $form['preparatory_h'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // 1. Name of person(s) confirming flow diagram is correct:
  $form['preparatory_h']['h_1'] = array(
    '#type' => 'textfield',
    '#title' => t('1. Name of person(s) confirming flow diagram is correct:'),
    '#help_link' => 22,
    '#help_text' => t('Name of person with overall responsibility for confirming it is correct and up-to-date.'),
    '#default_value' => array_get($values, 'preparatory_h.h_1', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm the name of person(s) confirming flow diagram is correct.'),
    ),
  );

  // 2. Is every process step identified on the flow diagram? .
  $form['preparatory_h']['h_2'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('2. Is every process step identified on the flow diagram?'),
    '#help_link' => 22,
    '#help_text' => t('It is <strong>vital</strong> that every step is identified. This is a key stage.  Steps are often overlooked. If this occurs the potential to compromise food safety significantly increases. It is strongly recommended that you read the guidance notes on this.'),
    '#default_value' => array_get($values, 'preparatory_h.h_2', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm if every process step identified on the flow diagram.'),
    ),
  );

  // 3. Is the flow diagram an accurate representation of the process from
  // start to finish?
  $form['preparatory_h']['h_3'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('3. Is the flow diagram an accurate representation of the process from start to finish?'),
    '#help_link' => 22,
    '#help_text' => t('Is the flow (shown by use of arrows) correct? Does the diagram go right from the start to the end of the process?'),
    '#default_value' => array_get($values, 'preparatory_h.h_3', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm if the flow diagram is an accurate representation of the process from start to finish.'),
    ),
  );

  // 4. Is the process flow diagram correct for all shifts (e.g. days, nights
  // and weekend)?
  $form['preparatory_h']['h_4'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('4. Is the process flow diagram correct for all shifts (e.g. days, nights and weekend)?'),
    '#help_link' => 22,
    '#help_text' => t('Does the process flow change at all depending on which shift is working?  Someone (preferably not on the shift) should check that this is the case for all shifts.'),
    '#default_value' => array_get($values, 'preparatory_h.h_4', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm if the process flow diagram correct for all shifts (e.g. days, nights and weekend).'),
    ),
  );

  // 5. Is the flow diagram correct during all seasonal variations?
  $form['preparatory_h']['h_5'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('5. Is the flow diagram correct during all seasonal variations?'),
    '#help_link' => 22,
    '#help_text' => t('Consider high, standard and low  production times?'),
    '#default_value' => array_get($values, 'preparatory_h.h_5', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm if the flow diagram correct during all seasonal variations.'),
    ),
  );

  // 6. Has the team leader signed off and dated the flow diagram as being
  // correct?
  $form['preparatory_h']['h_6'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('6. Has the team leader signed off and dated the flow diagram as being correct?'),
    '#help_link' => 22,
    '#help_text' => t('The leader for HACCP should do this as they have ultimate responsibility to ensure it is correct.'),
    '#default_value' => array_get($values, 'preparatory_h.h_6', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm if the team leader has signed off and dated the flow diagram as being correct.'),
    ),
  );

  // 7. Who in your organisation is aware that any changes to the process will require changes to the flow diagram?
  $form['preparatory_h']['h_7'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('7. Who in your organisation is aware that any changes to the process will require changes to the flow diagram?'),
    '#help_link' => 22,
    '#help_text' => t('The flow diagram must be up-to-date at all times.  This should be all those involved in the HACCP study as a minimum.  For larger companies systems should be in place to ensure that a future planned or unplanned change to the process (equipment, product etc) will  trigger a change to the flow diagram.'),
    '#default_value' => array_get($values, 'preparatory_h.h_7', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm the name of at least one person in your organisation who is aware that any changes to the process will require changes to the flow diagram.'),
    ),
  );

  // 8. Who in your organisation is responsible for storing all out-of-date versions of the flow diagram?
  $form['preparatory_h']['h_8'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('8. Who in your organisation is responsible for storing all out-of-date versions of the flow diagram?'),
    '#help_link' => 22,
    '#help_text' => t('Name of person responsible for this.'),
    '#default_value' => array_get($values, 'preparatory_h.h_8', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm the name of at least one person in your organisation who is responsible for storing all out-of-date versions of the flow diagram.'),
    ),
  );

  $form['#validate'][] = __FUNCTION__ . '_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_h_validate($form, &$form_state) {
  $validator = Validator::getInstance();
  $validator->setFormState($form_state);

  if ($validator->pagerButtonUsed() && $validator->allFieldsAreEmpty()) {
    return;
  }

  $checks = array(
    'preparatory_h.h_1' => 'fieldIsNotEmpty',
    'preparatory_h.h_2' => array('fieldIsNotEmpty', 'radioIsNotNo'),
    'preparatory_h.h_3' => array('fieldIsNotEmpty', 'radioIsNotNo'),
    'preparatory_h.h_4' => array('fieldIsNotEmpty', 'radioIsNotNo'),
    'preparatory_h.h_5' => array('fieldIsNotEmpty', 'radioIsNotNo'),
    'preparatory_h.h_6' => array('fieldIsNotEmpty', 'radioIsNotNo'),
    'preparatory_h.h_7' => 'fieldIsNotEmpty',
    'preparatory_h.h_8' => 'fieldIsNotEmpty',
  );

  foreach ($checks as $target => $method) {
    $validator->validate($method, $target);
  }

  $validator->setErrorMessages();
}
