<?php

function preparatory_c_question_1_3(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_c_question_4';

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

  drupal_set_title('Preparatory Stage C: Define scope of the study, Questions 1-3');

  $form = array();
  $form['#attributes']['class'][] = 'pcq13';

  // Wrap the form section in a fieldset.
  $form['container'] = array(
    '#type' => 'fieldset',
  );

  $form['container']['prep_c_q1'] = array(
    '#type' => 'select',
    '#title' => t('1. What type of HACCP plan are you producing? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#options' => drupal_map_assoc(
      array(
        t('Linear'),
        t('Modular'),
        t('Linear / Modular'),
        t('Generic'),
      )
    ),
    '#default_value' => isset($values['prep_c_q1']) ? $values['prep_c_q1'] : NULL
  );

  $form['container']['prep_c_q2'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('2. State the type of product you are producing and briefly how it is going to be packed: !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => isset($values['prep_c_q2']) ? $values['prep_c_q2'] : NULL
  );

  $form['container']['prep_c_q3'] = array(
    '#type' => 'container',
  );

  $form['container']['prep_c_q3']['title'] = array(
    '#markup' => '<div class="label">' . t('3. State start and end points of the HACCP plan: !tip', array(
      '!tip' => _help_tip(),
      )
    ) . '</div>',
  );

  $form['container']['prep_c_q3']['start'] = array(
    '#type' => 'textfield',
    '#title' => t('It will start at '),
    '#default_value' => isset($values['start']) ? $values['start'] : NULL
  );

  $form['container']['prep_c_q3']['end'] = array(
    '#type' => 'textfield',
    '#title' => t('Through to '),
    '#default_value' => isset($values['end']) ? $values['end'] : NULL
  );

  return $form;
}
