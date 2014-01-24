<?php

function preparatory_c_question_1_3(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_c_question_4';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'preparatory_c_question_1_3');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  drupal_set_title('Preparatory Stage C: Define scope of the study, <br/>Questions 1-3', PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'prep-c-1';

  // Wrap the form section in a fieldset.
  $form['preparatory_c_question_1_3'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  # 1. What type of HACCP plan are you producing?
  $form['preparatory_c_question_1_3']['type'] = array(
    '#type' => 'select',
    '#title' => t('1. What type of HACCP plan are you producing? !tip', array(
      '!tip' => _help_tip(15),
    )),
    '#help_text' => t("Linear HACCP Plan - Typically one study that covers raw materials right  through to despatch (usually for simple systems).<br/>Modular HACCP Plan - Typically several separate HACCP studies e.g. one on raw materials, one  for each production line or product produced and one for despatch of the product (usually for complex systems/large variety of products).<br/>Generic HACCP Plan typically a plan applied across several sites."),
    '#options' => array(
      'none' => t('-- Please select --'),
      'linear' => t('Linear'),
      'modular' => t('Modular'),
      'linear_modular' => t('Linear / Modular'),
      'generic' => t('Generic'),
    ),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-notequal' => 'none',
      'data-parsley-error-message' => t('Please select the type of HACCP plan you are producing.'),
    ),
    '#default_value' => array_get($values, 'preparatory_c_question_1_3.type', array()),
  );

  # 2. State the type of product you are producing and briefly how it is going to be packed.
  $form['preparatory_c_question_1_3']['product'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('2. State the type of product you are producing and briefly how it is going to be packed: !tip', array(
      '!tip' => _help_tip(15),
    )),
    '#help_text' => t("State the products you are making (those covered in the HACCP plan) and how they are packaged e.g. vacuum packed, gas flushed, flexible pouches."),
    '#default_value' => array_get($values, 'preparatory_c_question_1_3.product', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state the type of product you are producing and how it will be packed.'),
    ),
  );

  # 3.State the process start and end points of the HACCP plan.
  $form['preparatory_c_question_1_3']['q3'] = array(
    '#type' => 'container',
  );

  $form['preparatory_c_question_1_3']['q3']['title'] = array(

    '#markup' => '<div class="label">' . t('3. State the process start and end points of the HACCP plan. !tip !help', array(
        '!tip' => _help_tip(),
        '!help' => '<div class="help-text">State where your HACCP plan begin e.g. at raw materials or goods in.  State where it will end e.g. at delivery to the wholesaler, at despatch, when purchased by the  the consumer.</div>')) . '</div>',
      '#title' => t('2. State the type of product you are producing and briefly how it is going to be packed: !tip', array(
      '!tip' => _help_tip(15),
    )),
    );


  $form['preparatory_c_question_1_3']['q3']['start'] = array(
    '#type' => 'textfield',
    '#title' => t('It will start at '),
    '#default_value' => array_get($values, 'preparatory_c_question_1_3.q3.start', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state the process start.'),
    ),
  );

  $form['preparatory_c_question_1_3']['q3']['end'] = array(
    '#type' => 'textfield',
    '#title' => t('Through to '),
    '#default_value' => array_get($values, 'preparatory_c_question_1_3.q3.end', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state the process end.'),
    ),
  );

  $form['#validate'][] = 'preparatory_c_question_1_3_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_c_question_1_3_validate($form, &$form_state) {
  $invalid = array();

  // Validation: Some content.
  $checks = array(
    'preparatory_c_question_1_3.type' => '_select_field_is_empty',
    'preparatory_c_question_1_3.product' => '_text_field_is_empty',
    'preparatory_c_question_1_3.q3.start' => '_text_field_is_empty',
    'preparatory_c_question_1_3.q3.end' => '_text_field_is_empty',
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
