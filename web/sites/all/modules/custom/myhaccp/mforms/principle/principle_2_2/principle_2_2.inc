<?php

/**
 * Principle 2, Question (part) 4.
 */
function principle_2_2(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_3';

  // Retrieve submitted values.
  $data = mforms_get_vals('myhaccp', 'principle_2_2');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  $values = myhaccp_prepare_values($data, $form_state);

  // Get the dependency injection container.
  global $container;
  // Get the current study.
  $study = $container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  drupal_set_title($stage->title, PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'principle-2-question-4';

  // Wrap the form section in a fieldset.
  $form['principle_2_2'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array(
      'class' => array(
        'stage-fieldset',
      ),
    ),
  );

  // Determine how many instances we need to display. This is based on the data
  // from Principle 1 Question 3.
  $store = mforms_store_get('myhaccp');
  // Fetch the previous step data.
  $steps = MformsSteps::getInstance($store);
  $prev_step = $steps->getPrev();
  $previous_data = $store->getStore($prev_step);

  $hazards = Hazards::getInstance();

  if ($hazards->countHazards() == 0) {
    // There were no hazards.
    drupal_set_message('You must add at least a step number and step name in step 1.1 as well as at least a hazard for the step. Please return to 1.1', 'error', FALSE);
    return $form;
  }

  // Ensure there are hazards over the threshold.
  if ($hazards->countHazardsOverThreshold() == 0) {
    drupal_set_message('You have no significant hazards so you cannot continue', 'error', FALSE);
    return $form;
  }

  // Create the fieldset container.
  $form['principle_2_2'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array(
      'class' => array(
        'stage-fieldset',
      ),
    ),
  );

  // Introductory text.
  $form['principle_2_2']['intro'] = array(
    '#prefix' => '<p class="intro">',
    '#suffix' => '</p>',
    '#markup' => t('For each significant hazard you will need apply your chosen decision making process to identify if this step is a CCP.'),
  );

  // Create the table.
  $form['principle_2_2']['instance_table'] = array(
    '#theme' => 'myhaccp_2_2_table',
  );

  // Based on the information in the previous stage, build out the decision tree
  // radios.
  $decision_tree = array_get($previous_data, 'principle_2_1.2_1_1', 'no');
  $tree_type = array_get($previous_data, 'principle_2_1.2_1_1a', FALSE);

  // Build out the rows (three columns).
  foreach ($hazards->getHazardsOverTheshold() as $hazard_key => $hazard) {
    // Prepare the text.
    $step = $hazard->step;
    $process_step_text = '(' . $step->no . ') ' . $step->name;
    // The hazard column text.
    $hazard_text = '<div class="label hazard">' . $hazard->name . '</div><div class="hazard-description">' . nl2br($hazard->description) . '</div>';

    $form['principle_2_2']['instance_table'][$hazard_key]['process_step'] = array(
      '#markup' => $process_step_text,
    );

    $form['principle_2_2']['instance_table'][$hazard_key]['hazard'] = array(
      '#markup' => $hazard_text,
    );

    $form['principle_2_2']['instance_table'][$hazard_key]['control_measure'] = array(
      '#markup' => '<div class="hazard-control-measure">' . nl2br($hazard->controlMeasure) . '</div>',
    );

    if ($decision_tree !== 'no') {
      $num = 1;
      for ($q = 1; $q <= 6; $q++) {
        $id = 'Q' . $num;
        if ($tree_type == 'codex') {
          if ($q == 2) {
            $id = 'Q1a';
            $num = 2;
          }
          else {
            $num++;
          }
          if ($q == 6) {
            // There isn't a question 5 in codex tree so skip this loop.
            continue;
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

        $form['principle_2_2']['instance_table'][$hazard_key]['decision_tree'][$id] = array(
          '#type' => 'radios',
          '#options' => array(
            'yes' => t('Yes'),
            'no' => t('No'),
            'n/a' => t('N/A'),
          ),
          '#title' => $id,
          '#default_value' => array_get($values, "principle_2_2.instance_table.$hazard_key.decision_tree.$id", array()),
          '#attributes' => array(
            'class' => array(
              'question-' . $id,
            ),
            'data-parsley-required' => 'true',
            'data-parsley-error-message' => t('Please indicate \'Yes\', \'No\' or \'N/A\' for this question in the decision tree.'),
          ),
        );
      }

    }
    else {
      $form['principle_2_2']['instance_table'][$hazard_key]['decision_tree'] = array(
        '#type' => 'hidden',
        '#value' => $decision_tree,
      );
    }

    $form['principle_2_2']['instance_table'][$hazard_key]['ccp'] = array(
      '#type' => 'radios',
      '#options' => array(
        'yes' => t('Yes'),
        'no' => t('No'),
      ),
      '#default_value' => array_get($values, "principle_2_2.instance_table.$hazard_key.ccp", array()),
      '#attributes' => array(
        'class' => array(
          'ccp',
        ),
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please indicate whether this process step is a critical control point.'),
      ),
    );
  }

  // Add the validation handler.
  $form['#validate'][] = 'principle_2_2_validate';

  return $form;
}

/**
 * Validation handler for Principle 2 Question 4.
 */
function principle_2_2_validate($form, &$form_state) {
  // Get the dependency injection container.
  global $container;
  // Get the current study.
  $study = $container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  $validator = $stage->getValidator();
  $validator->setFormState($form_state);
  $validator->setForm($form);

  if ($validator->pagerButtonUsed() && $validator->allFieldsAreEmpty()) {
    return;
  }

  $checks = array();

  // Get the data from the previous stage.
  $previous = mforms_get_vals('myhaccp', 'principle_2_1');
  $decision = array_get($previous, 'principle_2_1.2_1_1', 'no') == 'yes' ? TRUE : FALSE;

  // Checks is an array with the key being the element being targeted (in dot
  // notation) and the value being the callback to use to check whether the
  // field is empty.
  $rows = array_get($form_state, 'values.principle_2_2.instance_table', array());
  // Get rid of the hidden decision_tree row as that is needed only for the
  // table theme function.
  unset($rows['decision_tree']);
  // Iterate over each row of the table.
  foreach ($rows as $key => $row) {
    // Within each row there may be multiple elements of a decision tree. There
    // may also be no decision tree.
    $tree = array_get($row, "decision_tree", array());
    if ($decision) {
      foreach ($tree as $id => $element) {
        $checks["principle_2_2.instance_table.$key.decision_tree.$id"] = 'fieldIsNotEmpty';
      }
    }
    // Ensure there is a CCP value.
    $checks["principle_2_2.instance_table.$key.ccp"] = 'fieldIsNotEmpty';
  }

  // Check all the errors.
  foreach ($checks as $target => $method) {
    $validator->validate($method, $target);
  }

  $validator->setErrorMessages();
  $form_state = $validator->getFormState();

}

