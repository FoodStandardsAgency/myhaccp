<?php

/**
 * Principle 1, Question 2.
 */
function principle_1_question_2(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_1_question_3';

  // Retrieve submitted values.
  $data = mforms_get_vals('myhaccp', 'principle_1_question_2');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  $values = myhaccp_prepare_values($data, $form_state);

  // Set the page title.
  drupal_set_title('Principle 1, question 2: Conduct a hazard analysis.');

  $form = array();
  $form['#tree'] = TRUE;
  $form['#attributes']['class'][] = 'principle-1-question-2';

  // The wrapper for each instance of the form.
  $form['container'] = array(
    '#type' => 'markup',
    // Set up the wrapper so that AJAX will be able to replace the fieldset.
    '#prefix' => '<div id="instance-container">',
    '#suffix' => '</div>',
  );

  // Show global message on this form.
  $form['validation_messages'] = array(
    '#type' => 'container',
    '#id' => 'validation-messages',
    '#weight' => -10,
    '#attributes' => array(
      'data-validation-stage' => 'principle_1_question_2',
    ),
  );

  // Determine how many instances we need to display. This is based on the data
  // from Principle 1 Question 1.
  $store = mforms_store_get('myhaccp');
  // Fetch the previous step data.
  $steps = MformsSteps::getInstance($store);
  $prev_step = $steps->getPrev();
  $previous_data = $store->getStore($prev_step);

  // Set an instance count so we know how many instances of the fieldsets we
  // need to show. One instance per previous step instance.
  $instance_count = 0;

  // Iterate through the previous data and look for instances which have a step
  // number and step name and then dig deeper for a hazard. We need this semi
  // validation up front so we know what to show.
  if (isset($previous_data)) {
    foreach ($previous_data['principle_1_question_1'] as $key => $instance) {
      if (strpos($key, 'instance') === 0) {
        if (array_get($instance, 'wrapper.step_no', FALSE) && array_get($instance, 'wrapper.step_no', FALSE)) {
          $checks = array(
            "hazards_wrapper.biological" => '_text_field_is_empty',
            "hazards_wrapper.physical" => '_text_field_is_empty',
            "hazards_wrapper.allergens" => '_text_field_is_empty',
            "hazards_wrapper.chemical" => '_text_field_is_empty',
          );

          foreach ($checks as $target => $callback) {
            $invalid[] = $callback($instance, $target);
          }

          // If all four hazard fields from the previous stage are 'invalid'
          // (empty) then this instance doesn't pass.
          if (in_array(FALSE, $invalid)) {
            $instance_count++;
          }

        }
      }
    }
  }
  // Bail out here with a message if there are no instances of the fieldsets
  // filled out correctly in the previous screen.
  if ($instance_count == 0) {
    drupal_set_message('You must add at least a step number and step name in the previous question as well as at least a hazard for the step.', 'error');
    return $form;
  }

  // Check whether the form_state has instances already filled out.
  // @todo: How do we deal with changing instance numbers in the previous screen if a user has started filling out this screen?
  $form_state['num_instances'] = $instance_count;

  // Iterate over all the instances and generate a fieldset per previous
  // screen's instances (or filled out instances saved in the form_state).
  for ($i = 0; $i < $form_state['num_instances']; $i++) {
    // Get the necessary values from the previous step.
    $step_no = $previous_data['principle_1_question_1']['instance_' . $i]['wrapper']['step_no'];
    $step_name = $previous_data['principle_1_question_1']['instance_' . $i]['wrapper']['step_name'];
    // Prepare each of the four categories of hazard.
    $categories = array(
      'bio' => $previous_data['principle_1_question_1']['instance_' . $i]['hazards_wrapper']['biological'],
      'chem' => $previous_data['principle_1_question_1']['instance_' . $i]['hazards_wrapper']['chemical'],
      'phys' => $previous_data['principle_1_question_1']['instance_' . $i]['hazards_wrapper']['physical'],
      'allergens' => $previous_data['principle_1_question_1']['instance_' . $i]['hazards_wrapper']['allergens'],
    );
    // Process the hazards within each category.
    $hazards = array();
    // Iterate over the categories.
    foreach ($categories as $category) {
      if (!empty($category)) {
        // Split the hazard items listed in the category text area into an
        // array, one item per line in the text area.
        $hazard_items = explode("\r\n", trim($category));
        // Iterate over each hazard item in this category.
        foreach ($hazard_items as $item) {
          // If the item isn't empty add the hazard.
          if ($item != '') {
            // Create a unique id for this item.
            $key = drupal_html_id($item);
            $hazards[$key] = $item;
          }
        }
      }
    }

    // Create a fieldset to wrap this instance and give it a legend.
    $form['principle_1_question_2']['instance_' . $i] = array(
      '#type' => 'fieldset',
      '#title' => t('Process Step !step_no: !step_name', array(
        '!step_no' => $step_no,
        '!step_name' => $step_name,
      )),
    );

    // Create the table.
    $form['principle_1_question_2']['instance_' . $i]['instance_table'] = array(
      '#theme' => 'myhacpp_p1q2_table',
    );

    // Build out the rows.
    // @todo: What do we do with existing data? Do we only care about previous step.
    foreach ($hazards as $hazard => $name) {
      // Simplify the depth of the form with a reference.
      $form_position = &$form['principle_1_question_2']['instance_' . $i]['instance_table'][$hazard];
      // Reference the form's default values to make it easier.
      $default_value = &$values['principle_1_question_2']['instance_' . $i]['instance_table'][$hazard];
      // Create the elements of a row.
      $details = array(
        'step_name' => $step_name,
        'step_number' => $step_no,
        'name' => $name,
      );
      $form_position['details'] = array(
        '#type' => 'hidden',
        '#prefix' => $name,
        '#value' => serialize($details),
      );
      $form_position['description'] = array(
        '#type' => 'textarea',
        '#resizable' => FALSE,
        '#cols' => 20,
        '#default_value' => isset($default_value['description']) ? $default_value['description'] : NULL,
        '#attributes' => array(
          'data-parsley-required' => 'true',
          'data-parsley-error-message' => t('Please add a description.'),
        ),
      );
      $form_position['severity'] = array(
        '#type' => 'textfield',
        '#size' => 6,
        '#default_value' => isset($default_value['severity']) ? $default_value['severity'] : NULL,
        '#attributes' => array(
          'data-parsley-required' => 'true',
          'data-parsley-min' => 1,
          'data-parsley-max' => 3,
          'data-parsley-type' => 'digits',
          'data-parsley-validation-minlength' => 1,
          'data-parsley-error-message' => t('Please add a severity between 1 and 3.'),
          'class' => array('severity'),
        ),
      );
      $form_position['likelihood'] = array(
        '#type' => 'textfield',
        '#size' => 6,
        '#default_value' => isset($default_value['likelihood']) ? $default_value['likelihood'] : NULL,
        '#attributes' => array(
          'data-parsley-required' => 'true',
          'data-parsley-min' => 1,
          'data-parsley-max' => 3,
          'data-parsley-type' => 'digits',
          'data-parsley-validation-minlength' => 1,
          'data-parsley-error-message' => t('Please add a likelihood between 1 and 3.'),
          'class' => array('likelihood'),
        ),
      );
      $form_position['significance'] = array(
        '#type' => 'textfield',
        '#size' => 6,
        '#default_value' => isset($default_value['significance']) ? $default_value['significance'] : NULL,
        '#attributes' => array(
          'data-parsley-required' => 'true',
          'data-parsley-min' => 1,
          'data-parsley-max' => 9,
          'data-parsley-type' => 'digits',
          'data-parsley-validation-minlength' => 1,
          'data-parsley-error-message' => t('Please add a significance between 1 and 9.'),
          'class' => array('significance'),
        ),
        '#attached' => array(
          'js' => array(
            drupal_get_path('module', 'myhaccp') . '/mforms/js/principle_1_question_2.js',
          ),
        ),
      );
    }
  }

  $form['principle_1_question_2']['threshold'] = array(
    '#title' => t('Determine the threshold, above which you consider the hazard to be \'significant\': !tip', array(
      '!tip' => _help_tip(),
      )),
    '#help_text' => t('Please enter a number above which we will consider the hazard to be significant.'),
    '#type' => 'textfield',
    '#default_value' => array_get($values, 'principle_1_question_2.threshold', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-min' => 1,
      'data-parsley-max' => 9,
      'data-parsley-type' => 'digits',
      'data-parsley-validation-minlength' => 1,
      'data-parsley-error-message' => t('Please add a threshold value between 1 and 9.'),
    ),
  );

  // Add the validation handler.
  $form['#validate'][] = 'principle_1_question_2_validate';

  return $form;
}

/**
 * Validation handler for Principle 1 Question 2.
 */
function principle_1_question_2_validate($form, &$form_state) {
  $invalid = array();

  $num_instances = $form_state['num_instances'];

  // Iterate over each instance.
  for ($i = 0; $i < $num_instances; $i++) {
    $rows = array_get($form_state['values'], "principle_1_question_2.instance_$i.instance_table", array());
    foreach ($rows as $key => $hazard) {
      $checks = array(
        "principle_1_question_2.instance_$i.instance_table.$key.description" => '_text_field_is_empty',
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

