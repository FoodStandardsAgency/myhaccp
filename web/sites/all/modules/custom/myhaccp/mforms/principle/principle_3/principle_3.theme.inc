<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_principle_3().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_principle_3(&$variables) {
  $stage = 'principle_3';
  $values = $variables['data'][$stage];
}

function myhaccp_principle_3_cl($h_key) {
  $principle_3_data = mforms_get_vals('myhaccp', 'principle_3');
  $p_3_values = $principle_3_data['principle_3'];

  $content ='';

  if($h_key) {
    // 1. What is the critical limit for this critical control point (what separates safe from potentially unsafe product)?
    $content .= '<p><strong>' . $p_3_values[$h_key]['3_1'] . '</strong></p>';

    // 2. Provide details of how the critical limit was determined.
    $content .= '<p>' . $p_3_values[$h_key]['3_2'] . '</p>';

    // 3. Is the critical limit appropriate to control the specific hazard?
    if($p_3_values[$h_key]['3_3'] == 'yes') {
      $content .= '<p>' . t('The critical limit is appropriate to control the specific hazard.') . '</p>';
    }

    // 4. Is the critical limit measurable or observable in real time?
    if($p_3_values[$h_key]['3_3'] == 'yes') {
      $content .= '<p>' . t('The critical limit is measurable or observable in real time.') . '</p>';
    }

    // Is there a target value?
    if($p_3_values[$h_key]['3_5'] == 'yes') {
      $content .= '<p><strong>Target value:</strong> ' . $p_3_values[$h_key]['3_6'] . '<br />';
      $content .= '<p><strong>Tolerances:</strong> ' . $p_3_values[$h_key]['3_7'] . '</p>';
    }

    return $content;

  } else {
    return $content;
  }

}
