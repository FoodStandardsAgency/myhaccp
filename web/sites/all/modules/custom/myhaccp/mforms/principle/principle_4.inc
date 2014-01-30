<?php

/**
 * Principle 4.
 */
function principle_4(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_4';

  // Retrieve submitted values.
  $data = mforms_get_vals('myhaccp', 'principle_4');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  $values = myhaccp_prepare_values($data, $form_state);

  // Set the page title.
  drupal_set_title('Principle 4: Establish a monitoring system for each CCP');

  $form = array();
  $form['#attributes']['class'][] = 'principle-4';

  // Wrap the form section in a fieldset.
  $form['principle_4'] = array(
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
  $rows = array_get($previous_data, 'principle_3', array());
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
  $form['principle_4'] = array(
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
    $form['principle_4']['instance_' . $key] = array(
      '#type' => 'container',
    );

    // Each hazard with a ccp is an instance. Show the text first.
    $form['principle_4']['instance_' . $key]['ccp_no'] = array(
      '#type' => 'hidden',
      '#value' => serialize($item),
      '#prefix' => $ccp_number_text,
    );

    $form['principle_4']['instance_' . $key]['process_step'] = array(
      '#markup' => $process_step_text,
    );

    $form['principle_4']['instance_' . $key]['hazard'] = array(
      '#markup' => $hazard_text,
    );

    $form['principle_4']['instance_' . $key]['control_measure'] = array(
      '#markup' => $control_text,
    );

    // Now the form fields.
    $form['principle_4']['instance_' . $key]['activities'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('1. What monitoring activities are going to take place at this CCP?'),
      '#default_value' => array_get($values, "principle_4.instance_$key.monitoring", FALSE),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please state what monitoring activities are going to take place at this CCP.'),
      ),
    );

    $form['principle_4']['instance_' . $key]['frequency'] = array(
      '#type' => 'textfield',
      '#title' => t('2. Specify how frequently the monitoring activities are to be carried out.'),
      '#default_value' => array_get($values, "principle_4.instance_$key.frequency", FALSE),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please specify  how frequently the monitoring activities are to be carried out.'),
      ),
    );

    $form['principle_4']['instance_' . $key]['carried_out'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('3. Define how the monitoring activities are carried out.'),
      '#default_value' => array_get($values, "principle_4.instance_$key.carried_out", FALSE),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please define how the monitoring activities are carried out.'),
      ),
    );

    $form['principle_4']['instance_' . $key]['responsible'] = array(
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('4. Who is responsible for monitoring actions at this CCP?'),
      '#default_value' => array_get($values, "principle_4.instance_$key.responsible", FALSE),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please state who is responsible for monitoring actions at this CCP.'),
      ),
    );

    $form['principle_4']['instance_' . $key]['deputy'] = array(
      '#type' => 'radios',
      '#options' => array(
        'yes' => t('Yes'),
        'no' => t('No'),
      ),
      '#title' => t('5. Is there a deputy?'),
      '#default_value' => array_get($values, "principle_4.instance_$key.deputy", FALSE),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please state if there is a deputy.'),
      ),
    );

    $form['principle_4']['instance_' . $key]['deputy_name'] = array(
      '#type' => 'textfield',
      '#title' => t("5b. What is the deputy's name?"),
      '#default_value' => array_get($values, "principle_4.instance_$key.deputy_name", FALSE),
      '#states' => array(
        'visible' => array(
          ':input[name="principle_4[instance_' . $key . '][deputy]"]' => array('value' => 'yes'),
        ),
      ),
      '#attributes' => array(
        'data-parsley-error-message' => t("Please state the deputy's name."),
      ),
    );

    $form['principle_4']['instance_' . $key]['location'] = array(
      '#type' => 'textfield',
      '#title' => t('6. Where are the results of monitoring recorded?'),
      '#default_value' => array_get($values, "principle_4.instance_$key.location", FALSE),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please state where the results of monitoring are recorded.'),
      ),
    );

    $form['principle_4']['instance_' . $key]['checked'] = array(
      '#type' => 'radios',
      '#options' => array(
        'yes' => t('Yes'),
        'no' => t('No'),
      ),
      '#title' => t('7. Will the monitoring records be checked and signed off by anyone?'),
      '#default_value' => array_get($values, "principle_4.instance_$key.checked", FALSE),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please state if the monitoring records are to be checked and signed off by anyone.'),
      ),
    );

    $form['principle_4']['instance_' . $key]['record_name'] = array(
      '#type' => 'textfield',
      '#title' => t('7a. Who will check the records?'),
      '#default_value' => array_get($values, "principle_4.instance_$key.record_name", FALSE),
      '#states' => array(
        'visible' => array(
          ':input[name="principle_4[instance_' . $key . '][checked]"]' => array('value' => 'yes'),
        ),
      ),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please state who will check the records.'),
      ),
    );

    $form['principle_4']['instance_' . $key]['record_frequency'] = array(
      '#type' => 'textfield',
      '#title' => t('7b. How frequently will they check the records?'),
      '#default_value' => array_get($values, "principle_4.instance_$key.record_frequency", FALSE),
      '#states' => array(
        'visible' => array(
          ':input[name="principle_4[instance_' . $key . '][checked]"]' => array('value' => 'yes'),
        ),
      ),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please state how frequently the records will be checked.'),
      ),
    );

  }

  // Add the validation handler.
  $form['#validate'][] = 'principle_4_validate';

  return $form;
}

/**
 * Validation handler for Principle 2 Question 4.
 */
function principle_4_validate($form, &$form_state) {
  $invalid = array();

  // Checks is an array with the key being the element being targeted (in dot
  // notation) and the value being the callback to use to check whether the
  // field is empty.
  $rows = array_get($form_state, 'values.principle_4', array());
  // Iterate over each row.
  foreach ($rows as $key => $row) {

    // Check for content in visible questions.
    $checks = array(
      "principle_4.$key.activities" => '_text_field_is_empty',
      "principle_4.$key.frequency" => '_text_field_is_empty',
      "principle_4.$key.carried_out" => '_text_field_is_empty',
      "principle_4.$key.responsible" => '_text_field_is_empty',
      "principle_4.$key.deputy" => '_radios_field_is_empty',
      "principle_4.$key.location" => '_text_field_is_empty',
      "principle_4.$key.checked" => '_radios_field_is_empty',
    );

    foreach ($checks as $target => $callback) {
      $invalid[] = _check_validation($callback, $target, $form, $form_state);
    }

    // Now check if the radio button in 5 is set to yes.
    if (array_get($form_state['values'], "principle_4.$key.deputy", FALSE) == 'yes') {
      // Now check that the dependent fields 5a has something in it.
      $invalid[] = _check_validation('_text_field_is_empty', "principle_4.$key.deputy_name", $form, $form_state);
    }

    // Now check if the radio button in 7 is set to yes.
    if (array_get($form_state['values'], "principle_4.$key.checked", FALSE) == 'yes') {
      // Now check that both dependent fields 7a and 7b have something in them.
      $checks = array(
        "principle_4.$key.record_name" => '_text_field_is_empty',
        "principle_4.$key.record_frequency" => '_text_field_is_empty',
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

