<?php

/**
 * @file
 * Principle 1 question 3 form and validation handler.
 */

/**
 * Principle 1 question 3.
 */
function principle_1_3(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_2_1';

  // Retrieve submitted values.
  $data = mforms_get_vals('myhaccp', 'principle_1_3');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  $values = myhaccp_prepare_values($data, $form_state);

  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  drupal_set_title($stage->title, PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'principle-1-question-3';

  $hazards = Hazards::getInstance();

  if ($hazards->countHazards() == 0) {
    // There were no hazards.
    drupal_set_message(t('You must add at least a step number and step name in step 1.1 as well as at least a hazard for the step. Please return to 1.1'), 'error', FALSE);
    return $form;
  }

  // Check if we have anything over the threshold set in principle 1 question 2.
  $instance_count = $hazards->countHazardsOverThreshold();
  // Bail out here with a message if there are no instances of the fieldsets
  // filled out correctly in the previous screen.
  if ($instance_count == 0) {
    // There were no hazards over the threshold.
    drupal_set_message(t('You have no significant hazards so you cannot continue'), 'error', FALSE);
    return $form;
  }

  // Create the fieldset container.
  $form['principle_1_3'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array(
      'class' => array(
        'stage-fieldset',
      ),
    ),
  );

  // Introductory text.
  $form['principle_1_3']['intro'] = array(
    '#prefix' => '<p class="intro">',
    '#suffix' => '</p>',
    '#markup' => t('Control measures are actions and/or activities that are taken to prevent, eliminate or reduce the occurrence of a hazard.'),
  );

  // Create the table.
  $form['principle_1_3']['instance_table'] = array(
    '#theme' => 'myhaccp_1_3_table',
  );

  $theshold = $hazards->getHazardsOverTheshold();

  // Build out the rows (three columns).
  foreach ($theshold as $hazard_key => $hazard) {

    $step = $hazard->step;
    // Prepare the text.
    $process_step_text = '(' . $step->no . ') ' . $step->name;
    // The hazard column text.
    $hazard_text = '<div class="label hazard">' . $hazard->name . '</div><div class="hazard-description">' . nl2br($hazard->description) . '</div>';

    $form['principle_1_3']['instance_table'][$hazard_key]['process_step'] = array(
      '#markup' => $process_step_text,
    );

    $form['principle_1_3']['instance_table'][$hazard_key]['hazard'] = array(
      '#markup' => $hazard_text,
    );

    $form['principle_1_3']['instance_table'][$hazard_key]['control_measure'] = array(
      '#type' => 'textarea',
      '#help_text' => t('For each significant hazard, please specify the control measure.'),
      '#resizable' => FALSE,
      '#default_value' => array_get($values, "principle_1_3.instance_table.$hazard_key.control_measure", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add a control measure.'),
        'data-parsley-required' => TRUE,
        'class' => array(
          'control-measure',
        ),
      ),
    );
  }

  // Add the validation handler.
  $form['#validate'][] = 'principle_1_3_validate';

  return $form;
}

/**
 * Validation handler for Principle 1 Question 3.
 */
function principle_1_3_validate($form, &$form_state) {
  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  $validator = $stage->getValidator();
  $validator->setFormState($form_state);
  $validator->setForm($form);

  if ($validator->pagerButtonUsed() && $validator->allFieldsAreEmpty()) {
    return;
  }

  $rows = array_get($form_state, 'values.principle_1_3.instance_table', array());
  foreach ($rows as $hazard_key => $row) {
    $checks["principle_1_3.instance_table.$hazard_key.control_measure"] = 'fieldIsNotEmpty';
  }

  foreach ($checks as $target => $method) {
    $validator->validate($method, $target);
  }

  $validator->setErrorMessages();
  $form_state = $validator->getFormState();
}
