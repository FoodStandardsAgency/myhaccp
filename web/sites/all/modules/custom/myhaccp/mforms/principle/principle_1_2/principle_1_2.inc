<?php

/**
 * @file
 * Principle 1 question 2 form and validation handler.
 */

/**
 * Principle 1 question 2.
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

  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
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

  $hazards = Hazards::getInstance();

  // Set an instance count so we know how many instances of the fieldsets we
  // need to show. One instance per step.
  $instance_count = $hazards->countHazards();

  // Bail out here with a message if there are no instances of the fieldsets
  // filled out correctly in the previous screen.
  if ($instance_count == 0) {
    drupal_set_message(t('You must add at least a step number and step name in the previous question as well as at least a hazard for the step.'), 'error', FALSE);
    return $form;
  }

  // Check whether the form_state has instances already filled out.
  $form_state['num_instances'] = $instance_count;

  // Keep a step count.
  $step_count = 0;

  $steps = $hazards->getHazardsByStep();

  // Introductory text.
  $form['principle_1_2']['intro'] = array(
    '#prefix' => '<p class="intro">',
    '#suffix' => '</p>',
    '#markup' => t('An assessment of the hazards identified is carried out to determine which hazards are of such a nature that their prevention, elimination or reduction to acceptable levels is essential to the production of safe food.'),
  );

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

    $form['principle_1_2'][$step_id]['intro'] = array(
      '#prefix' => '<div class="group-title">',
      '#suffix' => '</div>',
      '#markup' => t('For each hazard conduct a hazard analysis, giving it a score for severity of hazard and likelihood of hazard.'),
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
    '#title' => t('Determine the threshold, above which you consider the hazard to be \'significant\':'),
    '#help_text' => t('Please enter a number above which we will consider the hazard to be significant.'),
    '#help_link' => 17,
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
  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  $validator = $stage->getValidator();
  $validator->setFormState($form_state);
  $validator->setForm($form);

  if ($validator->pagerButtonUsed() && $validator->allFieldsAreEmpty()) {
    return;
  }

  // Iterate over each step.
  foreach ($form_state['values']['principle_1_2'] as $step_id) {
    foreach (array_get($form_state['values'], "principle_1_2", array()) as $step_id => $step) {
      if (!is_array($step)) {
        continue;
      }
      foreach ($step['instance_table'] as $key => $value) {
        $checks = array(
          "principle_1_2.$step_id.instance_table.$key.description" => 'fieldIsNotEmpty',
          "principle_1_2.$step_id.instance_table.$key.severity" => 'fieldIsNotEmpty',
          "principle_1_2.$step_id.instance_table.$key.likelihood" => 'fieldIsNotEmpty',
          "principle_1_2.$step_id.instance_table.$key.significance" => 'fieldIsNotEmpty',
        );
        foreach ($checks as $target => $method) {
          $validator->validate($method, $target);
        }
      }
    }
  }

  $validator->setErrorMessages();
  $form_state = $validator->getFormState();
}

