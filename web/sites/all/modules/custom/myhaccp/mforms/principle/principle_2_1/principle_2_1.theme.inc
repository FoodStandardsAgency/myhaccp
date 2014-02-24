<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_principle_2_1().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_principle_2_1(&$variables) {
  $stage = 'principle_2_1';
  $values = $variables['data'][$stage];

  // 1. Are you using a decision tree?
  if ($values['2_1_1'] == 'yes') {
    $variables['p_2_1_1'] = t('We are using a decision tree.');
  } elseif ($values['2_1_1'] == 'no') {
    $variables['p_2_1_1'] = t('For this study we are not using a decision tree. We are deciding on our CCPS in the following ways:<br />');
    $variables['p_2_1_1'] .= $values['2_1_1b'];
  }

  // 1a. Which decision tree are you using?
  if ($values['2_1_1a'] == 'codex') {
    $variables['p_2_1_1a'] = t('For this study, we are using the Codex decision tree.');
  } elseif ($values['2_1_1a'] == 'campden') {
    $variables['p_2_1_1a'] = t('For this study, we are using the Campden decision tree.');
  }

}
