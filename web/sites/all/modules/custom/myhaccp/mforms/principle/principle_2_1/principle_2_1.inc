<?php

function principle_2_1(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_2_2';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'principle_2_1');

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
  $form['#attributes']['class'][] = 'principle-2-question-1-3';

  // Wrap the form section in a fieldset.
  $form['principle_2_1'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // Introductory text.
  $form['principle_2_1']['intro'] = array(
    '#prefix' => '<p class="intro">',
    '#suffix' => '</p>',
    '#markup' => t('A CCP is a step at which control can be applied and is essential to prevent or eliminate a food safety hazard or reduce it to an acceptable level.'),
  );

  $hazards = Hazards::getInstance();

  // Ensure data has been entered on principle_1_1.
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

  // 1. Are you using a decision tree?
  $form['principle_2_1']['2_1_1'] = array(
    '#type' => 'radios',
    '#title' => t('1. Are you using a decision tree?'),
    '#help_link' => 27,
    '#help_text' => t("A 'decision tree' is a tool that can be used to help identify a critical control point. You do not have to use a decision tree."),
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#default_value' => array_get($values, 'principle_2_1.2_1_1', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm whether you are using a decision tree.'),
    ),
  );

  // 2. Which decision tree are you using?
  $form['principle_2_1']['2_1_1a'] = array(
    '#type' => 'select',
    '#options' => array(
      '0' => t('-- Please select --'),
      'codex' => t('Codex'),
      'campden' => t('Campden'),
    ),
    '#title' => t('1a. Which decision tree are you using?'),
    '#help_link' => 27,
    '#help_text' => t('You can select which decision tree you wish to use to help you, but you can use one  of your own or none at all.  More information on the  decision trees can be found.'),
    '#states' => array(
      'visible' => array(
        ':input[name="principle_2_1[2_1_1]"]' => array('value' => 'yes'),
      ),
    ),
    '#default_value' => array_get($values, 'principle_2_1.2_1_1a', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-notequal' => '0',
      'data-parsley-error-message' => t('Please select a decision tree, or none if you are not using one.'),
    ),
  );

  // 3. If you are not using  either of the decision trees, please explain how you are deciding on your CCPs.
  $form['principle_2_1']['2_1_1b'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('1b. Please explain how you are deciding on your CCPs. !tip', array(
      '!tip' => _help_tip(),
    )),
    '#states' => array(
      'visible' => array(
        ':input[name="principle_2_1[2_1_1]"]' => array('value' => 'no'),
      ),
    ),
    '#default_value' => array_get($values, 'principle_2_1.2_1_1b', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state how you are deciding your on your Critical Control Points.'),
    ),
  );

  $form['#validate'][] = 'principle_2_1_validate';

  return $form;
}

/**
 * Validation handler.
 */
function principle_2_1_validate($form, &$form_state) {
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

  $checks = array(
    'principle_2_1.2_1_1' => 'fieldIsNotEmpty',
  );

  foreach ($checks as $target => $method) {
    $validator->validate($method, $target);
  }

  $tree = array_get($form_state, 'values.principle_2_1.2_1_1', FALSE);

  // If not using a decision tree.
  if ($tree == 'no') {
    $target = 'principle_2_1.2_1_1b';
    $validator->validate($method, $target);
  }
  elseif ($tree == 'yes') {
    // Using a decision tree so check which tree.
    $target = 'principle_2_1.2_1_1a';
    $validator->validate($method, $target);
  }

  $validator->setErrorMessages();
  $form_state = $validator->getFormState();
}
