<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_preparatory_f().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_preparatory_f(&$variables) {
  $stage = 'preparatory_f';
  $values = $variables['data'][$stage];

  dpm($values);

  // Name of the product
  $variables['f_1'] = $values['f_1'];

  // Is the product designed for the young?
  $variables['f_2'] = $values['f_2'];

  // Is the product designed for the elderly?
  $variables['f_3'] = $values['f_3'];

  // Is the product designed for pregnant ladies?
  $variables['f_4'] = $values['f_4'];

  // Is the product designed for the immunosuppressed / immunocompromised?
  $variables['f_5'] = $values['f_5'];

  // Is the product suitable for people with allergies or intolerances?
  $variables['f_6'] = $values['f_6'];

  // Are there any other groups of people that may consume your product that require f_7 consideration?
  $variables['f_7'] = $values['f_7'];

  // Is it possible that your product could be consumed by someone other than those for whom it is intended?
  $variables['f_8'] = $values['f_8'];

  // Detail below how you have considered the likely abuse / unintended use of the product by the consumer. ?
  $variables['f_9'] = $values['f_9'];


}
