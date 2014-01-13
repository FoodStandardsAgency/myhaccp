<?php

function preparatory_b(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_c_question_1_3';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  drupal_set_title('Preparatory Stage B: Management Commitment');

  $form = array();
  $form['#attributes']['class'][] = 'pb';

  // Wrap the form section in a fieldset.
  $form['container'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $form['container']['prep_b_support'] = array(
    '#type' => 'checkboxes',
    '#title' => t('What documented evidence do you have to show the support of senior management to the food safety management based on HACCP? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#options' => drupal_map_assoc(
      array(
        t('A Food Safety Policy has been drawn up and signed by managementv'),
        t('Senior management document, support and communicate their policies'),
        t('Minutes of team meetings are taken and reviewed'),
        t('Senior management support the work of the HACCP team'),
        t('Resources identified by the HACCP team are made available as required to develop, implement and maintain the HACCP system'),
        t('Training takes place for HACCP studies'),
        t('N/A I am the management and can confirm that I am committed.'),
      )
    ),
    '#default_value' => isset($values['container']['prep_b_support']) ? $values['container']['prep_b_support'] : array(),
  );

  $form['container']['prep_b_evidence'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('Other evidence: !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => isset($values['container']['prep_b_evidence']) ? $values['container']['prep_b_evidence'] : FALSE
  );

  $form['#validate'][] = 'preparatory_b_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_b_validate($form, &$form_state) {
  // Set a default of the form being valid.
  $invalid = FALSE;
  $values = $form_state['values'];

  // Validation: At least one box checked from Q1, or some content in question 2.
  if (_text_field_is_empty($values, 'container.prep_b_evidence') && _checkboxes_field_is_empty($values, 'container.prep_b_support')) {
    $message = t('Please choose at least one option in question 1 or add some content in question 2.');
    myhacpp_prepare_validation('container[prep_b_support]', $message, $form_state);
    myhacpp_prepare_validation('container[prep_b_evidence]', NULL, $form_state);
    // Ensure validation errors aren't cleared.
    $invalid = TRUE;
  }

  // Check to see whether we have failed validation and therefore should store
  // it in the database or whether we have passed and therefore clear validation
  // errors.
  if ($invalid == FALSE) {
    // Remove any stored validation.
    myhaccp_clear_validation($form_state);
  }
}
