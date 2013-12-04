<?php

/**
 * Principle 1, Question 1.
 */
function _principle_1_question_2(&$form_state, &$next_step) {
  // Define following step callback. If none set, that implies it is
  // the last step.
//  $next_step = '_principle_1_question_2';

  // Retrieve submitted values. This comes in handy when back action
  // occured and we need to display values that were originaly submitted.
  $data = mforms_get_vals('myhaccp');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  if (!empty($data)) {
    $vals = $data;
  }
  elseif (isset($form_state['values'])) {
    $vals = $form_state['values'];
  }

  $form = array();
  $form['item'] = array(
    '#weight' => '0',
    '#required' => '0',
    '#multiple' => '0',
    '#key_type_toggled' => '0',
    '#type' => 'select',
    '#options' => array(
      '1' => t('Linear'),
      '2' => t('Modular'),
      '3' => t('Linear / Modular'),
      '4' => t('Generic'),
    ),
    '#multiple_toggle' => '1',
    '#title' => t('1. What type of HACCP plan are you producing?'),
    '#default_value' => isset($vals['item']) ? $vals['item'] : NULL
  );
  return $form;
}
