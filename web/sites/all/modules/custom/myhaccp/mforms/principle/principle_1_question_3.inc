<?php

/**
 * Principle 1, Question 3.
 */
function principle_1_question_3(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_2_question_1_3';

  // Retrieve submitted values.
  $data = mforms_get_vals('myhaccp', 'principle_1_question_3');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  $values = myhaccp_prepare_values($data, $form_state);

  // Set the page title.
  drupal_set_title('Principle 1, question 3: Specify control measures.', PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'principle-1-question-3';

  // Wrap the form section in a fieldset.
  $form['principle_1_question_3'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // Determine how many instances we need to display. This is based on the data
  // from Principle 1 Question 2.
  $store = mforms_store_get('myhaccp');
  // Fetch the previous step data.
  $steps = MformsSteps::getInstance($store);
  $prev_step = $steps->getPrev();
  $previous_data = $store->getStore($prev_step);

  // Get the previously set threshold value.
  $threshold = array_get($previous_data, 'principle_1_question_2.threshold', FALSE);
  // Set a instance count so we know how many rows we
  // need to show. One instance per previous stage instance with a number over
  // the threshold amount.
  $instance_count = 0;
  $items = array();

  // Iterate through the previous data and look for instances which have the
  // correct form fields filled out.
  if (isset($previous_data) && $threshold) {
    foreach ($previous_data['principle_1_question_2'] as $key => $instance) {
      if (strpos($key, 'instance') === 0) {
        foreach ($instance['instance_table'] as $key => $item) {
          if (isset($item['significance']) && $item['significance'] > $threshold) {
            $items[] = $item;
          }
        }
      }
    }
  }

  $instance_count = count($items);
  // Bail out here with a message if there are no instances of the fieldsets
  // filled out correctly in the previous screen.
  if ($instance_count == 0) {
    drupal_set_message('You have no hazards over the threshold set in the previous question.', 'error');
    return $form;
  }

  // Create the fieldset container.
  $form['principle_1_question_3'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // Create the table.
  $form['principle_1_question_3']['instance_table'] = array(
    '#theme' => 'myhacpp_p1q3_table',
  );

  // Build out the rows (three columns).
  foreach ($items as $key => $item) {

    // Get the details of this step and item, serialized into a hidden form
    // element in the previous question (seemed like the easiest way).
    $details = unserialize($item['details']);

    // Prepare the text.
    $process_step_text = '(' . $details['step_number'] . ') ' . $details['step_name'];
    // The hazard column text.
    $hazard_text = '<div class="label hazard">' . $details['name'] . '</div><div class="hazard-description">' . $item['description'] . '</div>';

    $form['principle_1_question_3']['instance_table']['row_' . $key]['process_step'] = array(
      '#markup' => $process_step_text,
    );

    $hazard_details = $details;
    $hazard_details['description'] = $item['description'];
    $hazard_details['control_measure'] = array_get($values, "principle_1_question_3.instance_table.row_$key.control_measure", FALSE);

    $form['principle_1_question_3']['instance_table']['row_' . $key]['hazard'] = array(
      '#prefix' => $hazard_text,
      '#type' => 'hidden',
      '#value' => serialize($hazard_details),
    );

    $form['principle_1_question_3']['instance_table']['row_' . $key]['control_measure'] = array(
      '#type' => 'textarea',
      '#help_text' => t('For each signifiant hazard, please specify the control measure.'),
      '#resizable' => FALSE,
      '#default_value' => array_get($values, "principle_1_question_3.instance_table.row_$key.control_measure", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add a control measure.'),
        'data-parsley-required' => TRUE,
      ),
    );
  }


  // Add the validation handler.
  $form['#validate'][] = 'principle_1_question_3_validate';

  return $form;
}

/**
 * Validation handler for Principle 1 Question 1.
 */
function principle_1_question_3_validate($form, &$form_state) {
  $invalid = array();

  // Checks is an array with the key being the element being targeted (in dot
  // notation) and the value being the callback to use to check whether the
  // field is empty.
  $rows = array_get($form_state, 'values.principle_1_question_3.instance_table', array());
  foreach ($rows as $key => $row) {
    $checks = array(
      "principle_1_question_3.instance_table.$key.control_measure" => '_text_field_is_empty',
    );
  }

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

