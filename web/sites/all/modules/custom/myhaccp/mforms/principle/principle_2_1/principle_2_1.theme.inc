<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_preparatory_2_1().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_preparatory_2_1(&$variables) {
  $stage = 'preparatory_2_1';
  $values = $variables['data'][$stage];

  // a_1
  // $variables['a_1_title'] = t('The company has in place a number of effective prerequisite programmes, including:');
  // $variables['a_1'] = !empty($names) ? '<ul><li>' . implode('</li><li>', $names) . '</li></ul>' : '';

}
