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
function myhaccp_preprocess_13_documentation(&$variables) {
  $study = $variables['study'];
  $data = $study->getStage('principle_7')->getData();
  $principle_7 = $data['principle_7'];

  // 1. Select all forms of documentation relating to this HACCP study that your business retains.
  $documentation = myhaccp_prepare_checkboxes_output('principle_7', '7_1', $principle_7);
  $content = '';
  if (!empty($documentation)) {
    $content .= '<h4>' . t('Documentation relating to this HACCP study that the business retains:') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $documentation);
    $content .= '</li></ul>';
    $variables['p_7_1'] = $content;
  }

  // 2. Provide details of any other supporting information (i.e. anything else covered in your HACCP plan) that is retained.
  if (!empty($principle_7['7_2'])) {
    $variables['p_7_2_title'] = t('Other supporting information that is retained');
    $variables['p_7_2'] = nl2br($principle_7['7_2']);
  }

  // 3. How is documentation controlled (up-dates / issue number)?
  if (!empty($principle_7['7_3'])) {
    $variables['p_7_3_title'] = t('Documentation control');
    $variables['p_7_3'] = $principle_7['7_3'];
  }

  // 4. What is the maximum length of time that you retain this information for?
  if (!empty($principle_7['7_4'])) {
    $variables['p_7_4'] = t('The maximum length of time we retain this information for is ') . '<strong>' . $principle_7['7_4'] . '</strong>';
  }

  // 5. Are the records accessible, accurate and up to date?
  if (!empty($principle_7['7_5'])) {
    if ($principle_7['7_5'] == 'yes') {
      $variables['p_7_5'] = t('All records are accessible, accurate and up to date.');
    }
  }

}
