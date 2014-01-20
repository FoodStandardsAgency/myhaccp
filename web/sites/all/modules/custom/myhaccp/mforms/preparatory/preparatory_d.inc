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
  $form['#attributes']['class'][] = 'prep-d';

  // Wrap the form section in a fieldset.
  $form['prep_d'] = array(
    '#type' => 'fieldset',
    '#prefix' => '<div id="container">',
    '#suffix' => '</div>',
  );

  // Check whether the number of instances has been set and if so show them,
  // otherwise show 2. If instances has been set but there is only 1 then show a
  // second (blank) one.
  if (empty($form_state['num_instances'])) {
    $form_state['num_instances'] = 1;
  }
  for ($i = 0; $i < $form_state['num_instances']; $i++) {
    // Contain everything for this instance inside a fieldset.
    $form['prep_d']["instance_$i"] = array(
      '#type' => 'fieldset',
      '#attributes' => array(
        'class' => array('instance'),
      ),
    );
    // Team member name.
    $form['prep_d']["instance_$i"]['team_name'] = array(
      '#weight' => '0',
      '#type' => 'textfield',
      '#title' => t('Name of HACCP team member: !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => array_get($values, "prep_d.instance_$i.team_name", FALSE),
      '#help_text' => t('State how the product should be kept  (during storage and distribution of the product) e.g. product to be kept chilled, frozen or heated.'),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add the name of the HACCP team member.'),
        'data-parsley-required' => TRUE,
      ),
    );
    // Team member external.
    $form['prep_d']["instance_$i"]['team_external'] = array(
      '#weight' => '1',
      '#type' => 'radios',
      '#options' => array(
        'internal' => t('Internal'),
        'external' => t('External'),
      ),
      '#attributes' => array(
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please state whether the team member is internal or external.'),
      ),
      '#title' => t('Location of team member !tip', array(
        '!tip' => _help_tip(),
      )),

      '#default_value' => array_get($values, "prep_d.instance_$i.team_external", FALSE),
    );
    // Team member role.
    $form['prep_d']["instance_$i"]['team_role'] = array(
      '#weight' => '2',
      '#type' => 'textfield',
      '#title' => t('Role of individual !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => array_get($values, "prep_d.instance_$i.team_role", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add the role of the individual.'),
        'data-parsley-required' => TRUE,
      ),
    );
    $form['prep_d']["instance_$i"]['wrapper'] = array(
      '#type' => 'container',
      '#weight' => '3',
    );
    // Team member training.
    $form['prep_d']["instance_$i"]['wrapper']['team_training'] = array(
      '#weight' => '1',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Relevant training !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => array_get($values, "prep_d.instance_$i.wrapper.team_training", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add any relevant training or enter "none".'),
        'data-parsley-required' => TRUE,
      ),
    );
    // Team member training.
    $form['prep_d']["instance_$i"]['wrapper']['team_qualifications'] = array(
      '#weight' => '2',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Qualifications !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => array_get($values, "prep_d.instance_$i.wrapper.team_qualifications", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add any relevant qualifications or enter "none".'),
        'data-parsley-required' => TRUE,
      ),
    );
    // Team member experience.
    $form['prep_d']["instance_$i"]['wrapper']['team_experience'] = array(
      '#weight' => '3',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('List relevant experience !tip', array(
        '!tip' => _help_tip(),
      )),
      '#default_value' => array_get($values, "prep_d.instance_$i.wrapper.team_experience", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add any relevant experience or enter "none".'),
        'data-parsley-required' => TRUE,
      ),
    );
  }

  // First instance of the team role field should have a default value and for
  // it to be un-editable (enforced).
  $form['prep_d']['instance_0']['team_role']['#default_value'] = t('Team leader');
  $form['prep_d']['instance_0']['team_role']['#disabled'] = TRUE;
  $form['prep_d']['instance_0']['team_external']['#disabled'] = TRUE;
  $form['prep_d']['instance_0']['team_external']['#default_value'] = 'internal';
  $form['prep_d']['instance_0']['team_name']['#title'] = t('Name of HACCP lead for business');

  $form['prep_d']['team_skills'] = array(
    '#type' => 'radios',
    '#weight' => 10,
    '#options' => array(
      'Yes' => t('Yes'),
      'No' => t('No'),
    ),
    '#title' => t('Do you consider the team to have sufficient skills (scientific/technical knowledge and HACCP expertise) to ensure the HACCP study will be effective? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'prep_d.team_skills', FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('Please indicate whether you consider the team to have sufficient skills.'),
      'data-parsley-required' => TRUE,
    ),
  );

  // Add a prep_d for the button controls.
  $form['prep_d']['controls'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('form-controls'),
    ),
  );

  // Provide an add more button.
  $form['prep_d']['controls']['add_instance'] = array(
    '#type' => 'submit',
    '#value' => t('Add another team member'),
    '#submit' => array('instance_add_more_add_one'),
    '#limit_validation_errors' => TRUE,
    '#ajax' => array(
      'callback' => 'instance_add_more_callback_prep_d',
      'wrapper' => 'container',
    ),
  );

  // If there are more than two instances in the form then provide a button
  // to remove the last one.
  if ($form_state['num_instances'] > 1) {
    $form['prep_d']['controls']['remove_instance'] = array(
      '#type' => 'submit',
      '#value' => t('Remove one'),
      '#submit' => array('instance_add_more_remove_one'),
      '#limit_validation_errors' => TRUE,
      '#ajax' => array(
        'callback' => 'instance_add_more_callback_prep_d',
        'wrapper' => 'container',
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
  $invalid = array();

  for ($i = 0; $i < $form_state['num_instances']; $i++) {
    // In each instance, check whether some of the fields have been filled in,
    // if they have then check they have all been filled in.

    // Checks is an array with the key being the element being targeted (in dot
    // notation) and the value being the callback to use to check whether the
    // field is empty.
    $checks = array(
      "prep_d.instance_$i.team_external" => '_radios_field_is_empty',
      "prep_d.instance_$i.team_name" => '_text_field_is_empty',
      "prep_d.instance_$i.team_role" => '_text_field_is_empty',
      "prep_d.instance_$i.wrapper.team_training" => '_text_field_is_empty',
      "prep_d.instance_$i.wrapper.team_qualifications" => '_text_field_is_empty',
      "prep_d.instance_$i.wrapper.team_experience" => '_text_field_is_empty',
    );

    foreach ($checks as $target => $callback) {
      $invalid[] = _check_validation($callback, $target, $form, $form_state);
    }

  }

  $invalid[] = _check_validation('_radios_field_is_empty', 'prep_d.team_skills', $form, $form_state);

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
function instance_add_more_callback_prep_d($form, $form_state) {
  return $form['prep_d'];
}
