<?php

/**
 * Principle 3.
 */
function principle_3(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_4';

  // Retrieve submitted values.
  $data = mforms_get_vals('myhaccp', 'principle_3');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  $values = myhaccp_prepare_values($data, $form_state);

  // Set the page title.
  drupal_set_title('Principle 3: Establish Critical Limits');

  $form = array();
  $form['#attributes']['class'][] = 'principle-3';

  // Wrap the form section in a fieldset.
  $form['principle_3'] = array(
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
  $rows = array_get($previous_data, 'principle_2_question_4.instance_table', array());
  // Iterate through the previous data.
  foreach ($rows as $key => $item) {
    if (is_array($item)) {
      $hazard = unserialize($item['hazard']);
      // Determine the critical control point.
      if (!empty($item['ccp']) && $item['ccp'] == 'yes') {
        $items[] = $hazard;
      }
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
  $form['principle_3'] = array(
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
    $form['principle_3']['instance_' . $key] = array(
      '#type' => 'container',
    );

    // Each hazard with a ccp is an instance. Show the text first.
    $form['principle_3']['instance_' . $key]['ccp'] = array(
      '#type' => 'hidden',
      '#value' => serialize($item),
      '#prefix' => $ccp_number_text,
    );

    $form['principle_3']['instance_' . $key]['process_step'] = array(
      '#markup' => $process_step_text,
    );

    $form['principle_3']['instance_' . $key]['hazard'] = array(
      '#markup' => $hazard_text,
    );

    $form['principle_3']['instance_' . $key]['control_measure'] = array(
      '#markup' => $control_text,
    );

    // Now the form fields.
    $form['principle_3']['instance_' . $key]['limit'] = array(
      '#type' => 'textfield',
      '#title' => t('1. What is the critical limit for this critical control point (what separates safe from potentially unsafe product)?'),
      '#default_value' => array_get($values, "principle_3.instance_$key.limit", FALSE),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Validation message to be added'),
      ),
    );

    $form['principle_3']['instance_' . $key]['details'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('2. Provide details of how the critical limit was determined.'),
      '#default_value' => array_get($values, "principle_3.instance_$key.details", FALSE),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Validation message to be added'),
      ),
    );

    $form['principle_3']['instance_' . $key]['appropriate'] = array(
      '#type' => 'radios',
      '#options' => array(
        'yes' => t('Yes'),
        'no' => t('No'),
      ),
      '#title' => t('3. Is the critical limit appropriate to control the specific hazard?'),
      '#default_value' => array_get($values, "principle_3.instance_$key.appropriate", array()),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Validation message to be added'),
      ),
    );

    $form['principle_3']['instance_' . $key]['measurable'] = array(
      '#type' => 'radios',
      '#options' => array(
        'yes' => t('Yes'),
        'no' => t('No'),
      ),
      '#title' => t('4. Is the critical limit measurable or observable in real time?'),
      '#default_value' => array_get($values, "principle_3.instance_$key.measurable", array()),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Validation message to be added'),
      ),
    );

    $form['principle_3']['instance_' . $key]['target'] = array(
      '#type' => 'radios',
      '#options' => array(
        'yes' => t('Yes'),
        'no' => t('No'),
      ),
      '#title' => t('5. Is there a target value?'),
      '#default_value' => array_get($values, "principle_3.instance_$key.target", array()),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Validation message to be added'),
      ),
    );

    $form['principle_3']['instance_' . $key]['target_value'] = array(
      '#type' => 'textfield',
      '#title' => t('5a. If yes, what is the target value?'),
      '#default_value' => array_get($values, "principle_3.instance_$key.target_value", FALSE),
      '#states' => array(
        'visible' => array(
          ':input[name="principle_3[instance_' . $key . '][target]"]' => array('value' => 'yes'),
        ),
      ),
      '#attributes' => array(
        'data-parsley-error-message' => t('Validation message to be added'),
      ),
    );

    $form['principle_3']['instance_' . $key]['target_tolerances'] = array(
      '#type' => 'textfield',
      '#title' => t('5b. What are the tolerances?'),
      '#default_value' => array_get($values, "principle_3.instance_$key.target_tolerances", FALSE),
      '#states' => array(
        'visible' => array(
          ':input[name="principle_3[instance_' . $key . '][target]"]' => array('value' => 'yes'),
        ),
      ),
      '#attributes' => array(
        'data-parsley-error-message' => t('Validation message to be added'),
      ),
    );

  }

  // Add the validation handler.
  $form['#validate'][] = 'principle_3_validate';

  return $form;
}

/**
 * Validation handler for Principle 2 Question 4.
 */
function principle_3_validate($form, &$form_state) {
  $invalid = array();

  // Checks is an array with the key being the element being targeted (in dot
  // notation) and the value being the callback to use to check whether the
  // field is empty.
  $rows = array_get($form_state, 'values.principle_3', array());
  // Iterate over each row.
  foreach ($rows as $key => $row) {
    // Make sure 3 & 4 are yes values.
    $targets = array(
      "principle_3.$key.appropriate",
      "principle_3.$key.measurable",
    );
    // Iterate over the two fields and check them.
    foreach ($targets as $target) {
      // First check if the field is empty.
      if (!$invalid_item = _radios_field_is_empty($form_state['values'], $target)) {
        // The field is not empty so now check that the wrong value has been
        // entered.
        $invalid_item = _radios_field_is_not_value('yes', $form_state['values'], $target);
      }
      // If its invalid show the message.
      if ($invalid_item) {
        $message = array_get($form, $target . '.#attributes.data-parsley-error-message', NULL);
        myhacpp_prepare_validation($target, $message, $form_state);
      }
      // Add the invalid boolean to the array.
      $invalid[] = $invalid_item;
    }

    // Check for content in questions 1 & 2.
    $checks = array(
      "principle_3.$key.limit" => '_text_field_is_empty',
      "principle_3.$key.details" => '_text_field_is_empty',
    );

    foreach ($checks as $target => $callback) {
      $invalid[] = _check_validation($callback, $target, $form, $form_state);
    }

    // Now check if the radio button in 5 is set to yes.
    if (array_get($form_state['values'], "principle_3.$key.target", FALSE) == 'yes') {
      // Now check that both dependent fields 5a and 5b have something in them.
      $checks = array(
        "principle_3.$key.target_value" => '_text_field_is_empty',
        "principle_3.$key.target_tolerances" => '_text_field_is_empty',
      );

      foreach ($checks as $target => $callback) {
        $invalid[] = _check_validation($callback, $target, $form, $form_state);
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

