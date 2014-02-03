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

  // Determine how many instances we need to display. This is based on the data
  // from Principle 1 Question 3.
  $store = mforms_store_get('myhaccp');
  // Fetch the previous step data.
  $steps = MformsSteps::getInstance($store);
  $prev_step = $steps->getPrev();
  $previous_data = $store->getStore($prev_step);

  $items = array();
  $rows = array_get($previous_data, 'principle_4', array());
  // Iterate through the previous data.
  foreach ($rows as $key => $item) {
    if (is_array($item)) {
      $items[] = unserialize($item['ccp']);
    }
  }

  $instance_count = count($items);
  // Bail out here with a message if there are no instances of the fieldsets
  // filled out correctly in the previous screen.
  if ($instance_count == 0) {
    drupal_set_message('You have no critical control points');
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
      '#title' => t('1. Action to be taken !tip', array(
        '!tip' => _help_tip(),
      )),
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
      '#title' => t('2. Detail personnel who have the authority to take the stated corrective action. !tip', array(
        '!tip' => _help_tip(),
      )),
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
      '#title' => t('3. What happens to the product created during the period that a CCP was out of control? Detail any variation in handling this product that relates to, a parameter, eg degree of control lost. !tip', array(
        '!tip' => _help_tip(),
      )),
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
      '#title' => t('4. Where are you going to document what you have done with the product produced during the time period that a CCP was \'out of control\' (for example since the last good check)? !tip', array(
        '!tip' => _help_tip(),
      )),
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
      '#title' => t('5. Are all personnel (identified in any of the steps from 1-6 for all CCP’s) trained and competent for performing the activities stated? !tip', array(
        '!tip' => _help_tip(),
      )),
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
      '#title' => t('Are records of competency maintained? !tip', array(
        '!tip' => _help_tip(),
      )),
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
  $invalid = array();

  // Checks is an array with the key being the element being targeted (in dot
  // notation) and the value being the callback to use to check whether the
  // field is empty.
  $rows = array_get($form_state, 'values.principle_5', array());
  // Iterate over each row.
  foreach ($rows as $key => $row) {

    // Check for content in visible questions.
    $checks = array(
      "principle_5.$key.action" => '_text_field_is_empty',
      "principle_5.$key.authority" => '_text_field_is_empty',
      "principle_5.$key.product" => '_text_field_is_empty',
      "principle_5.$key.document_location" => '_text_field_is_empty',
      "principle_5.$key.trained" => '_radios_field_is_empty',
      "principle_5.$key.competencies" => '_radios_field_is_empty',
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

