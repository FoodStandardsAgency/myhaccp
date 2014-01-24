<?php

/**
 * Principle 2, Question (part) 4.
 */
function principle_2_question_4(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_2_question_4';

  // Retrieve submitted values.
  $data = mforms_get_vals('myhaccp', 'principle_2_question_4');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  $values = myhaccp_prepare_values($data, $form_state);

  // Set the page title.
  drupal_set_title('Principle 2, question 4: Specify control measures.');

  $form = array();
  $form['#attributes']['class'][] = 'principle-2-question-4';

  // Wrap the form section in a fieldset.
  $form['principle_2_question_4'] = array(
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

  // Fetch the data from principle 1 question 3.
  $hazard_data = mforms_get_vals('myhaccp', 'principle_1_question_3');

  $items = array();

  // Iterate through the previous data.
  if (isset($hazard_data)) {
    foreach ($hazard_data['principle_1_question_3']['instance_table'] as $key => $item) {
      $hazard = unserialize($item['hazard']);
      $hazard['control_measure'] = $item['control_measure'];
      $items[] = $hazard;
    }
  }

  $instance_count = count($items);
  // Bail out here with a message if there are no instances of the fieldsets
  // filled out correctly in the previous screen.
  if ($instance_count == 0) {
    drupal_set_message('You have no hazards or no hazards over the threshold set in principle 1.3.', 'error');
    return $form;
  }

  // Create the fieldset container.
  $form['principle_2_question_4'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // Create the table.
  $form['principle_2_question_4']['instance_table'] = array(
    '#theme' => 'myhacpp_p2q4_table',
  );

  // Based on the information in the previous stage, build out the decision tree
  // radios.
  $decision_tree = array_get($previous_data, 'principle_2_question_1_3.decision_tree', 'none');
  $tree_type = array_get($previous_data, 'principle_2_question_1_3.which_tree', 'none');

  $form['principle_2_question_4']['instance_table']['decision_tree'] = array(
    '#type' => 'hidden',
    '#value' => $decision_tree,
  );

  // Build out the rows (three columns).
  foreach ($items as $key => $item) {
    // Prepare the text.
    $process_step_text = '(' . $item['step_number'] . ') ' . $item['step_name'];
    // The hazard column text.
    $hazard_text = '<div class="label hazard">' . $item['name'] . '</div><div class="hazard-description">' . $item['description'] . '</div>';

    $form['principle_2_question_4']['instance_table']['row_' . $key]['process_step'] = array(
      '#markup' => $process_step_text,
    );

    $form['principle_2_question_4']['instance_table']['row_' . $key]['hazard'] = array(
      '#markup' => $hazard_text,
    );

    $form['principle_2_question_4']['instance_table']['row_' . $key]['control_measure'] = array(
      '#markup' => '<div class="hazard-control-measure">' . $item['control_measure'] . '</div>',
    );

    if ($decision_tree !== 'no') {
      $num = 1;
      for ($q = 1; $q <= 6; $q++) {
        $id = 'Q' . $num;
        if ($tree_type == 'campden') {
          if ($q == 2) {
            $id = 'Q1a';
            $num = 2;
          }
          else {
            $num++;
          }
        }
        else {
          if ($q == 3) {
            $id = 'Q2a';
            $num = 3;
          }
          else {
            $num++;
          }
        }

        $form['principle_2_question_4']['instance_table']['row_' . $key]['decision_tree'][$id] = array(
          '#type' => 'radios',
          '#options' => array(
            'yes' => t('Yes'),
            'no' => t('No'),
            'n/a' => t('N/A'),
          ),
          '#title' => $id,
          '#default_value' => array_get($values, "principle_2_question_4.instance_table.row_$key.decision_tree.$id", array()),
          '#attributes' => array(
            'data-parsley-required' => 'true',
            'data-parsley-error-message' => t('Please indicate \'Yes\', \'No\' or \'N/A\' for this question in the decision tree.'),
          ),
        );
      }

    }
    else {
      $form['principle_2_question_4']['instance_table']['row_' . $key]['decision_tree'] = array(
        '#type' => 'hidden',
        '#value' => $decision_tree,
      );
    }

    $form['principle_2_question_4']['instance_table']['row_' . $key]['ccp'] = array(
      '#type' => 'radios',
      '#options' => array(
        'yes' => t('Yes'),
        'no' => t('No'),
      ),
      '#default_value' => array_get($values, "principle_2_question_4.instance_table.row_$key.ccp", array()),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please indicate whether this process step is a critical control point.'),
      ),
    );
  }

  // Add the validation handler.
  $form['#validate'][] = 'principle_2_question_4_validate';

  return $form;
}

/**
 * Validation handler for Principle 1 Question 1.
 */
function principle_2_question_4_validate($form, &$form_state) {
  $invalid = array();

  // Checks is an array with the key being the element being targeted (in dot
  // notation) and the value being the callback to use to check whether the
  // field is empty.
  $rows = array_get($form_state, 'values.principle_2_question_4.instance_table', array());
  foreach ($rows as $key => $row) {
    $checks = array(
      "principle_2_question_4.instance_table.$key.control_measure" => '_text_field_is_empty',
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

