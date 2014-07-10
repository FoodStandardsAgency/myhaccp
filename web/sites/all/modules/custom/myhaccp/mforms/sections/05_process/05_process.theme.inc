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
function myhaccp_preprocess_05_process(&$variables) {
  // This section is made up of data from two stages.
  $study = $variables['study'];
  $data = $study->getStage('preparatory_g')->getData();
  $preparatory_g = $data['preparatory_g'];
  $data = $study->getStage('preparatory_h')->getData();
  $preparatory_h = $data['preparatory_h'];

  // Flow diagram file.
  $file = file_load($preparatory_g['g_2']);

  if (empty($file)) {
    // If the file couldn't be loaded then log a watchdog error.
    watchdog('myhaccp', t('Whilst rendering the PDF, the flow diagram could not be loaded.'), array(), WATCHDOG_ERROR);
  }

  // Prepare an image derivative of the flow diagram image of a reasonable maximum size (2048px wide).
  $image_url = image_style_url('pdf_flow_diagram', $file->uri);
  $variables['flow_diagram_url'] = $image_url;

  // 1. Have you completed a flow diagram?
  if ($preparatory_g['g_1'] == 'yes') {
    $variables['g_1'] = t('We have completed a flow diagram covering all steps in the manufacturing process of this product.');
  }
  else {
    $variables['g_1'] = t('We have <strong>not</strong> completed a flow diagram covering all steps in the manufacturing process of this product.');
  }

  // Hard copy location.
  if (!empty($preparatory_g['g_3'])) {
    $variables['g_3'] = $preparatory_g['g_3'];
  }

  // 1. Name of person(s) confirming flow diagram is correct:
  if (!empty($preparatory_h['h_1'])) {
    $variables['h_1'] = '<strong>' . $preparatory_h['h_1'] . '</strong> ' . t('has confirmed that our flow diagram is correct.');
  }

  // 2. Is every process step identified on the flow diagram?
  if (!empty($preparatory_h['h_2']) && $preparatory_h['h_2'] == 'yes') {
    $variables['h_2'] = t('Every process step is identified in our flow diagram.');
  }
  else {
    $variables['h_2'] = '';
  }

  // 3. Is the flow diagram an accurate representation of the process from start to finish?
  if (!empty($preparatory_h['h_3']) && $preparatory_h['h_3'] == 'yes') {
    $variables['h_3'] = t('The flow diagram is an accurate representation of the process from start to finish.');
  }
  else {
    $variables['h_3'] = '';
  }

  // 4. Is the process flow diagram correct for all shifts (e.g. days, nights and weekend)?
  if (!empty($preparatory_h['h_4']) && $preparatory_h['h_4'] == 'yes') {
    $variables['h_4'] = t('The flow diagram is correct for all shifts (e.g. days, nights and weekend).');
  }
  else {
    $variables['h_4'] = '';
  }

  // 5. Is the flow diagram correct during all seasonal variations?
  if (!empty($preparatory_h['h_5']) && $preparatory_h['h_5'] == 'yes') {
    $variables['h_5'] = t('The flow diagram is correct during all seasonal variations.');
  }
  else {
    $variables['h_5'] = '';
  }

  // 6. Has the team leader signed off and dated the flow diagram as being correct?
  if (!empty($preparatory_h['h_6']) && $preparatory_h['h_6'] == 'yes') {
    $variables['h_6'] = t('The HACCP lead has signed off and dated the flow diagram as being correct.');
  }
  else {
    $variables['h_6'] = '';
  }

  // 7. Please state who in your organisation is responsible for making changes to the flow diagram and storing out of date versions.
  if (!empty($preparatory_h['h_7'])) {
    $h7 = explode("\r\n", trim($preparatory_h['h_7']));
    $h7 = implode('</li><li>', $h7);
    $h7 = '<div><p>' . t('The following members of our organisation are responsible for making changes to the flow diagram and storing out of date versions:') . '</p><ul><li>' . $h7 . '</li></ul></div>';
    $variables['h_7'] = $h7;
  }

}
