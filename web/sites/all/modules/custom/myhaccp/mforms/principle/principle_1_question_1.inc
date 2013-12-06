<?php

/**
 * Principle 1, Question 1.
 */
function _principle_1_question_1(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_1_question_2';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  if (!empty($data)) {
    $vals = $data;
  }
  elseif (isset($form_state['values'])) {
    $vals = $form_state['values'];
  }

  // Set the page title.
  drupal_set_title('Principle 1 Question 1');

  $form = array();
  $form['#tree'] = TRUE;
  $form['#attributes']['class'][] = 'p1q1';

  // The wrapper fieldset for the form.
  $form['container'] = array(
    // Set up the wrapper so that AJAX will be able to replace the fieldset.
    '#prefix' => '<div id="instance-container">',
    '#suffix' => '</div>',
  );

  if (empty($form_state['num_instances'])) {
    $form_state['num_instances'] = 1;
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
      '#default_value' => isset($vals['container']['instance_' . $i]['p1q1_step_wrapper']['p1q1_step_no']) ? $vals['container']['instance_' . $i]['p1q1_step_wrapper']['p1q1_step_no'] : NULL
    );
    // Step name.
    $form['container']['instance_' . $i]['p1q1_step_wrapper']['p1q1_step_name'] = array(
      '#weight' => '1',
      '#type' => 'textfield',
      '#title' => t('Step name !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => isset($vals['container']['instance_' . $i]['p1q1_step_wrapper']['p1q1_step_name']) ? $vals['container']['instance_' . $i]['p1q1_step_wrapper']['p1q1_step_name'] : NULL
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
      '#default_value' => isset($vals['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_biological']) ? $vals['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_biological'] : NULL
    );
    // Chemical.
    $form['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_chemical'] = array(
      '#weight' => '4',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Chemical !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => isset($vals['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_chemical']) ? $vals['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_chemical'] : NULL
    );
    // Physical.
    $form['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_physical'] = array(
      '#weight' => '5',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Physical !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => isset($vals['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_physical']) ? $vals['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_physical'] : NULL
    );
    // Allergens.
    $form['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_allergens'] = array(
      '#weight' => '6',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Allergens !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => isset($vals['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_allergens']) ? $vals['container']['instance_' . $i]['p1q1_hazards_wrapper']['p1q1_allergens'] : NULL
    );
  }

  $form['container']['controls'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('form-controls'),
    ),
  );

  $form['container']['controls']['add_instance'] = array(
    '#type' => 'submit',
    '#value' => t('Add another'),
    '#submit' => array('instance_add_more_add_one'),
    '#limit_validation_errors' => TRUE,
    '#ajax' => array(
      'callback' => 'instance_add_more_callback',
      'wrapper' => 'instance_container',
    ),
  );
  if ($form_state['num_instances'] > 1) {
    $form['container']['controls']['remove_instance'] = array(
      '#type' => 'submit',
      '#value' => t('Remove one'),
      '#submit' => array('instance_add_more_remove_one'),
      '#limit_validation_errors' => TRUE,
      '#ajax' => array(
        'callback' => 'instance_add_more_callback',
        'wrapper' => 'instance_container',
      ),
    );
  }

  $form['#validate'][] = '_principle_1_question_1_validate';

  return $form;
}

