<?php

/**
 * Principle 1, Question 1.
 */
function principle_1_question_2(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
//  $next_step = '_principle_1_question_2';

  // Retrieve submitted values. This comes in handy when back action
  // occured and we need to display values that were originaly submitted.
  $data = mforms_get_vals('myhaccp');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  if (!empty($data)) {
    $vals = $data;
  }
  elseif (isset($form_state['values'])) {
    $vals = $form_state['values'];
  }

  // Set the page title.
  drupal_set_title('Principle 1 Question 2');

  $form = array();
  $form['#tree'] = TRUE;
  $form['#attributes']['class'][] = 'p1q2';

  // The wrapper for each instance of the form.
  $form['container'] = array(
    '#type' => 'markup',
    // Set up the wrapper so that AJAX will be able to replace the fieldset.
    '#prefix' => '<div id="instance-container">',
    '#suffix' => '</div>',
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

  // Iterate through the previous data and look for instances which have the
  // correct form fields filled out.
  if (isset($previous_data)) {
    foreach ($previous_data['container'] as $key => $instance) {
      if (strpos($key, 'instance') === 0) {
        if ($instance['p1q1_step_wrapper']['p1q1_step_no'] != '' && $instance['p1q1_step_wrapper']['p1q1_step_name'] != '') {
          $instance_count++;
        }
      }
    }
  }
  // Bail out here with a message if there are no instances of the fieldsets
  // filled out correctly in the previous screen.
  if ($instance_count == 0) {
    drupal_set_message('You must add at least a step number and step name in the previous question', 'warning');
    return $form;
  }

  // Check whether the form_state has instances already filled out.
  // @todo: How do we deal with changing instance numbers in the previous screen if a user has started filling out this screen?
  $form_state['num_instances'] = $instance_count;

  // Iterate over all the instances and generate a fieldset per previous
  // screen's instances (or filled out instances saved in the form_state).
  for ($i = 0; $i < $form_state['num_instances']; $i++) {
    // Get the necessary values from the previous step.
    $step_no = $previous_data['container']['instance_' . $i]['p1q1_step_wrapper']['p1q1_step_no'];
    $step_name = $previous_data['container']['instance_' . $i]['p1q1_step_wrapper']['p1q1_step_name'];
    // Prepare each of the four categories of hazard.
    $categories = array(
      'bio' => $previous_data['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_biological'],
      'chem' => $previous_data['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_chemical'],
      'phys' => $previous_data['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_physical'],
      'allergens' => $previous_data['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_allergens'],
    );
    // Process the hazards within each category.
    $hazards = array();
    foreach ($categories as $category) {
      if (!empty($category)) {
        $hazard_items = explode("\r\n", $category);
        foreach ($hazard_items as $item) {
          // Create a unique id for this item.
          $key = drupal_html_id($item);
          $hazards[$key] = $item;
        }
      }
    }

    // Create a fieldset to wrap this instance and give it a legend.
    $form['container']['instance_' . $i] = array(
      '#type' => 'fieldset',
      '#title' => t('Process Step !step_no: !step_name !tip', array(
        '!step_no' => $step_no,
        '!step_name' => $step_name,
        '!tip' => _help_tip(),
      )),
    );

    // Create the table.
    $form['container']['instance_' . $i]['instance_table'] = array(
      '#theme' => 'myhacpp_p1q2_table',
    );

    // Build out the rows.
    // @todo: What do we do with existing data? Do we only care about previous step.
    foreach ($hazards as $hazard => $name) {
      // Simplify the depth of the form with a reference.
      $form_position = &$form['container']['instance_' . $i]['instance_table'][$hazard];
      // Reference the form's default values to make it easier.
      $default_value = &$vals['container']['instance_' . $i]['instance_table'][$hazard];
      // Create the elements of a row.
      $form_position['name'] = array(
        '#markup' => $name,
      );
      $form_position['description'] = array(
        '#type' => 'textarea',
        '#resizable' => FALSE,
        '#cols' => 20,
        '#default_value' => isset($default_value['description']) ? $default_value['description'] : NULL
      );
      $form_position['severity'] = array(
        '#type' => 'textfield',
        '#size' => 6,
        '#default_value' => isset($default_value['severity']) ? $default_value['severity'] : NULL
      );
      $form_position['likelihood'] = array(
        '#type' => 'textfield',
        '#size' => 6,
        '#default_value' => isset($default_value['likelihood']) ? $default_value['likelihood'] : NULL
      );
      $form_position['significance'] = array(
        '#type' => 'textfield',
        '#size' => 6,
        '#default_value' => isset($default_value['significance']) ? $default_value['significance'] : NULL
      );
    }
  }

  $form['#validate'][] = 'principle_1_question_2_validate';

  return $form;
}

/**
 * Validation handler for Principle 1 Question 1.
 */
function principle_1_question_2_validate($form, &$form_state) {
  $validate = FALSE;

  // Test to see whether there is any submitted data for the first instance.
  if (isset($form_state['values']['container']['instance_0'])) {
    $form_position = & $form_state['values']['container'];
    // Iterate over the tables.
    foreach ($form_position as &$instance) {
      foreach ($instance['instance_table'] as &$item) {
        foreach ($item as $element) {
          if ($element != '') {
            $validate = TRUE;
          }
        }
      }
    }
  }

  // Determine which message to show.
  if ($validate == FALSE) {
    drupal_set_message(t('Principle 1 Question 2 requires information to be present.'), 'warning');
  }
  else {
    drupal_set_message(t('Information saved.'));
  }
}
