<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_preparatory_b().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_preparatory_b(&$variables) {
  $stage = 'preparatory_b';
  $values = $variables['data'][$stage];
  // Iterate over the checkboxes fetching their labels.
  $names = array();
  foreach ($values['b_1'] as $key => $value) {
    if ($key === $value) {
      $names[] = $value;
    }
  }
  // b_1 Logic: IF ‘I am the management and can confirm that I am committed.’  is selected:
  if (in_array('N/A - I am the management and can confirm that I am committed.', $names)) {
    $variables['b_1_title'] = t('I am the management and can confirm that I am committed to food safety management based on HACCP.');
    // Don't show any of the checkboxes output.
    $variables['b_1'] = '';
  }
  else {
    $variables['b_1_title'] = t('The following evidence shows the support of senior management to food safety management based on HACCP:');
    $variables['b_1'] = !empty($names) ? '<ul><li>' . implode('</li><li>', $names) . '</li></ul>' : '';
  }
  // b_2
  $variables['b_2_title'] = t('Other Evidence of management commitment:');
  $variables['b_2'] = $values['b_2'] ? $values['b_2'] : '';
}
