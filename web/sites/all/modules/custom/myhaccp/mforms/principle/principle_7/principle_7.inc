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
  $form['principle_7']['study'] = array(
    '#type' => 'checkboxes',
    '#title' => t('1. Mark all forms of documentation relating to the HACCP study that your organisation retain.'),
    '#options' => array(
      'scope' => 'Scope of the study',
      'reference' => 'Reference to prerequisite programmes',
      'team' => 'HACCP team members with details of their role, experience, training and qualifications',
      'product' => 'Product description',
      'use' => 'Intended use of the product',
      'flow' => 'Flow diagram, and the confirmation that it is correct',
      'hazards' => 'Relevant hazards (as determined from the hazard analysis) and control measures',
      'details' => 'Details of all CCP’s that have been determined',
      'evidence' => 'Evidence of how CCP’s were determined',
      'ccps' => 'The critical limits at the CCP’s, with targets and tolerances where relevant',
      'monitoring' => 'The monitoring plan for each CCP',
      'corrective' => 'The corrective action plan for each CCP',
      'dates' => 'Details and date(s) of validation activities',
      'verification' => 'Details of verification activities, including the programme for scheduled review and a list of factors that should initiate a review',
      'procedures' => 'Reference to relevant procedures/work instructions and record forms',
    ),
    '#help_text' => t('Do you keep hold of any of the following documents?'),
    '#default_value' => array_get($values, "principle_7.study", array()),
    '#attributes' => array(
      'data-parsley-required' => TRUE,
      'data-parsley-error-message' => t('Please choose at least one option.'),
      'data-parsley-group' => 'study',
      'data-parsley-error-container' => '#edit-principle-7-study',
    ),
  );

  $form['principle_7']['supporting'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('2. Detail any other supporting information (i.e. anything that covers the HACCP system operation) that is retained.'),
    '#help_text' => t('Is there anything else (other documents) covering HACCP  that you keep hold of?'),
    '#default_value' => array_get($values, "principle_7.supporting", FALSE),
  );

  $form['principle_7']['controlled'] = array(
    '#type' => 'textfield',
    '#title' => t('3. How is documentation controlled (up-dates / issue number)?'),
    '#help_text' => t('For any forms, records, procedures, whether on paper or the computer do you have a system to ensure the latest issue is being used?  Provide details on how you achieve this.'),
    '#default_value' => array_get($values, "principle_7.controlled", FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('Please detail how your documentation is controlled.'),
    ),
  );

  $form['principle_7']['time'] = array(
    '#type' => 'textfield',
    '#title' => t('4. What is the maximum length of time that you retain this information for?'),
    '#help_text' => t('State the time period typically this is a minimum of the shelf-life plus an ‘additional period’.  The additional period  must take into consideration abuse of your product and you  may wish to keep records for a much longer period of time.'),
    '#default_value' => array_get($values, "principle_7.time", FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('Please specify the maximum length of time that you retain this information for.'),
    ),
  );

  $form['principle_7']['maintained'] = array(
    '#type' => 'radios',
    '#title' => t('5. Are the records accessible, accurate and up to date?'),
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
  $validator = new validator($form, $form_state, 'principle_7');

  if ($validator->allFieldsAreEmpty()) {
    return;
  }

  $checks = array(
    'principle_7.study' => 'fieldIsNotEmpty',
    'principle_7.controlled' => 'fieldIsNotEmpty',
    'principle_7.time' => 'fieldIsNotEmpty',
    'principle_7.maintained' => 'fieldIsNotEmpty',
  );

  foreach ($checks as $target => $method) {
    $validator->validate($method, $target);
  }

  $validator->setErrorMessages();
}

