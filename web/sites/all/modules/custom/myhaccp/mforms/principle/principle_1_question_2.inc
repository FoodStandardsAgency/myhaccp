<?php

/**
 * Principle 1, Question 1.
 */
function _principle_1_question_2(&$form_state, &$next_step) {
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

  $form = array();
  $form['#tree'] = TRUE;
//  $form['#theme'] = 'myhacpp_p1q2_table';


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
  foreach ($previous_data['container'] as $key => $instance) {
    if (strpos($key, 'instance') === 0) {
      if ($instance['p1q1_step_no'] != '' && $instance['p1q1_step_name'] != '') {
        $instance_count++;
      }
    }
  }

  // Bail out here with a message if there are no instances of the fieldsets
  // filled out correctly in the previous screen.
  if ($instance_count == 0) {
    drupal_set_message('You must add some information in the previous question');
    return $form;
  }

  // Check whether the form_state has instances already filled out.
  // @todo: How do we deal with changing instance numbers in the previous screen if a user has started filling out this screen?
  if (empty($form_state['num_instances'])) {
    // Set the number of instances on this screen to the instance count from
    // the last screen.
    $form_state['num_instances'] = $instance_count;
  }
  // Iterate over all the instances and generate a fieldset per previous
  // screen's instances (or filled out instances saved in the form_state).
  for ($i = 0; $i < $form_state['num_instances']; $i++) {
    // Get the necessary values from the previous step.
    $step_no = $previous_data['container']['instance-' . $i]['p1q1_step_no'];
    $step_name = $previous_data['container']['instance-' . $i]['p1q1_step_name'];
    // Prepare each of the four categories of hazard.
    $categories = array(
      'bio' => $previous_data['container']['instance-' . $i]['p1q1_biological'],
      'chem' => $previous_data['container']['instance-' . $i]['p1q1_chemical'],
      'phys' => $previous_data['container']['instance-' . $i]['p1q1_physical'],
      'allergens' => $previous_data['container']['instance-' . $i]['p1q1_allergens'],
    );
    // Process the hazards within each category.
    $hazards = array();
    foreach ($categories as $category) {
      if (!empty($category)) {
        $hazard_items = explode("\r\n", $category);
        $hazards = array_merge($hazards, $hazard_items);
      }
    }

    $form['container']['instance-' . $i] = array(
      '#type' => 'fieldset',
    );
    $form['container']['instance-' . $i]['instance_title'] = array(
      '#weight' => -1,
      '#markup' => t('Process Step !step_no: !step_name', array(
        '!step_no' => $step_no,
        '!step_name' => $step_name,
      )),
    );
    $form['container']['instance-' . $i]['instance_table'] = array(
      '#theme' => 'myhacpp_p1q2_table',
    );

    // Build out the rows.
    // @todo: What do we do with existing data? Do we only care about previous step.
    foreach ($hazards as $hazard) {
      // Simplify the depth of the form with a reference.
      $form_position = &$form['container']['instance-' . $i]['instance_table'][$hazard];
      // Reference the form's default values to make it easier.
      $default_value = &$vals['container']['instance-' . $i]['instance_table'][$hazard];
      // Create the elements of a row.
      $form_position['name'] = array(
        '#markup' => $hazard,
      );
      $form_position['description'] = array(
        '#type' => 'textarea',
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

//    // Step name.
//    $form['container']['instance-' . $i]['p1q1_step_name'] = array(
//      '#weight' => '1',
//      '#type' => 'textfield',
//      '#title' => t('Step name'),
//      '#default_value' => isset($vals['container']['instance-' . $i]['p1q1_step_name']) ? $vals['container']['instance-' . $i]['p1q1_step_name'] : NULL
//    );
//    // Markup.
//    $form['container']['instance-' . $i]['p1q1_message'] = array(
//      '#weight' => '2',
//      '#type' => 'markup',
//      '#value' => t('List all potential hazards that may be reasonably expected to occur at this process step:'),
//    );
//    // Biological.
//    $form['container']['instance-' . $i]['p1q1_biological'] = array(
//      '#weight' => '3',
//      '#type' => 'textfield',
//      '#title' => t('Biological'),
//      '#default_value' => isset($vals['container']['instance-' . $i]['p1q1_biological']) ? $vals['container']['instance-' . $i]['p1q1_biological'] : NULL
//    );
//    // Chemical.
//    $form['container']['instance-' . $i]['p1q1_chemical'] = array(
//      '#weight' => '4',
//      '#type' => 'textfield',
//      '#title' => t('Chemical'),
//      '#default_value' => isset($vals['container']['instance-' . $i]['p1q1_chemical']) ? $vals['container']['instance-' . $i]['p1q1_chemical'] : NULL
//    );
//    // Physical.
//    $form['container']['instance-' . $i]['p1q1_physical'] = array(
//      '#weight' => '5',
//      '#type' => 'textfield',
//      '#title' => t('Physical'),
//      '#default_value' => isset($vals['container']['instance-' . $i]['p1q1_physical']) ? $vals['container']['instance-' . $i]['p1q1_physical'] : NULL
//    );
//    // Allergens.
//    $form['container']['instance-' . $i]['p1q1_allergens'] = array(
//      '#weight' => '6',
//      '#type' => 'textfield',
//      '#title' => t('Allergens'),
//      '#default_value' => isset($vals['container']['instance-' . $i]['p1q1_allergens']) ? $vals['container']['instance-' . $i]['p1q1_allergens'] : NULL
//    );
//  }
//
//  $form['container']['add_instance'] = array(
//    '#type' => 'submit',
//    '#value' => t('Add another'),
//    '#submit' => array('instance_add_more_add_one'),
//    '#ajax' => array(
//      'callback' => 'instance_add_more_callback',
//      'wrapper' => 'instance-container',
//    ),
//  );
//  if ($form_state['num_instances'] > 1) {
//    $form['container']['remove_instance'] = array(
//      '#type' => 'submit',
//      '#value' => t('Remove one'),
//      '#submit' => array('instance_add_more_remove_one'),
//      '#ajax' => array(
//        'callback' => 'instance_add_more_callback',
//        'wrapper' => 'instance-container',
//      ),
//    );
  }

  return $form;
}
