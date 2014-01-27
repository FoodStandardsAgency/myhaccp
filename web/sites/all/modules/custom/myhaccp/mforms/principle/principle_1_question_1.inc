<?php

/**
 * Principle 1, Question 1.
 */
function principle_1_question_1(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_1_question_2';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'principle_1_question_1');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  // Set the page title.
  drupal_set_title('Principle 1, question 1: Identify and list potential hazards.');

  $form = array();
  $form['#tree'] = TRUE;
  $form['#attributes']['class'][] = 'principle-1-question-1';

  // Show global message on this form.
  $form['validation_messages'] = array(
    '#type' => 'container',
    '#id' => 'validation-messages',
    '#weight' => -10,
    '#attributes' => array(
      'data-validation-stage' => 'principle_1_question_1',
    ),
  );

  // The wrapper fieldset for the form.
  $form['principle_1_question_1'] = array(
    // Set up the wrapper so that AJAX will be able to replace the fieldset.
    '#prefix' => '<div id="instance-container">',
    '#suffix' => '</div>',
  );

  // Set the number of instances to 1 if not already set.
  if (empty($form_state['num_instances'])) {
    $form_state['num_instances'] = 1;
  }
  for ($i = 0; $i < $form_state['num_instances']; $i++) {
    // Contain everything for this instance inside a fieldset.
    $form['principle_1_question_1']['instance_' . $i] = array(
      '#type' => 'fieldset',
    );
    // Create a wrapper container for the step details.
    $form['principle_1_question_1']['instance_' . $i]['wrapper'] = array(
      '#type' => 'container',
      '#weight' => '-1',
      '#attributes' => array(
        'class' => array('p1q1-step'),
      ),
    );
    // Step no.
    $form['principle_1_question_1']['instance_' . $i]['wrapper']['step_no'] = array(
      '#weight' => '0',
      '#type' => 'textfield',
      '#title' => t('Step no. !tip', array(
        '!tip' => _help_tip(16),
      )),
      '#help_text' => t('Number of process step.'),
      '#default_value' => array_get($values, "principle_1_question_1.instance_$i.wrapper.step_no", FALSE),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-validation-minlength' => 1,
        'data-parsley-error-message' => t('Please add a step number.'),
        'class' => array('step-no'),
      ),
    );
    // Step name.
    $form['principle_1_question_1']['instance_' . $i]['wrapper']['step_name'] = array(
      '#weight' => '1',
      '#type' => 'textfield',
      '#title' => t('Step name !tip', array(
        '!tip' => _help_tip(16),
      )),
      '#help_text' => t('Name of process step.'),
      '#default_value' => array_get($values, "principle_1_question_1.instance_$i.wrapper.step_name", FALSE),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please add a step name.'),
        'class' => array('step-name'),
      ),
    );
    // Add a wrapper for the categories.
    $form['principle_1_question_1']['instance_' . $i]['hazards_wrapper'] = array(
      '#type' => 'container',
      '#weight' => '1',
      '#attributes' => array(
        'class' => array('hazards'),
      ),
    );
    // Markup used as a title for the group.
    $form['principle_1_question_1']['instance_' . $i]['hazards_wrapper']['hazards_title'] = array(
      '#weight' => -10,
     //'#markup' => '<div class="group-title">' . t('List all potential hazards that may be reasonably expected to occur at this process step:  !tip', array(
     //     '!tip' => _help_tip(16),
     //   )) . '</div>',
      '#markup' => '<div class="group-title">' . t('List all potential hazards that may be reasonably expected to occur at this process step:') . '</div>',

    );
    // Biological.
    $form['principle_1_question_1']['instance_' . $i]['hazards_wrapper']['biological'] = array(
      '#weight' => '3',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Biological !tip', array(
        '!tip' => _help_tip(16),
      )),
      '#help_text' => t('List all biological hazards e.g. Salmonella spp., Listeria spp., Norovirus.'),
      '#default_value' => array_get($values, "principle_1_question_1.instance_$i.hazards_wrapper.biological", FALSE),
    );
    // Chemical.
    $form['principle_1_question_1']['instance_' . $i]['hazards_wrapper']['chemical'] = array(
      '#weight' => '4',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Chemical !tip', array(
        '!tip' => _help_tip(16),
      )),
      '#help_text' => t('List all chemical hazards e.g nitrate, patulin, cadmium.'),
      '#default_value' => array_get($values, "principle_1_question_1.instance_$i.hazards_wrapper.chemical", FALSE),
    );
    // Physical.
    $form['principle_1_question_1']['instance_' . $i]['hazards_wrapper']['physical'] = array(
      '#weight' => '5',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Physical !tip', array(
        '!tip' => _help_tip(16),
      )),
      '#help_text' => t('List all physical hazards e.g. stones, metal, wood.'),
      '#default_value' => array_get($values, "principle_1_question_1.instance_$i.hazards_wrapper.physical", FALSE),
    );
    // Allergens.
    $form['principle_1_question_1']['instance_' . $i]['hazards_wrapper']['allergens'] = array(
      '#weight' => '6',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Allergens !tip', array(
        '!tip' => _help_tip(16),
      )),
      '#help_text' => t('List all substances or products that cause allergies or intolerances e.g.  celery, sesame seeds, egg.'),
      '#default_value' => array_get($values, "principle_1_question_1.instance_$i.hazards_wrapper.allergens", FALSE),
    );
  }

  // Add a container for the button controls.
  $form['principle_1_question_1']['controls'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('form-controls'),
    ),
  );

  // Provide an add more button.
  $form['principle_1_question_1']['controls']['add_instance'] = array(
    '#type' => 'submit',
    '#value' => t('Add another step'),
    '#submit' => array('instance_add_more_add_one'),
    '#limit_validation_errors' => TRUE,
    '#ajax' => array(
      'callback' => 'instance_add_more_callback_principle_1_question_1',
      'wrapper' => 'instance-container',
    ),
  );

  // If there are more than two instances in the form then provide a button
  // to remove the last one.
  if ($form_state['num_instances'] > 1) {
    $form['principle_1_question_1']['controls']['remove_instance'] = array(
      '#type' => 'submit',
      '#value' => t('Remove a step'),
      '#submit' => array('instance_add_more_remove_one'),
      '#limit_validation_errors' => TRUE,
      '#ajax' => array(
        'callback' => 'instance_add_more_callback_principle_1_question_1',
        'wrapper' => 'instance-container',
      ),
    );
  }

  // Add a validation handler.
  $form['#validate'][] = 'principle_1_question_1_validate';

  return $form;
}

/**
 * Validation handler for Principle 1 Question 1.
 */
function principle_1_question_1_validate($form, &$form_state) {
  // Bail out if the ajax buttons were used.
  if (isset($form_state['triggering_element']['#limit_validation_errors']) && $form_state['triggering_element']['#limit_validation_errors'] == TRUE) {
    return TRUE;
  }

  $global = array();

  $invalid = array();

  for ($i = 0; $i < $form_state['num_instances']; $i++) {
    // In each instance, check whether some of the fields have been filled in,
    // if they have then check they have all been filled in.

    // Checks is an array with the key being the element being targeted (in dot
    // notation) and the value being the callback to use to check whether the
    // field is empty.
    $checks = array(
      "principle_1_question_1.instance_$i.hazards_wrapper.biological" => '_text_field_is_empty',
      "principle_1_question_1.instance_$i.hazards_wrapper.physical" => '_text_field_is_empty',
      "principle_1_question_1.instance_$i.hazards_wrapper.allergens" => '_text_field_is_empty',
      "principle_1_question_1.instance_$i.hazards_wrapper.chemical" => '_text_field_is_empty',
    );

    $invalid_hazards = array();
    $invalid_steps = array();

    foreach ($checks as $target => $callback) {
      $invalid_hazards[] = _check_validation($callback, $target, $form, $form_state, TRUE);
    }

    // Check the step no and name fields.
    $checks = array(
      "principle_1_question_1.instance_$i.wrapper.step_no" => '_text_field_is_empty',
      "principle_1_question_1.instance_$i.wrapper.step_name" => '_text_field_is_empty',
    );

    foreach ($checks as $target => $callback) {
      $invalid_steps[] = _check_validation($callback, $target, $form, $form_state, TRUE);
    }

    // Display the normal validation messages for the step number and name.
    foreach ($checks as $target => $callback) {
      $invalid[] = _check_validation($callback, $target, $form, $form_state);
    }

    if (!in_array(FALSE, $invalid_hazards)) {
      $message = t('Please add at least one hazard.');
      $global[] = $message;
      $invalid[] = TRUE;
    }

    if (!in_array(FALSE, $invalid_steps)) {
      $message = t('Steps must have a step number and a step name.');
      $global[] = $message;
      $invalid[] = TRUE;
    }
  }

  if (!empty($global)) {
    myhacpp_prepare_validation('global', array('principle_1_question_1' => $global), $form_state);
  }

  // Do some normal checks with error messages on the step no and step name
  // fields.
  $checks = array(
    "principle_1_question_1.instance_0.wrapper.step_no" => '_text_field_is_empty',
    "principle_1_question_1.instance_0.wrapper.step_name" => '_text_field_is_empty',
  );

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

/**
 * Ajax callback which returns the form array element to be applied against.
 */
function instance_add_more_callback_principle_1_question_1($form, $form_state) {
  return $form['principle_1_question_1'];
}
