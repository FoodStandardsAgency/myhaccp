<?php

/**
 * Principle 7.
 */
function principle_7(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_7';

  // Retrieve submitted values.
  $data = mforms_get_vals('myhaccp', 'principle_7');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  $values = myhaccp_prepare_values($data, $form_state);

  // Set the page title.
  drupal_set_title('Principle 7: Establish documentation and record keeping');

  $form = array();
  $form['#attributes']['class'][] = 'principle-7';

  // Wrap the form section in a fieldset.
  $form['principle_7'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // Determine how many instances we need to display. This is based on the data
  // from Principle 1 Question 3.
  $store = mforms_store_get('myhaccp');
  // Fetch the previous step data.
  $steps = MformsSteps::getInstance($store);
  $prev_step = $steps->getPrev();

  // Create the fieldset container.
  $form['principle_7'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // Now the form fields.

  $form['principle_7']['documentation'] = array(
    '#type' => 'container',
    '#prefix' => '<div class="label">Mark all forms of documentation relating to the HACCP study that your organisation retain.</div>',
  );

  $form['principle_7']['documentation']['study'] = array(
    '#type' => 'checkboxes',
    '#title' => t(''),
    '#options' => array(
      'scope' => 'Scope of the study',
      'reference' => 'Reference to prerequisite programmes',
      'team' => 'HACCP team members with details of their role, experience, training and qualifications',
      'product' => 'Product description',
      'use' => 'Intended use of the product',
      'flow' => 'Flow diagram, and the confirmation that it is correct',
      'hazards' => 'Relevant hazards (as determined from the hazard analysis) and control',
    ),
    '#default_value' => array_get($values, "principle_7.documentation.study", array()),
  );

  $form['principle_7']['documentation']['measures'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Measures'),
    '#options' => array(
      'details' => 'Details of all CCP’s that have been determined',
      'evidence' => 'Evidence of how CCP’s were determined',
      'ccps' => 'The critical limits at the CCP’s, with targets and tolerances where relevant',
      'monitoring' => 'The monitoring plan for each CCP',
      'corrective' => 'The corrective action plan for each CCP',
      'dates' => 'Details and date(s) of validation activities',
      'verification' => 'Details of verification activities, including the programme for scheduled review and a list of factors that should initiate a review',
      'procedures' => 'Reference to relevant procedures/work instructions and record forms',
    ),
    '#default_value' => array_get($values, "principle_7.documentation.measures", array()),
  );

  $form['principle_7']['supporting'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('Detail any other supporting information (i.e. anything that covers the HACCP system operation) that is retained.'),
    '#default_value' => array_get($values, "principle_7.supporting", FALSE),
  );

  $form['principle_7']['controlled'] = array(
    '#type' => 'textfield',
    '#title' => t('How is documentation controlled (up-dates / issue number)?'),
    '#default_value' => array_get($values, "principle_7.controlled", FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('Please detail how your documentation is controlled.'),
    ),
  );

  $form['principle_7']['time'] = array(
    '#type' => 'textfield',
    '#title' => t('What is the maximum length of time that you retain this information for?'),
    '#default_value' => array_get($values, "principle_7.time", FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('Please specify the maximum length of time that you retain this information for.'),
    ),
  );

  $form['principle_7']['maintained'] = array(
    '#type' => 'radios',
    '#title' => t('Are the records accessible, accurate and up to date?'),
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#default_value' => array_get($values, "principle_7.maintained", FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm that your records are accessible, accurate and up to date.'),
    ),
  );

  // Add the validation handler.
  $form['#validate'][] = 'principle_7_validate';

  return $form;
}

/**
 * Validation handler for Principle 2 Question 4.
 */
function principle_7_validate($form, &$form_state) {
  $invalid = array();

  $q11 = _checkboxes_field_is_empty($form_state['values'], 'principle_7.documentation.study');
  $q12 = _checkboxes_field_is_empty($form_state['values'], 'principle_7.documentation.measures');
  $q2 = _text_field_is_empty($form_state['values'], 'principle_7.supporting');

  // Check if there has been a response to question 1 or 2.
  if ((!$q11 || !$q12) || !$q2) {
    // In which case we need to check these three fields for values.
    $checks = array(
      'principle_7.controlled' => '_text_field_is_empty',
      'principle_7.time' => '_text_field_is_empty',
      'principle_7.maintained' => '_text_field_is_empty',
    );

    foreach ($checks as $target => $callback) {
      $invalid[] = _check_validation($callback, $target, $form, $form_state);
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

