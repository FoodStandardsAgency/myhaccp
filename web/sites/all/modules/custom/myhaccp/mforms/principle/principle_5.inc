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

  // Set the page title.
  drupal_set_title('Principle 5: Establish a corrective action plan');

  $form = array();
  $form['#attributes']['class'][] = 'principle-5';

  // Wrap the form section in a fieldset.
  $form['principle_5'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // Ensure there are hazards over the threshold.
  if (myhaccp_ensure_over_threshold() == 0) {
    drupal_set_message('You have no significant hazards so you cannot continue', 'error');
    return $form;
  }

  $items = myhaccp_get_ccps();

  $instance_count = count($items);
  // Bail out here with a message if there are no critical control points.
  if ($instance_count == 0) {
    drupal_set_message('You have no critical control points so you cannot continue');
    return $form;
  }

  // Create the fieldset container.
  $form['principle_5'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // Build out the instances.
  foreach ($items as $key => $item) {
    $ccp_number_text = '<div class="ccp-number"><span class="label">Critical Control Point (CCP) Number:</span> ' . ($key + 1) . '</div>';
    // Prepare the text.
    $process_step_text = '<div class="process-step"><span class="label">Process Step:</span> ' . '(' . $item['step_number'] . ') ' . $item['step_name'] . '</div>';
    // The hazard text.
    $hazard_text = '<div class="hazard"><span class="label">Hazard:</span> ' . $item['name'] . '<div class="hazard-description">' . $item['description'] . '</div></div>';
    $control_text = '<div class="control-measure"><span class="label">Control Measure:</span> ' . $item['control_measure'] . '</div>';

    $item['ccp_no'] = $key + 1;

    // Create the instance container.
    $form['principle_5']['instance_' . $key] = array(
      '#type' => 'container',
    );

    // Each hazard with a ccp is an instance. Show the text first.
    $form['principle_5']['instance_' . $key]['ccp_no'] = array(
      '#type' => 'hidden',
      '#value' => serialize($item),
      '#prefix' => $ccp_number_text,
    );

    $form['principle_5']['instance_' . $key]['process_step'] = array(
      '#markup' => $process_step_text,
    );

    $form['principle_5']['instance_' . $key]['hazard'] = array(
      '#markup' => $hazard_text,
    );

    $form['principle_5']['instance_' . $key]['control_measure'] = array(
      '#markup' => $control_text,
    );

    // Now the form fields.
    $form['principle_5']['instance_' . $key]['action'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('1. Action to be taken'),
      '#default_value' => array_get($values, "principle_5.instance_$key.action", FALSE),
      '#help_text' => t("State the person's name."),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please state the action to be taken at this CCP.'),
      ),
    );

    $form['principle_5']['instance_' . $key]['authority'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('2. Detail personnel who have the authority to take the stated corrective action.'),
      '#default_value' => array_get($values, "principle_5.instance_$key.authority", FALSE),
      '#help_text' => t("State the person's name."),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please detail the personnel who have the authority to take the stated corrective action.'),
      ),
    );

    $form['principle_5']['instance_' . $key]['product'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('3. What happens to the product created during the period that a CCP was out of control? Detail any variation in handling this product that relates to, a parameter, eg degree of control lost.'),
      '#default_value' => array_get($values, "principle_5.instance_$key.product", FALSE),
      '#help_text' => t("State the person's name."),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please detail what happens to the product created during the period that a CCP was out of control.'),
      ),
    );

    $form['principle_5']['instance_' . $key]['document_location'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('4. Where are you going to document what you have done with the product produced during the time period that a CCP was \'out of control\' (for example since the last good check)?'),
      '#default_value' => array_get($values, "principle_5.instance_$key.document_location", FALSE),
      '#help_text' => t("State the person's name."),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t("Please detail where you will document what you have done with the product produced during the time period that a CCP was 'out of control'."),
      ),
    );

    $form['principle_5']['instance_' . $key]['trained'] = array(
      '#type' => 'radios',
      '#options' => array(
        'yes' => t('Yes'),
        'no' => t('No'),
      ),
      '#title' => t('5. Are all personnel (identified in any of the steps from 1-6 for all CCP’s) trained and competent for performing the activities stated?'),
      '#default_value' => array_get($values, "principle_5.instance_$key.trained", FALSE),
      '#help_text' => t("State the person's name."),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('All personnel engaged in any of the activities mentioned should have received appropriate training for the task undertaken. Records of training should be available.'),
      ),
    );

    $form['principle_5']['instance_' . $key]['competencies'] = array(
      '#type' => 'radios',
      '#options' => array(
        'yes' => t('Yes'),
        'no' => t('No'),
      ),
      '#title' => t('Are records of competency maintained?'),
      '#help_text' => t("The competencies of staff should be reviewed. It may be necessary to train staff, refresh their training, provide on-the-job experience, records of which should be kept to reflect that staff are capable of performing the task they are undertaking"),
      '#default_value' => array_get($values, "principle_5.instance_$key.competencies", FALSE),
      '#help_text' => t("State the person's name."),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please indicate if records of competency are maintained.'),
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
  $validator = new validator($form, $form_state, 'principle_5');

  if ($validator->allFieldsAreEmpty()) {
    return;
  }

  $rows = array_get($form_state, 'values.principle_5', array());
  // Iterate over each row.
  foreach ($rows as $key => $row) {
    $checks = array(
      "principle_5.$key.action" => 'fieldIsNotEmpty',
      "principle_5.$key.authority" => 'fieldIsNotEmpty',
      "principle_5.$key.product" => 'fieldIsNotEmpty',
      "principle_5.$key.document_location" => 'fieldIsNotEmpty',
      "principle_5.$key.trained" => 'fieldIsNotEmpty',
      "principle_5.$key.competencies" => 'fieldIsNotEmpty',
    );

    foreach ($checks as $target => $method) {
      $validator->validate($method, $target);
    }

  }

  $validator->setErrorMessages();

}

