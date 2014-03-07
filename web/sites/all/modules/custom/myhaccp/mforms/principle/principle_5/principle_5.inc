<?php

/**
 * Principle 5.
 */
function principle_5(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_6';

  // Retrieve submitted values.
  $data = mforms_get_vals('myhaccp', 'principle_5');

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
  $form['#attributes']['class'][] = 'principle-5';

  // Wrap the form section in a fieldset.
  $form['principle_5'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array(
      'class' => array(
        'stage-fieldset',
      ),
    ),
  );

  // Introductory text.
  $form['principle_5']['intro'] = array(
    '#prefix' => '<p class="intro">',
    '#suffix' => '</p>',
    '#markup' => t('Document any action to be taken when monitoring results show that a CCP has deviated from the critical limit (indicating a loss of control).'),
  );

  $hazards = Hazards::getInstance();

  // Ensure there are hazards over the threshold.
  if ($hazards->countHazardsOverThreshold() == 0) {
    drupal_set_message('You have no significant hazards so you cannot continue', 'error');
    return $form;
  }

  // Determine how many instances we need to display. This is based on the data
  // from Principle 1 Question 3.
  $ccps = $hazards->getCCPs();

  $instance_count = count($ccps);

  // Bail out here with a message if there are no instances of the fieldsets
  // filled out correctly in the previous screen.
  if ($instance_count == 0) {
    drupal_set_message('You have no critical control points so you cannot continue');
    return $form;
  }

  // Build out the instances.
  foreach ($ccps as $hazard_key => $hazard) {
    $header = $hazard->getHeader();

    // Create the instance container.
    $form['principle_5'][$hazard_key] = array(
      '#type' => 'container',
    );

    $form['principle_5'][$hazard_key] += $header;

    // Now the form fields.
    $form['principle_5'][$hazard_key]['5_1'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('1. Corrective action to be taken.'),
      '#default_value' => array_get($values, "principle_5.$hazard_key.5_1", FALSE),
      '#help_text' => t("Provide details of what should be done in the event of failure to meet a critical limit."),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please state the action to be taken at this CCP.'),
      ),
    );

    $form['principle_5'][$hazard_key]['5_2'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('2. Detail personnel who have the authority to take the stated corrective action.'),
      '#default_value' => array_get($values, "principle_5.$hazard_key.5_2", FALSE),
      '#help_text' => t("Provide names. These people should be trained and competent in the activities that they are to perform when something has failed to meet a critical limit."),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please detail the personnel who have the authority to take the stated corrective action.'),
      ),
    );

    $form['principle_5'][$hazard_key]['5_3'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('3. What happens to the product created during the period that a CCP was out of control? Detail any variation in handling this product that relates to, a parameter, eg degree of control lost.'),
      '#default_value' => array_get($values, "principle_5.$hazard_key.5_3", FALSE),
      '#help_text' => t("Describe what will happen to the affected product?  E.g. will the product be disposed of ?  If so, how? Please provide all details. "),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please detail what happens to the product created during the period that a CCP was out of control.'),
      ),
    );

    $form['principle_5'][$hazard_key]['5_4'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('4. Where are you going to document what you have done with the product produced during the time period that a CCP was \'out of control\' (for example since the last good check)?'),
      '#default_value' => array_get($values, "principle_5.$hazard_key.5_4", FALSE),
      '#help_text' => t("Where will this information be recorded?  E.g. on a monitoring sheet, on a corrective action note, do you hold a specific file where this information is recorded?"),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t("Please detail where you will document what you have done with the product produced during the time period that a CCP was 'out of control'."),
      ),
    );

    $form['principle_5'][$hazard_key]['5_5'] = array(
      '#type' => 'radios',
      '#options' => array(
        'yes' => t('Yes'),
        'no' => t('No'),
      ),
      '#title' => t('5. Are all personnel (identified in any of the steps from 1-6 for all CCP’s) trained and competent for performing the activities stated?'),
      '#default_value' => array_get($values, "principle_5.$hazard_key.5_5", FALSE),
      '#help_text' => t("Is their training specific to the tasks they are expected to carry out?  Is it up-to-date."),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('All personnel engaged in any of the activities mentioned should have received appropriate training for the task undertaken. Records of training should be available.'),
      ),
    );

    $form['principle_5'][$hazard_key]['5_6'] = array(
      '#type' => 'radios',
      '#options' => array(
        'yes' => t('Yes'),
        'no' => t('No'),
      ),
      '#title' => t('6. Are records of competency maintained?'),
      '#help_text' => t("The competencies of staff should be reviewed. It may be necessary to train staff, refresh their training, provide on-the-job experience, records of which should be kept to reflect that staff are capable of performing the task they are undertaking"),
      '#default_value' => array_get($values, "principle_5.$hazard_key.5_6", FALSE),
      '#help_text' => t("State the person's name."),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('It is essential that all verification records are maintained.'),
      ),
    );

  }

  // Add the validation handler.
  $form['#validate'][] = 'principle_5_validate';

  return $form;
}

/**
 * Validation handler for Principle 2 Question 4.
 */
function principle_5_validate($form, &$form_state) {
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

  $rows = array_get($form_state, 'values.principle_5', array());
  // Iterate over each row.
  foreach ($rows as $key => $row) {
    $checks = array(
      "principle_5.$key.5_1" => 'fieldIsNotEmpty',
      "principle_5.$key.5_2" => 'fieldIsNotEmpty',
      "principle_5.$key.5_3" => 'fieldIsNotEmpty',
      "principle_5.$key.5_4" => 'fieldIsNotEmpty',
      "principle_5.$key.5_5" => array('fieldIsNotEmpty', 'radioIsNotNo'),
      "principle_5.$key.5_6" => array('fieldIsNotEmpty', 'radioIsNotNo'),
    );

    foreach ($checks as $target => $method) {
      $validator->validate($method, $target);
    }

  }

  $validator->setErrorMessages();
  $form_state = $validator->getFormState();

}

