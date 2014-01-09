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
  $data = mforms_get_vals('myhaccp');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  if (!empty($data)) {
    $values = $data;
  }
  elseif (isset($form_state['values'])) {
    $values = $form_state['values'];
  }

  // Set the page title.
  drupal_set_title('Principle 1, question 1:
Identify and list potential hazards.');

  $form = array();
  $form['#tree'] = TRUE;
  $form['#attributes']['class'][] = 'p1q1';

  // The wrapper fieldset for the form.
  $form['container'] = array(
    // Set up the wrapper so that AJAX will be able to replace the fieldset.
    '#prefix' => '<div id="instance-container">',
    '#suffix' => '</div>',
  );

  // Check whether the number of instances has been set and if so show them,
  // otherwise show 2. If instances has been set but there is only 1 then show a
  // second (blank) one.
  if (empty($form_state['num_instances']) || $form_state['num_instances'] == 1) {
    $form_state['num_instances'] = 2;
  }
  for ($i = 0; $i < $form_state['num_instances']; $i++) {
    // Contain everything for this instance inside a fieldset.
    $form['container']['instance_' . $i] = array(
      '#type' => 'fieldset',
    );
    // Create a wrapper container for the step details.
    $form['container']['instance_' . $i]['p1q1_step_wrapper'] = array(
      '#type' => 'container',
      '#weight' => '-1',
      '#attributes' => array(
        'class' => array('p1q1-step'),
      ),
    );
    $form['container']['instance_' . $i]['p1q1_step_wrapper']['p1q1_step_no'] = array(
      '#weight' => '0',
      '#type' => 'textfield',
      '#title' => t('Step no. !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => isset($values['container']['instance_' . $i]['p1q1_step_wrapper']['p1q1_step_no']) ? $values['container']['instance_' . $i]['p1q1_step_wrapper']['p1q1_step_no'] : NULL
    );
    // Step name.
    $form['container']['instance_' . $i]['p1q1_step_wrapper']['p1q1_step_name'] = array(
      '#weight' => '1',
      '#type' => 'textfield',
      '#title' => t('Step name !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => isset($values['container']['instance_' . $i]['p1q1_step_wrapper']['p1q1_step_name']) ? $values['container']['instance_' . $i]['p1q1_step_wrapper']['p1q1_step_name'] : NULL
    );
    // Add a wrapper for the categories.
    $form['container']['instance_' . $i]['p1q1_hazards_wrapper'] = array(
      '#type' => 'container',
      '#weight' => '1',
      '#attributes' => array(
        'class' => array('p1q1-hazards'),
      ),
    );
    // Markup used as a title for the group.
    $form['container']['instance_' . $i]['p1q1_hazards_wrapper']['hazards_title'] = array(
      '#weight' => -10,
      '#markup' => '<div class="group-title">' . t('List all potential hazards that may be reasonably expected to occur at this process step:  !tip', array(
          '!tip' => _help_tip(),
        )) . '</div>',
    );
    // Biological.
    $form['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_biological'] = array(
      '#weight' => '3',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Biological !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => isset($values['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_biological']) ? $values['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_biological'] : NULL
    );
    // Chemical.
    $form['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_chemical'] = array(
      '#weight' => '4',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Chemical !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => isset($values['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_chemical']) ? $values['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_chemical'] : NULL
    );
    // Physical.
    $form['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_physical'] = array(
      '#weight' => '5',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Physical !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => isset($values['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_physical']) ? $values['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_physical'] : NULL
    );
    // Allergens.
    $form['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_allergens'] = array(
      '#weight' => '6',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Allergens !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => isset($values['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_allergens']) ? $values['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_allergens'] : NULL
    );
  }

  // Add a container for the button controls.
  $form['container']['controls'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('form-controls'),
    ),
  );

  // Provide an add more button.
  $form['container']['controls']['add_instance'] = array(
    '#type' => 'submit',
    '#value' => t('Add another'),
    '#submit' => array('instance_add_more_add_one'),
    '#limit_validation_errors' => TRUE,
    '#ajax' => array(
      'callback' => 'instance_add_more_callback',
      'wrapper' => 'instance-container',
    ),
  );

  // If there are more than two instances in the form then provide a button
  // to remove the last one.
  if ($form_state['num_instances'] > 2) {
    $form['container']['controls']['remove_instance'] = array(
      '#type' => 'submit',
      '#value' => t('Remove one'),
      '#submit' => array('instance_add_more_remove_one'),
      '#limit_validation_errors' => TRUE,
      '#ajax' => array(
        'callback' => 'instance_add_more_callback',
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
  $validate = FALSE;

  // Test to see whether there is any submitted data in any instance.
  foreach ($form_state['values']['container'] as &$instance) {
    foreach ($instance as &$container) {
      if (is_array($container)) {
        foreach ($container as &$element) {
          if ($element != '') {
            $validate = TRUE;
          }
        }
      }
    }
  }

  // Determine which message to show.
  if ($validate == FALSE) {
    drupal_set_message(t('Principle 1 Question 1 requires information to be present.'), 'warning');
  }
  else {
    drupal_set_message(t('Information saved.'));
  }
}
