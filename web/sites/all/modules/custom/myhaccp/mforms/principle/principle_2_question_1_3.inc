<?php

function principle_2_question_1_3(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_3';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'principle_2_question_1_3');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  drupal_set_title('Principle 2, questions 1-3: Determine Critical Control Points (CCPs)', PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'principle-2-question-1-3';

  // Wrap the form section in a fieldset.
  $form['principle_2_question_1_3'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // 1. Are you using a decision tree?
  $form['principle_2_question_1_3']['decision_tree'] = array(
    '#type' => 'radios',
    '#title' => t('1. Are you using a decision tree? !tip', array(
      '!tip' => _help_tip(27),
    )),
    '#help_text' => t('We recomend using either the Campden or Codex decision trees.'),
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#default_value' => array_get($values, 'principle_2_question_1_3.decision_tree', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm whether you are using a decision tree.'),
    ),
  );

  // 2. Which decision tree are you using?
  $form['principle_2_question_1_3']['which_tree'] = array(
    '#type' => 'select',
    '#options' => array(
      'none' => t('-- Please select --'),
      'no_tree' => t('None'),
      'codex' => t('Codex'),
      'campden' => t('Campden'),
    ),
    '#title' => t('2. Which decision tree are you using? !tip', array(
      '!tip' => _help_tip(27),
    )),
    '#default_value' => array_get($values, 'principle_2_question_1_3.which_tree', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-notequal' => 'none',
      'data-parsley-error-message' => t('Please select a decision tree, or none if you are not using one.'),
    ),
  );

  // 3. If using your own, how many questions are in your decision tree?
  $form['principle_2_question_1_3']['own'] = array(
    '#type' => 'textfield',
    '#title' => t('3. If using your own, how many questions are in your decision tree? !tip', array(
      '!tip' => _help_tip(27),
    )),
    '#default_value' => array_get($values, 'principle_2_question_1_3.own', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state how many questions are in your decision tree.'),
    ),
  );

  $form['#validate'][] = 'principle_2_question_1_3_validate';

  return $form;
}

/**
 * Validation handler.
 */
function principle_2_question_1_3_validate($form, &$form_state) {
  $invalid = array();

  // Checks is an array with the key being the element being targeted (in dot
  // notation) and the value being the callback to use to check whether the
  // field is empty.
  $checks = array(
    'principle_2_question_1_3.decision_tree' => '_radios_field_is_empty',
    'principle_2_question_1_3.which_tree' => '_select_field_is_empty',
    'principle_2_question_1_3.own' => '_text_field_is_empty',
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
