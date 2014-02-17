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
 * Modify the form for each stage.
 *
 * Adds the parsley attributes to the form element. Also adds a save message
 * handler.
 */
function myhaccp_form_myhaccp_study_resume_alter(&$form, &$form_state) {
  $form['#attributes']['data-parsley-namespace'] = 'data-parsley-';
  $form['#attributes']['data-parsley-validate'] = '';
  // The message that says the stage has saved.
  $form['#validate'][] = 'myhaccp_saved_message';
  // Add the validation messages container.
  $form['validation_messages'] = array(
    '#type' => 'container',
    '#id' => 'validation-messages',
    '#weight' => -10,
  );
  $form['#process']['myhaccp'] = 'myhaccp_form_process';
  // Include the CTools tools that we need.
  ctools_include('ajax');
  ctools_include('modal');
  // Add CTools' javascript to the page.
  ctools_modal_add_js();
  // Create our own javascript that will be used to theme a modal.
  $haccp_modal_style = array(
    'myhaccp-style' => array(
      'modalSize' => array(
        'type' => 'scale',
        'width' => 0.9,
        'height' => 0.9,
        'addWidth' => 10,
        'addHeight' => 0,
        'contentRight' => 35,
        'contentBottom' => 50,
      ),
      'modalOptions' => array(
        'opacity' => .6,
        'background-color' => '#333333',
      ),
      'animation' => 'fadeIn',
      'modalTheme' => 'myhaccp_modal',
    ),
  );
  // Add the settings array defined above to Drupal 7's JS settings:
  drupal_add_js($haccp_modal_style, 'setting');
  ctools_add_js('myhaccp_modal', 'myhaccp', 'mforms/js');
}
