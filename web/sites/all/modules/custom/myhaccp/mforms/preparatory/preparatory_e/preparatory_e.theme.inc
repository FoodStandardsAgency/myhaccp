<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_preparatory_e().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_preparatory_e(&$variables) {
  $stage = 'preparatory_e';
  $values = $variables['data'][$stage];

  $variables['e_1_title'] = t('Ingredients');
  $variables['e_1'] = $values['e_1'];

  $variables['e_2_title'] = t('Physical properties');
  $variables['e_2'] = $values['e_2'];

  $variables['e_3_title'] = t('Processing');
  $variables['e_3'] = $values['e_3'];

  $variables['e_4_title'] = t('Packaging');
  $variables['e_4'] = $values['e_4'];

  $variables['e_5_title'] = t('Storage');
  $variables['e_5'] = $values['e_5'];

  $variables['e_6_title'] = t('Shelf life');
  $variables['e_6'] = $values['e_6'];

  $variables['e_7_title'] = '';
  $variables['e_7'] = $values['e_7'];

}
