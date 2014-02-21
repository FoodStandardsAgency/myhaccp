<?php

function preparatory_d(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_e';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'preparatory_d');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  $stages = new Stages();
  $stage = $stages->getStage(__FUNCTION__);
  drupal_set_title($stage->title, PASS_THROUGH);

  $form = array();
  $form['#tree'] = TRUE;
  $form['#attributes']['class'][] = 'prep-d';

  // Wrap the form section in a fieldset.
  $form['preparatory_d'] = array(
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
    $form['preparatory_d']["instance_$i"] = array(
      '#type' => 'fieldset',
      '#attributes' => array(
        'class' => array('instance'),
      ),
    );
    // 1. Team member name.
    $form['preparatory_d']["instance_$i"]['d_1'] = array(
      '#weight' => '0',
      '#type' => 'textfield',
      '#title' => t('Name of HACCP team member:'),
      '#help_link' => 21,
      '#default_value' => array_get($values, "preparatory_d.instance_$i.d_1", FALSE),
      '#help_text' => t("State the person's name."),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add the name of the HACCP team member.'),
        'data-parsley-required' => TRUE,
      ),
    );
    // 2. Team member external.
    $form['preparatory_d']["instance_$i"]['d_2'] = array(
      '#weight' => '1',
      '#type' => 'select',
      '#options' => array(
        '0' => t('-- Please select --'),
        'internal' => t('Internal'),
        'external' => t('External'),
      ),
      '#attributes' => array(
        'data-parsley-notequal' => '0',
        'data-parsley-required' => 'true',
        'data-parsley-error-message' => t('Please indicate if this person is internal (works at the company) or external (eg an external consultant).'),
      ),
      '#title' => t('Is this person Internal or External to the company?'),
      '#help_link' => 21,
      '#help_text' => t("State if the person is an employee of the company (internal) or not (external)."),
      '#default_value' => array_get($values, "preparatory_d.instance_$i.d_2", FALSE),
    );

    // 3. Team member role.
    $form['preparatory_d']["instance_$i"]['d_3'] = array(
      '#weight' => '2',
      '#type' => 'textfield',
      '#title' => t('What is the role of this individual in the HACCP team?'),
      '#help_link' => 21,
      '#help_text' => t("For example, QA Manager to provide technical expertise, Consultant to provide knowledge of HACCP and expertise from a chemical and biological hazard perspective."),
      '#default_value' => array_get($values, "preparatory_d.instance_$i.d_3", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add the role of the individual.'),
        'data-parsley-required' => TRUE,
      ),
    );
    $form['preparatory_d']["instance_$i"]['wrapper'] = array(
      '#type' => 'container',
      '#weight' => '3',
    );

    // 4. Team member training.
    $form['preparatory_d']["instance_$i"]['wrapper']['d_4'] = array(
      '#weight' => '1',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Relevant training'),
      '#help_link' => 21,
      '#help_text' => t("What training has this person undertaken that is specific to the support they can provide e.g HACCP (state level), Food safety (state level), Internal auditing."),
      '#default_value' => array_get($values, "preparatory_d.instance_$i.wrapper.d_4", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add any relevant training or enter "none".'),
        'data-parsley-required' => TRUE,
      ),
    );
    // 5. Team member qualifications.
    $form['preparatory_d']["instance_$i"]['wrapper']['d_5'] = array(
      '#weight' => '2',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Qualifications'),
      '#help_link' => 21,
      '#help_text' => t("Provide details of their qualifications e.g. BSc Biochemistry, CIEH Intermediate food safety, MSc  Food Science, Management and Hygiene."),
      '#default_value' => array_get($values, "preparatory_d.instance_$i.wrapper.d_5", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add any relevant qualifications or enter "none".'),
        'data-parsley-required' => TRUE,
      ),
    );
    // 6. Team member experience.
    $form['preparatory_d']["instance_$i"]['wrapper']['d_6'] = array(
      '#weight' => '3',
      '#type' => 'textarea',
      '#resizable' => FALSE,
      '#title' => t('Relevant experience'),
      '#help_link' => 21,
      '#help_text' => t("Detail only that experience that is applicable to their involvement with the HACCP study e.g. 1 year as a chemical hazard scientist, 2 years working with the customer complaints team."),
      '#default_value' => array_get($values, "preparatory_d.instance_$i.wrapper.d_6", FALSE),
      '#attributes' => array(
        'data-parsley-error-message' => t('Please add any relevant experience or enter "none".'),
        'data-parsley-required' => TRUE,
      ),
    );
  }

  // First instance of the team role field should have a default value and for
  // it to be un-editable (enforced).
  $form['preparatory_d']['instance_0']['d_3']['#default_value'] = t('HACCP Lead');
  $form['preparatory_d']['instance_0']['d_3']['#access'] = FALSE;
  $form['preparatory_d']['instance_0']['d_3']['#help_text'] = t("The first person identified here should be the HACCP Lead, so this field is pre-completed to read 'HACCP Lead'.");
  $form['preparatory_d']['instance_0']['d_2']['#access'] = FALSE;
  $form['preparatory_d']['instance_0']['d_2']['#default_value'] = 'internal';
  $form['preparatory_d']['instance_0']['d_2']['#help_text'] = t("The HACCP Lead should be an employee of the company, so this option is pre-selected to be 'Internal'.");
  $form['preparatory_d']['instance_0']['d_1']['#title'] = t('Name of HACCP lead for business:');
  $form['preparatory_d']['instance_0']['d_1']['#attributes']['data-parsley-error-message'] = t('Please add the name of the HACCP lead for the business.');
  $form['preparatory_d']['instance_0']['d_1']['#help_text'] = t("State the person's name.");


  // Do you consider the team to have sufficient skills?
  $form['preparatory_d']['team_skills'] = array(
    '#type' => 'radios',
    '#weight' => 10,
    '#options' => array(
      'Yes' => t('Yes'),
      'No' => t('No'),
    ),
    '#title' => t('Do you consider the team to have sufficient skills (scientific/technical knowledge and HACCP expertise) to ensure the HACCP study will be effective?'),
    '#help_link' => 21,
    '#help_text' => t("In your opinion as leader of the HACCP team, state whether you consider that you have the necessary skills to enable an effective HACCP study to be carried out and maintained on an ongoing basis?"),
    '#default_value' => array_get($values, 'preparatory_d.team_skills', FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('Please indicate whether you consider the team to have sufficient skills.'),
      'data-parsley-required' => TRUE,
    ),
  );

  // Add a preparatory_d for the button controls.
  $form['preparatory_d']['controls'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('form-controls'),
    ),
  );

  // Provide an add more button.
  $form['preparatory_d']['controls']['add_instance'] = array(
    '#type' => 'submit',
    '#value' => t('Add another team member'),
    '#submit' => array('instance_add_more_add_one'),
    '#limit_validation_errors' => TRUE,
    '#ajax' => array(
      'callback' => 'instance_add_more_callback_preparatory_d',
      'wrapper' => 'container',
    ),
  );

  // If there are more than two instances in the form then provide a button
  // to remove the last one.
  if ($form_state['num_instances'] > 1) {
    $form['preparatory_d']['controls']['remove_instance'] = array(
      '#type' => 'submit',
      '#value' => t('Remove one'),
      '#submit' => array('instance_add_more_remove_one'),
      '#limit_validation_errors' => TRUE,
      '#ajax' => array(
        'callback' => 'instance_add_more_callback_preparatory_d',
        'wrapper' => 'container',
      ),
    );
  }

  // Add a validation handler.
  $form['#validate'][] = __FUNCTION__ . '_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_d_validate($form, &$form_state) {
  $validator = new Validator($form, $form_state, 'preparatory_d');

  if ($validator->allFieldsAreEmpty()) {
    return;
  }

  // Bail out if the ajax buttons were used.
  if (isset($form_state['triggering_element']['#limit_validation_errors']) && $form_state['triggering_element']['#limit_validation_errors'] == TRUE) {
    return TRUE;
  }

  for ($i = 0; $i < $form_state['num_instances']; $i++) {
    // In each instance, check whether some of the fields have been filled in,
    // if they have then check they have all been filled in.

    // Checks is an array with the key being the element being targeted (in dot
    // notation) and the value being the callback to use to check whether the
    // field is empty.
    $checks = array(
      "preparatory_d.instance_$i.d_1" => 'fieldIsNotEmpty',
      "preparatory_d.instance_$i.d_2" => 'fieldIsNotEmpty',
      "preparatory_d.instance_$i.d_3" => 'fieldIsNotEmpty',
      "preparatory_d.instance_$i.wrapper.d_4" => 'fieldIsNotEmpty',
      "preparatory_d.instance_$i.wrapper.d_5" => 'fieldIsNotEmpty',
      "preparatory_d.instance_$i.wrapper.d_6" => 'fieldIsNotEmpty',
    );

    foreach ($checks as $target => $method) {
      $validator->validate($method, $target);
    }

  }

  // Check the team skills field has been filled in.
  $validator->validate('fieldIsNotEmpty', 'preparatory_d.team_skills');

  $validator->setErrorMessages();
}

/**
 * Ajax callback which returns the form array element to be applied against.
 */
function instance_add_more_callback_preparatory_d($form, $form_state) {
  return $form['preparatory_d'];
}
