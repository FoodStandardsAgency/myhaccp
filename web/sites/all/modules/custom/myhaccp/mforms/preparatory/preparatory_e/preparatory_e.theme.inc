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

  // @todo turn all titles (e.g 'Ingredients') into variables passed through t()

  // Ingredients
  $variables['e_1'] = $values['e_1'];

  // Physical properties
  $variables['e_2'] = $values['e_2'];

  // Processing
  $variables['e_3'] = $values['e_3'];

  // Packaging
  $variables['e_4'] = $values['e_4'];

  // Storage
  $variables['e_5'] = $values['e_5'];

  // Shelf life
  $variables['e_6'] = $values['e_6'];

  // Storage & handling
  $variables['e_7'] = $values['e_7'];

}
