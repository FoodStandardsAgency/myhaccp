<?php

/**
 * @file
 * Defines all of the step definitions.
 *
 * Each step is defined in this file and included in another file.
 */

/**
 * Prototype form.
 *
 * @return array
 */
function myhaccp_prototype_form_step_1(&$form_state, &$next_step, $params) {
  module_load_include('module', 'myhaccp_prototype', '/mforms/steps/' . $step_name);
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'myhaccp_prototype_form_step_2';

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
  $form['test1'] = array(
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
    '#default_value' => isset($vals['test1']) ? $vals['test1'] : NULL
  );
  $form['test2'] = array(
    '#weight' => '1',
    '#required' => '0',
    '#type' => 'textarea',
    '#title' => t('2. State the type of product you are producing and briefly how it is going to be packed:'),
    '#default_value' => isset($vals['test2']) ? $vals['test2'] : NULL
  );
  $form['test3'] = array(
    '#weight' => '2',
    '#required' => '0',
    '#type' => 'textfield',
    '#title' => t('It will start at '),
    '#default_value' => isset($vals['test3']) ? $vals['test3'] : NULL
  );
  $form['test4'] = array(
    '#weight' => '3',
    '#required' => '0',
    '#type' => 'textfield',
    '#title' => t('Through to '),
    '#default_value' => isset($vals['test4']) ? $vals['test4'] : NULL
  );
  return $form;
}

/**
 * Prototype form.
 *
 * @return array
 */
function myhaccp_prototype_form_step_2(&$form_state, &$next_step, $params) {
  // Define following step callback. If none set, that implies it is
  // the last step.

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
  $form['test5'] = array(
    '#weight' => '0',
    '#required' => '0',
    '#multiple' => '0',
    '#key_type_toggled' => '0',
    '#type' => 'select',
    '#options' => array(
      '1' => t('A test'),
      '2' => t('Another test'),
    ),
    '#multiple_toggle' => '1',
    '#title' => t('1. This is a test'),
    '#default_value' => isset($vals['test5']) ? $vals['test5'] : NULL
  );
  return $form;
}
