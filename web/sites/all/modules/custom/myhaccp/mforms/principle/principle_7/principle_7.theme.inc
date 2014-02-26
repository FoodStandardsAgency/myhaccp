<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_principle_7().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_principle_7(&$variables) {
  $stage = 'principle_7';
  $values = $variables['data'][$stage];

  // 1. Mark all forms of documentation relating to the HACCP study that your organisation retain.
  // @todo $variables['p_7_1'] = '';

  // 2. Detail any other supporting information (i.e. anything that covers the HACCP system operation) that is retained.
  $variables['p_7_2_title'] = t('Other supporting information that is retained');
  $variables['p_7_2'] = $values['7_2'];

  // 3. How is documentation controlled (up-dates / issue number)?
  $variables['p_7_3_title'] = t('Documentation control');
  $variables['p_7_3'] = $values['7_3'];

  // 4. What is the maximum length of time that you retain this information for?
  $variables['p_7_4'] = t('The maximum length of time we retain this information for is ') . '<strong>' . $values['7_4'] . '</strong>';

  // 5. Are the records accessible, accurate and up to date?
  if($values['7_5'] == 'yes') {
    $variables['p_7_5'] = t('All records are accessible, accurate and up to date.');
  }

}
