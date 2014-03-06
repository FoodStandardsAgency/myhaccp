<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_preparatory_h().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_preparatory_h(&$variables) {
  $stage = 'preparatory_h';
  $values = $variables['data'][$stage];

  // 1. Name of person(s) confirming flow diagram is correct:
  if(!empty($values['h_1'])) {
    $variables['h_1'] = '<strong>' . $values['h_1'] . '</strong> ' . t('has confirmed that our flow diagram is correct.');
  }

  // 2. Is every process step identified on the flow diagram?
  if(!empty($values['h_2']) && $values['h_2'] == 'yes') {
    $variables['h_2'] =  t('Every process step is identified in our flow diagram.');
  } else {
    $variables['h_2'] = '';
  }

  // 3. Is the flow diagram an accurate representation of the process from start to finish?
  if(!empty($values['h_3']) && $values['h_3'] == 'yes') {
    $variables['h_3'] =  t('The flow diagram is an accurate representation of the process from start to finish.');
  } else {
    $variables['h_3'] = '';
  }

  // 4. Is the process flow diagram correct for all shifts (e.g. days, nights and weekend)?
  if(!empty($values['h_4']) && $values['h_4'] == 'yes') {
    $variables['h_4'] =  t('The flow diagram is correct for all shifts (e.g. days, nights and weekend).');
  } else {
    $variables['h_4'] = '';
  }

  // 5. Is the flow diagram correct during all seasonal variations?
  if(!empty($values['h_5']) && $values['h_5'] == 'yes') {
    $variables['h_5'] =  t('The flow diagram is correct during all seasonal variations.');
  } else {
    $variables['h_5'] = '';
  }

  // 6. Has the team leader signed off and dated the flow diagram as being correct?
  if(!empty($values['h_6']) && $values['h_6'] == 'yes') {
    $variables['h_6'] =  t('The HACCP lead has signed off and dated the flow diagram as being correct.');
  } else {
    $variables['h_6'] = '';
  }

  // 7. Please state who in your organisation is responsible for making changes to the flow diagram and storing out of date versions.
  if(!empty($values['h_7'])) {
    $h7 = explode("\r\n", trim($values['h_7']));
    $h7 = implode('</li><li>', $h7);
    $h7 = '<div><p>' . t('The following members of our organisation are responsible for making changes to the flow diagram and storing out of date versions:') . '</p><ul><li>' . $h7 . '</li></ul></div>';
    $variables['h_7'] = $h7;
  }

}
