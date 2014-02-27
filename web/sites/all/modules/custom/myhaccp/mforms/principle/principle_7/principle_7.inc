<?php

/**
 * Principle 7.
 */
function principle_7(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_summary';

  // Retrieve submitted values.
  $data = mforms_get_vals('myhaccp', 'principle_7');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  $values = myhaccp_prepare_values($data, $form_state);

  // Get the dependency injection container.
  global $container;
  // Get the current study.
  $study = $container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  drupal_set_title($stage->title, PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'principle-7';

  // Wrap the form section in a fieldset.
  $form['principle_7'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // Create the fieldset container.
  $form['principle_7'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // Now the form fields.
  $form['principle_7']['7_1'] = array(
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
    '#default_value' => array_get($values, "principle_7.7_1", array()),
    '#attributes' => array(
      'data-parsley-required' => TRUE,
      'data-parsley-error-message' => t('Please choose at least one option.'),
      'data-parsley-group' => 'study',
      'data-parsley-error-container' => '#edit-principle-7-study',
    ),
  );

  $form['principle_7']['7_2'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('2. Detail any other supporting information (i.e. anything that covers the HACCP system operation) that is retained.'),
    '#help_text' => t('Is there anything else (other documents) covering HACCP  that you keep hold of?'),
    '#default_value' => array_get($values, "principle_7.7_2", FALSE),
  );

  $form['principle_7']['7_3'] = array(
    '#type' => 'textfield',
    '#title' => t('3. How is documentation controlled (up-dates / issue number)?'),
    '#help_text' => t('For any forms, records, procedures, whether on paper or the computer do you have a system to ensure the latest issue is being used?  Provide details on how you achieve this.'),
    '#default_value' => array_get($values, "principle_7.7_3", FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('Please detail how your documentation is controlled.'),
    ),
  );

  $form['principle_7']['7_4'] = array(
    '#type' => 'textfield',
    '#title' => t('4. What is the maximum length of time that you retain this information for?'),
    '#help_text' => t('State the time period typically this is a minimum of the shelf-life plus an ‘additional period’.  The additional period  must take into consideration abuse of your product and you  may wish to keep records for a much longer period of time.'),
    '#default_value' => array_get($values, "principle_7.7_4", FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('Please specify the maximum length of time that you retain this information for.'),
    ),
  );

  $form['principle_7']['7_5'] = array(
    '#type' => 'radios',
    '#title' => t('5. Are the records accessible, accurate and up to date?'),
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#default_value' => array_get($values, "principle_7.7_5", FALSE),
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
  // Get the dependency injection container.
  global $container;
  // Get the current study.
  $study = $container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  $validator = $stage->getValidator();
  $validator->setFormState($form_state);
  $validator->setForm($form);

  if ($validator->pagerButtonUsed() && $validator->allFieldsAreEmpty()) {
    return;
  }

  $checks = array(
    'principle_7.7_1' => 'fieldIsNotEmpty',
    'principle_7.7_3' => 'fieldIsNotEmpty',
    'principle_7.7_4' => 'fieldIsNotEmpty',
    'principle_7.7_5' => 'fieldIsNotEmpty',
  );

  foreach ($checks as $target => $method) {
    $validator->validate($method, $target);
  }

  $validator->setErrorMessages();
  $form_state = $validator->getFormState();
}

