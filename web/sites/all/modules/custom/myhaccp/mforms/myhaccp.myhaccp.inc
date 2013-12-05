<?php

/**
 * @file
 * Defines all of the step definitions.
 *
 * Each step is defined in this file and included in another file.
 */

/**
 * Helper function which loads the correct file for the step.
 *
 * Includes files which are named after the calling function with the following
 * pattern: [function name].inc
 *
 * @param string $function
 *   The function name as provided by __FUNCTION__
 * @param string $type
 *   The type dictates the name of the directory under mforms, e.g. principles.
 * @param array $form_state
 *   The form state array.
 * @param string $next_step
 *   The next step to be considered.
 *
 * @return array
 *   The form array for the called function.
 */
function _get_step($function, $type, &$form_state, &$next_step) {
  // Use ctools include to include our step file.
  ctools_include($function, 'myhaccp', 'mforms/' . $type);
  $function = '_' . $function;
  if (function_exists($function)) {
    return $function($form_state, $next_step);
  }
}

/**
 * Principle 1, question 1.
 */
function principle_1_question_1(&$form_state, &$next_step) {
  $function = __FUNCTION__;
  $type = 'principle';
  return _get_step($function, $type, $form_state, $next_step);
}

/**
 * Principle 1, question 2.
 */
function principle_1_question_2(&$form_state, &$next_step) {
  $function = __FUNCTION__;
  $type = 'principle';
  return _get_step($function, $type, $form_state, $next_step);
}

/**
 * Ajax callback which returns the form array element to be applied against.
 */
function instance_add_more_callback($form, $form_state) {
  return $form['container'];
}

/**
 * Ajax submit handler which positively adjusts the number of instances.
 */
function instance_add_more_add_one($form, &$form_state) {
  $form_state['num_instances']++;
  // Trigger a form rebuilt with an increased number of instances.
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax submit handler which negatively adjusts the number of instances.
 */
function instance_add_more_remove_one($form, &$form_state) {
  if ($form_state['num_instances'] > 1) {
    $form_state['num_instances']--;
  }
  // Trigger a form rebuild.
  $form_state['rebuild'] = TRUE;
}

/**
 * The submit handler to store the form at the end of the process.
 */
function _principle_1_question_2_submit($form, &$form_state) {
  $form_state['values'] += $_POST;
  mforms_submit('myhaccp', $form, $form_state);
}
