<?php

function preparatory_d(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_e';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  drupal_set_title('Preparatory Stage D: Select the team');

  $form = array();
  $form['#tree'] = TRUE;
  $form['#attributes']['class'][] = 'pd';

  // Wrap the form section in a fieldset.
  $form['container'] = array(
    '#type' => 'fieldset',
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
    $form['container']["instance_$i"] = array(
      '#type' => 'fieldset',
    );
    // Team member name.
    $form['container']["instance_$i"]['team_name'] = array(
      '#weight' => '0',
      '#type' => 'textfield',
      '#title' => t('Name of HACCP Team Member !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => array_get($values, "container.instance_$i.team_name", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add the name of the team member.'),
        'data-parsley-required' => TRUE,
      ),
    );
    // Team member external.
    $form['container']["instance_$i"]['team_external'] = array(
      '#weight' => '1',
      '#type' => 'select',
      '#title' => t('Location of team member !tip', array(
        '!tip' => _help_tip(),
      )),
      '#options' => array(
        'internal' => t('Internal'),
        'external' => t('External'),
      ),
      '#default_value' => array_get($values, "container.instance_$i.team_external", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add the name of the team member.'),
        'data-parsley-required' => TRUE,
      ),
    );
    // Team member role.
    $form['container']["instance_$i"]['team_role'] = array(
      '#weight' => '2',
      '#type' => 'textfield',
      '#title' => t('Role within the team !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => array_get($values, "container.instance_$i.team_role", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add the role of the team member.'),
        'data-parsley-required' => TRUE,
      ),
    );
    // Team member training.
    $form['container']["instance_$i"]['team_training'] = array(
      '#weight' => '3',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Relevant training !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => array_get($values, "container.instance_$i.team_training", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add the training of the team member.'),
        'data-parsley-required' => TRUE,
      ),
    );
    // Team member training.
    $form['container']["instance_$i"]['team_qualifications'] = array(
      '#weight' => '4',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Qualifications !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => array_get($values, "container.instance_$i.team_qualifications", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add the qualifications of the team member.'),
        'data-parsley-required' => TRUE,
      ),
    );
    // Team member experience.
    $form['container']["instance_$i"]['team_experience'] = array(
      '#weight' => '5',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('List relevant experience !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => array_get($values, "container.instance_$i.team_experience", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add the experience of the team member.'),
        'data-parsley-required' => TRUE,
      ),
    );
  }

  // First instance of the team role field should have a default value and for
  // it to be un-editable (enforced).
  $form['container']['instance_0']['team_role']['#default_value'] = t('Team leader');
  $form['container']['instance_0']['team_role']['#disabled'] = TRUE;
  $form['container']['instance_0']['team_external']['#access'] = FALSE;

  $form['container']['team_skills'] = array(
    '#type' => 'radios',
    '#weight' => 10,
    '#options' => array(
      'Yes' => t('Yes'),
      'No' => t('No'),
    ),
    '#title' => t('Do you consider the team to have sufficient skills (scientific/technical knowledge and HACCP expertise) to ensure the HACCP study will be effective? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.team_skills', FALSE),
  );

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
  $form['#validate'][] = 'preparatory_d_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_d_validate($form, &$form_state) {
  // Assume this form is valid.
  $invalid = FALSE;
  $values = $form_state['values'];

  for ($i = 0; $i < $form_state['num_instances']; $i++) {
    // In each instance, check whether some of the fields have been filled in,
    // if they have then check they have all been filled in.
    $checks = array(
      "container[instance_$i][team_name]" => "container.instance_$i.team_name",
      "container[instance_$i][team_role]" => "container.instance_$i.team_role",
      "container[instance_$i][team_training]" => "container.instance_$i.team_training",
      "container[instance_$i][team_qualifications]" => "container.instance_$i.team_qualifications",
      "container[instance_$i][team_experience]" => "container.instance_$i.team_experience",
    );
    // Iterate through all the field checks and if we get any FALSE returns it
    // means we have some content in a field. This will no longer invalidate the
    // form.
    $field_count = 0;
    foreach ($checks as $name => $path) {
      if (_text_field_is_empty($values, $path) == FALSE) {
        $field_count++;
      }
      else {
        $field_errors[$name] = $path;
      }
    }
    // Now check if there is some content but not all the content.
    if ($field_count > 0 && $field_count < 5) {
      // Check each field and highlight the error fields.
      foreach ($field_errors as $name => $path) {
        $element = array_get($form, $path);
        myhacpp_prepare_validation($name, $element['#attributes']['data-parsley-error-message'], $form_state);
      }
      $invalid = TRUE;
    }
  }

  // Check to see whether we have failed validation and therefore should store
  // it in the database or whether we have passed and therefore clear validation
  // errors.
  if ($invalid == FALSE) {
    // Remove any stored validation.
    myhaccp_clear_validation($form_state);
  }
}
