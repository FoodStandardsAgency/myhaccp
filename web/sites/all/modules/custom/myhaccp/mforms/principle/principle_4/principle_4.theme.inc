<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_principle_4().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_principle_4(&$variables) {
  $stage = 'principle_4';
  $values = $variables['data'][$stage];

}

/**
 *
 * Return monitoring procedures for a hazard.
 *
 * @param string $h_key
 *   The key of the Hazard.
 */

function myhaccp_principle_4_m($h_key) {
  $principle_4_data = mforms_get_vals('myhaccp', 'principle_4');
  $values = $principle_4_data['principle_4'];

  // dpm($values);

  $content ='';

  if($h_key) {
    // 1. What monitoring activities are going to take place at this CCP?
    $content .= '<p>' . $values[$h_key]['4_1'] . '</p>';

    // 2. What monitoring activities are going to take place at this CCP?
    $content .= '<p>' . $values[$h_key]['4_1'] . '</p>';

    // @todo

    return $content;

  } else {
    return $content;
  }

}
