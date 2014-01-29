<?php

/**
 * Principle 3.
 */
function principle_3(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_3';

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
    if (isset($item['hazard'])) {
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
    // The hazard column text.
    $hazard_text = '<div class="hazard"><span class="label">Hazard:</span> ' . $item['name'] . '<div class="hazard-description">' . $item['description'] . '</div>';
    $control_text = '<div class="control-measure"><span class="label">Control Measure:</span> ' . $item['control_measure'] . '</div>';

    $form['principle_3']['instance_' . $key]['ccp_no'] = array(
      '#type' => 'hidden',
      '#value' => $key + 1,
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

    $form['principle_3']['instance_' . $key]['limit'] = array(
      '#type' => 'textfield',
      '#title' => t('What is the critical limit for this critical control point (what separates safe from potentially unsafe product)?'),
      '#default_value' => array_get($values, "principle_3.instance_$key.limit", array()),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('To be added'),
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
  $checks = array();

  // Checks is an array with the key being the element being targeted (in dot
  // notation) and the value being the callback to use to check whether the
  // field is empty.
  $rows = array_get($form_state, 'values.principle_3', array());
  // Iterate over each row of the table.
  foreach ($rows as $key => $row) {
    // Within each row there may be multiple elements of a decision tree.
    $tree = array_get($row, "decision_tree", array());
    foreach ($tree as $id => $element) {
      $checks["principle_3.instance_table.$key.decision_tree.$id"] = '_radios_field_is_empty';
    }
    // Ensure there is a CCP value.
    $checks["principle_3.instance_table.$key.ccp"] = '_radios_field_is_empty';
  }

  // Check all the errors.
  foreach ($checks as $target => $callback) {
    $invalid[] = _check_validation($callback, $target, $form, $form_state);
  }

  // Check to see whether we have failed validation and therefore should store
  // it in the database or whether we have passed and therefore clear validation
  // errors.
  if (!in_array(TRUE, $invalid)) {
    // Remove any stored validation.
    myhaccp_clear_validation($form_state);
  }
}

