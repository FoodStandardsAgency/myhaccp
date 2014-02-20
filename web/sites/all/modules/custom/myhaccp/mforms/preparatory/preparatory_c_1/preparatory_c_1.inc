<?php

function preparatory_c_1(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_c_2';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'preparatory_c_1');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  $titles = _get_all_stage_names();
  drupal_set_title($titles[__FUNCTION__], PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'prep-c-1';

  // Wrap the form section in a fieldset.
  $form['preparatory_c_1'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // 1. What type of HACCP plan are you producing?
  $form['preparatory_c_1']['c_1'] = array(
    '#type' => 'select',
    '#title' => t('1. What type of HACCP plan are you producing?'),
    '#help_link' => 15,
    '#help_text' => t("Linear HACCP Plan - Typically one study that covers raw materials right  through to despatch (usually for simple systems).<br/>Modular HACCP Plan - Typically several separate HACCP studies e.g. one on raw materials, one  for each production line or product produced and one for despatch of the product (usually for complex systems/large variety of products).<br/>Generic HACCP Plan typically a plan applied across several sites."),
    '#options' => array(
      '0' => t('-- Please select --'),
      'linear' => t('Linear'),
      'modular' => t('Modular'),
      'linear_modular' => t('Linear / Modular'),
      'generic' => t('Generic'),
    ),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-notequal' => '0',
      'data-parsley-error-message' => t('Please select the type of HACCP plan you are producing.'),
    ),
    '#default_value' => array_get($values, 'preparatory_c_1.c_1', array()),
  );

  // 2. State the type of product you are producing and briefly how it is going to be packed.
  $form['preparatory_c_1']['c_2'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('2. State the type of product you are producing and briefly how it is going to be packed:'),
    '#help_link' => 15,
    '#help_text' => t("State the c_2s you are making (those covered in the HACCP plan) and how they are packaged e.g. vacuum packed, gas flushed, flexible pouches."),
    '#default_value' => array_get($values, 'preparatory_c_1.c_2', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state the type of product you are producing and how it will be packed.'),
    ),
  );

  // 3.State the process start and end points of the HACCP plan.
  $form['preparatory_c_1']['c_3'] = array(
    '#type' => 'container',
  );

  $form['preparatory_c_1']['c_3']['title'] = array(

    '#markup' => '<div class="label">' . t('3. State the process start and end points of the HACCP plan. !tip !help', array(
        '!tip' => _help_tip(15),
        '!help' => '<div class="help-text">State where your HACCP plan begin e.g. at raw materials or goods in.  State where it will end e.g. at delivery to the wholesaler, at despatch, when purchased by the  the consumer.</div>')) . '</div>',
      '#title' => t('2. State the type of product you are producing and briefly how it is going to be packed:'),
    '#help_link' => 15,
    );


  $form['preparatory_c_1']['c_3']['start'] = array(
    '#type' => 'textfield',
    '#title' => t('It will start at '),
    '#default_value' => array_get($values, 'preparatory_c_1.c_3.start', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state the process start.'),
    ),
  );

  $form['preparatory_c_1']['c_3']['end'] = array(
    '#type' => 'textfield',
    '#title' => t('Through to '),
    '#default_value' => array_get($values, 'preparatory_c_1.c_3.end', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state the process end.'),
    ),
  );

  $form['#validate'][] = __FUNCTION__ . '_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_c_1_validate($form, &$form_state) {
  $validator = new validator($form, $form_state, 'preparatory_c_1');

  if ($validator->allFieldsAreEmpty()) {
    return;
  }

  // Validation: Some content.
  $checks = array(
    'preparatory_c_1.c_1' => 'fieldIsNotEmpty',
    'preparatory_c_1.c_2' => 'fieldIsNotEmpty',
    'preparatory_c_1.c_3.start' => 'fieldIsNotEmpty',
    'preparatory_c_1.c_3.end' => 'fieldIsNotEmpty',
  );

  foreach ($checks as $target => $method) {
    $validator->validate($method, $target);
  }

  $validator->setErrorMessages();
}
