<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_preparatory_g().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_preparatory_g(&$variables) {
  $stage = 'preparatory_g';
  $values = $variables['data'][$stage];

  //dpm($values);

  // Hard copy location
  $variables['g_3'] = $values['g_3'];

}
