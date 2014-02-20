<?php

/**
 * Principle 1, Question 2.
 */
function principle_1_2(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_1_3';

  // Retrieve submitted values.
  $data = mforms_get_vals('myhaccp', 'principle_1_2');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  $values = myhaccp_prepare_values($data, $form_state);

  // Set the page title.
  $stages = new stages();
  $stage = $stages->allStages[__FUNCTION__];
  drupal_set_title($stage->title, PASS_THROUGH);

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
      'data-validation-stage' => 'principle_1_2',
    ),
  );

  $hazards = new hazards();

  // Set an instance count so we know how many instances of the fieldsets we
  // need to show. One instance per step.
  $instance_count = $hazards->countHazards();

  // Bail out here with a message if there are no instances of the fieldsets
  // filled out correctly in the previous screen.
  if ($instance_count == 0) {
    drupal_set_message('You must add at least a step number and step name in the previous question as well as at least a hazard for the step.', 'error');
    return $form;
  }

  // Check whether the form_state has instances already filled out.
  $form_state['num_instances'] = $instance_count;

  // Keep a step count.
  $step_count = 0;

  $steps = $hazards->getHazardsByStep();

  // Iterate over the steps.
  foreach ($steps as $step_id => $step) {
    // Create a fieldset to wrap this instance and give it a legend.
    $form['principle_1_2'][$step_id] = array(
      '#type' => 'fieldset',
      '#title' => t('Process Step !step_no: !step_name', array(
        '!step_no' => $step['no'],
        '!step_name' => $step['name'],
      )),
    );

    // Create a table per step.
    $form['principle_1_2'][$step_id]['instance_table'] = array(
      '#theme' => 'myhaccp_1_2_table',
    );

    // Build out the rows.
    foreach ($step['hazards'] as $hazard_key => $hazard) {
      // Simplify the depth of the form with a reference.
      $form_position = &$form['principle_1_2'][$step_id]['instance_table'][$hazard_key];
      // Reference the form's default values to make it easier.
      $default_value = &$values['principle_1_2'][$step_id]['instance_table'][$hazard_key];
      // Create the elements of a row.
      $form_position['name'] = array(
        '#type' => 'hidden',
        '#value' => $hazard->name,
      );
      $form_position['description'] = array(
        '#type' => 'textarea',
        '#resizable' => FALSE,
        '#cols' => 20,
        '#default_value' => isset($default_value['description']) ? $default_value['description'] : NULL,
        '#attributes' => array(
          'data-parsley-required' => 'true',
          'data-parsley-error-message' => t('Please add a description.'),
          'class' => array('description'),
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
            drupal_get_path('module', 'myhaccp') . '/mforms/js/principle_1_2.js',
          ),
        ),
      );
    }
    // Increment the count.
    $step_count++;
  }

  $form['principle_1_2']['threshold'] = array(
    '#title' => t('Determine the threshold, above which you consider the hazard to be \'significant\': !tip', array(
      '!tip' => _help_tip(),
      )),
    '#help_text' => t('Please enter a number above which we will consider the hazard to be significant.'),
    '#type' => 'textfield',
    '#default_value' => array_get($values, 'principle_1_2.threshold', FALSE),
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
  $form['#validate'][] = 'principle_1_2_validate';

  return $form;
}

/**
 * Validation handler for Principle 1 Question 2.
 */
function principle_1_2_validate($form, &$form_state) {
  $validator = new validator($form, $form_state, 'principle_1_2');

  if ($validator->allFieldsAreEmpty()) {
    return;
  }

  // Iterate over each step.
  foreach ($form_state['values']['principle_1_2'] as $step_id) {
    $rows = array_get($form_state['values'], "principle_1_2.instance_$step_id.instance_table", array());
    foreach ($rows as $key => $hazard) {
      $checks = array(
        "principle_1_2.instance_$step_id.instance_table.$key.description" => 'fieldIsNotEmpty',
//        "principle_1_2.instance_$step_count.instance_table.$key.severity" => 'fieldIsNotEmpty',
//        "principle_1_2.instance_$step_count.instance_table.$key.likelihood" => 'fieldIsNotEmpty',
//        "principle_1_2.instance_$step_count.instance_table.$key.significance" => 'fieldIsNotEmpty',
      );
      foreach ($checks as $target => $method) {
        $validator->validate($method, $target);
      }
    }
  }

  $validator->setErrorMessages();
}

