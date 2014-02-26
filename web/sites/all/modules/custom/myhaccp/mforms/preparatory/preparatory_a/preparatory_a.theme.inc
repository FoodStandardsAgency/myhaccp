<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_preparatory_a().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_preparatory_a(&$variables) {

}

/**
 * Pull data in from Preparatory Stage A (Prerequisites)
 *
 * @return array $variables
 *   Data to pass into the template
 */
function myhaccp_preparatory_stage_a_data() {
  // Initialise mforms so we can get values from other stages and then
  // get values from other stages.
  myhaccp_myhaccp_mforms_init();
  $stage = 'preparatory_a';
  $data = mforms_get_vals('myhaccp', $stage);
  $values = $data[$stage];

  // Iterate over the checkboxes fetching their labels.
  $names = array();
  foreach ($values['a_1'] as $key => $value) {
    if ($key === $value) {
      $names[] = $value;
    }
  }
  // a_1
  $variables['a_1_title'] = t('The company has in place a number of effective prerequisite programmes, including:');
  $variables['a_1'] = !empty($names) ? '<ul><li>' . implode('</li><li>', $names) . '</li></ul>' : '';
  // a_2
  $variables['a_2_title'] = t('The location of the above documents is:');
  $variables['a_2'] = $values['a_2'] ? $values['a_2'] : '';

  return $variables;
}
