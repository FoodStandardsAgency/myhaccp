<?php

/**
 * Principle 1, Question 1.
 */
function principle_1_1(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_1_2';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'principle_1_1');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  // Get the dependency injection container.
  global $container;
  // Get the current study.
  $study = $container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  drupal_set_title($stage->title, PASS_THROUGH);

  $form = array();
  $form['#tree'] = TRUE;
  $form['#attributes']['class'][] = 'principle-1-question-1';

  // The wrapper fieldset for the form.
  $form['principle_1_1'] = array(
    // Set up the wrapper so that AJAX will be able to replace the fieldset.
    '#prefix' => '<div id="instance-container">',
    '#suffix' => '</div>',
  );

  // Introductory text.
  $form['principle_1_1']['intro'] = array(
    '#prefix' => '<p class="intro">',
    '#suffix' => '</p>',
    '#markup' => t('Potential hazards include all hazards (biological, chemical, physical and allergens) that may be reasonably expected to occur at a particular process step.'),
  );

  // Set the number of instances to 1 if not already set.
  if (empty($values['principle_1_1']) && empty($form_state['num_instances'])) {
    $form_state['num_instances'] = 1;
  }
  elseif (principle_1_1_triggering_element_check($form_state)) {
    // This is the ajax trigger.
    $form_state['num_instances'] = $form_state['num_instances'];
  }
  else {
    // Get the number of instances from the saved form data.
    unset($values['principle_1_1']['controls']);
    $form_state['num_instances'] = count($values['principle_1_1']);
  }

  for ($i = 0; $i < $form_state['num_instances']; $i++) {
    // Contain everything for this instance inside a fieldset.
    $form['principle_1_1']['instance_' . $i] = array(
      '#type' => 'fieldset',
    );
    // Create a wrapper container for the step details.
    $form['principle_1_1']['instance_' . $i]['wrapper'] = array(
      '#type' => 'container',
      '#weight' => '-1',
      '#attributes' => array(
        'class' => array('p1q1-step'),
      ),
    );

    $form['principle_1_1']['instance_' . $i]['wrapper']['step_intro'] = array(
      '#prefix' => '<div class="group-title">',
      '#suffix' => '</div>',
      '#markup' => t('Enter the process step number and name.'),
    );

    // Step no.
    $form['principle_1_1']['instance_' . $i]['wrapper']['step_no'] = array(
      '#weight' => '0',
      '#type' => 'textfield',
      '#title' => t('Step no.'),
      '#help_link' => 16,
      '#help_text' => t('Number of process step.'),
      '#default_value' => array_get($values, "principle_1_1.instance_$i.wrapper.step_no", FALSE),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-validation-minlength' => 1,
        'data-parsley-error-message' => t('Please add a step number.'),
        'class' => array('step-no'),
      ),
    );
    // Step name.
    $form['principle_1_1']['instance_' . $i]['wrapper']['step_name'] = array(
      '#weight' => '1',
      '#type' => 'textfield',
      '#title' => t('Step name'),
      '#help_link' => 16,
      '#help_text' => t('Name of process step.'),
      '#default_value' => array_get($values, "principle_1_1.instance_$i.wrapper.step_name", FALSE),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please add a step name.'),
        'class' => array('step-name'),
      ),
    );
    // Add a wrapper for the categories.
    $form['principle_1_1']['instance_' . $i]['hazards_wrapper'] = array(
      '#type' => 'container',
      '#weight' => '1',
      '#attributes' => array(
        'class' => array('hazards'),
      ),
    );
    // Markup used as a title for the group.
    $form['principle_1_1']['instance_' . $i]['hazards_wrapper']['hazards_title'] = array(
      '#weight' => -10,
      '#markup' => '<div class="group-title">' . t('List all potential hazards that may be reasonably expected to occur at this process step. In the text boxes below, please list each hazard on a new line.') . '</div>',

    );
    // Biological.
    $form['principle_1_1']['instance_' . $i]['hazards_wrapper']['biological'] = array(
      '#weight' => '3',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Biological'),
      '#help_link' => 16,
      '#help_text' => t('List all biological hazards with each hazard on a new line, e.g.<br/>Salmonella spp.<br/>Listeria spp.<br/>Norovirus'),
      '#default_value' => array_get($values, "principle_1_1.instance_$i.hazards_wrapper.biological", FALSE),
    );
    // Chemical.
    $form['principle_1_1']['instance_' . $i]['hazards_wrapper']['chemical'] = array(
      '#weight' => '4',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Chemical'),
      '#help_link' => 16,
      '#help_text' => t('List all chemical hazards with each hazard on a new line, e.g.<br/>nitrate<br/>patulin<br/>cadmium'),
      '#default_value' => array_get($values, "principle_1_1.instance_$i.hazards_wrapper.chemical", FALSE),
    );
    // Physical.
    $form['principle_1_1']['instance_' . $i]['hazards_wrapper']['physical'] = array(
      '#weight' => '5',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Physical'),
      '#help_link' => 16,
      '#help_text' => t('List all physical hazards, with each hazard on a new line, e.g.<br/>stones<br/>metal<br/>wood'),
      '#default_value' => array_get($values, "principle_1_1.instance_$i.hazards_wrapper.physical", FALSE),
    );
    // Allergens.
    $form['principle_1_1']['instance_' . $i]['hazards_wrapper']['allergens'] = array(
      '#weight' => '6',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Allergens'),
      '#help_link' => 16,
      '#help_text' => t('List all substances or products that cause allergies or intolerances, with each hazard on a new line, e.g.<br/>celery<br/>sesame seeds<br/>egg'),
      '#default_value' => array_get($values, "principle_1_1.instance_$i.hazards_wrapper.allergens", FALSE),
    );
  }

  // Add a container for the button controls.
  $form['principle_1_1']['controls'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('form-controls'),
    ),
  );

  // Provide an add more button.
  $form['principle_1_1']['controls']['add_instance'] = array(
    '#type' => 'submit',
    '#value' => t('Add another step'),
    '#submit' => array('instance_add_more_add_one'),
    '#limit_validation_errors' => array(),
    '#ajax' => array(
      'callback' => 'instance_add_more_callback_principle_1_1',
      'wrapper' => 'instance-container',
    ),
  );

  // If there are more than two instances in the form then provide a button
  // to remove the last one.
  if ($form_state['num_instances'] > 1) {
    $form['principle_1_1']['controls']['remove_instance'] = array(
      '#type' => 'submit',
      '#value' => t('Remove a step'),
      '#submit' => array('instance_add_more_remove_one'),
      '#limit_validation_errors' => array(),
      '#ajax' => array(
        'callback' => 'instance_add_more_callback_principle_1_1',
        'wrapper' => 'instance-container',
      ),
    );
  }

  // Add a validation handler.
  $form['#validate'][] = 'principle_1_1_validate';

  return $form;
}

/**
 * Validation handler for Principle 1 Question 1.
 */
function principle_1_1_validate($form, &$form_state) {
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

  // Bail out if the ajax buttons were used.
  if (principle_1_1_triggering_element_check($form_state)) {
    return TRUE;
  }

  // Do some normal checks with error messages on the step no and step name
  // fields.
  $checks = array(
    "principle_1_1.instance_0.wrapper.step_no" => 'fieldIsNotEmpty',
    "principle_1_1.instance_0.wrapper.step_name" => 'fieldIsNotEmpty',
  );

  foreach ($checks as $target => $method) {
    $validator->validate($method, $target);
  }

  $messages = array();

  for ($i = 0; $i < $form_state['num_instances']; $i++) {
    // In each instance, check whether some of the fields have been filled in,
    // if they have then check they have all been filled in.
    $invalid_hazards = array();
    $invalid_steps = array();

    // Checks is an array with the key being the element being targeted (in dot
    // notation) and the value being the callback to use to check whether the
    // field is empty.
    $checks = array(
      "principle_1_1.instance_$i.hazards_wrapper.biological" => 'fieldIsNotEmpty',
      "principle_1_1.instance_$i.hazards_wrapper.physical" => 'fieldIsNotEmpty',
      "principle_1_1.instance_$i.hazards_wrapper.allergens" => 'fieldIsNotEmpty',
      "principle_1_1.instance_$i.hazards_wrapper.chemical" => 'fieldIsNotEmpty',
    );

    foreach ($checks as $target => $method) {
      $validation = new Validation($form, $form_state, $target);
      $invalid_hazards[] = $validation->$method();
    }

    if (!in_array(TRUE, $invalid_hazards)) {
      $message = t('Please add at least one hazard.');
      $messages['hazards'] = $message;
      $validator->passed = FALSE;
    }

    // Check the step no and name fields.
    $checks = array(
      "principle_1_1.instance_$i.wrapper.step_no" => 'fieldIsNotEmpty',
      "principle_1_1.instance_$i.wrapper.step_name" => 'fieldIsNotEmpty',
    );

    foreach ($checks as $target => $method) {
      $validation = new Validation($form, $form_state, $target);
      $invalid_steps[] = $validation->$method();
    }

    if (!in_array(TRUE, $invalid_steps)) {
      $message = t('Steps must have a step number and a step name.');
      $messages["principle_1_1.instance_$i.wrapper"] = $message;
      $validator->passed = FALSE;
    }
  }

//
//    if (!$evidence->fieldIsNotEmpty() && !$support->fieldIsNotEmpty()) {
//      $messages = array(
//        'validation_messages' => array(t('Please choose at least one option in question 1 or add some content in question 2.')),
//      );
//      $validator->passed = FALSE;
//      $validator->setErrorMessages(($messages));
//    }


  $validator->setErrorMessages((array('validation_messages' => $messages)));
  $form_state = $validator->getFormState();

}

/**
 * Ajax callback which returns the form array element to be applied against.
 */
function instance_add_more_callback_principle_1_1($form, $form_state) {
  return $form['principle_1_1'];
}

/**
 * Check whether the step buttons have been clicked.
 */
function principle_1_1_triggering_element_check($form_state) {
  if (isset($form_state['triggering_element']['#value'])) {
    if ($form_state['triggering_element']['#value'] == 'Remove a step' || $form_state['triggering_element']['#value'] == 'Add another step') {
      return TRUE;
    }
  }
  return FALSE;
}
