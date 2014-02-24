<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_principle_1_3().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_principle_1_3(&$variables) {
  // @todo pull in data from Principle 1.2, e.g hazard description

  $stage = 'principle_1_3';
  $values = $variables['data'][$stage];

  foreach($values['instance_table'] as $key =>  $control_measure) {
    $variables[''] = '';
  }

}
