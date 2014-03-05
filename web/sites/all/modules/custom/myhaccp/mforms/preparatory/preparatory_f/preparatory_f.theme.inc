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

  // Name of the product
  if(!empty($values['f_1'])) {
    $variables['f_1'] = $values['f_1'];
  }

  // 2. Is the product specifically designed for consumption by the general public?
  if(!empty($values['f_2'])) {
    $variables['f_2'] = ($values['f_2'] == 'yes' ? t('The product is specifically designed for consumption by the general public.') : '' );
  }

  // 3. Is the product specifically designed for the young?
  if(!empty($values['f_3'])) {
    $variables['f_3'] = ($values['f_3'] == 'yes' ? t('The product is specifically designed for the young.') : '' );
  }

  // 4. Is the product specifically designed for the elderly?
  if(!empty($values['f_4'])) {
    $variables['f_4'] = ($values['f_4'] == 'yes' ? t('The product is specifically designed for the elderly.') : '' );
  }

  // 5. Is the product specifically designed for pregnant ladies?
  if(!empty($values['f_5'])) {
    $variables['f_5'] = ($values['f_5'] == 'yes' ? t('The product is specifically designed for pregnant ladies.') : '' );
  }

  // 6. Is the product specifically designed for the immunosuppressed / immunocompromised?
  if(!empty($values['f_6'])) {
    $variables['f_6'] = ($values['f_6'] == 'yes' ? t('The product is specifically designed for the immunosuppressed / immunocompromised.') : '' );
  }

  // 7. Is the product specifically designed for people with allergies or intolerances?
  if(!empty($values['f_7'])) {
    $variables['f_7'] = ($values['f_7'] == 'yes' ? t('The product is specifically designed for people with allergies or intolerances.') : '' );
  }

  // 8. Detail below how you have considered the likely abuse/unintended use of the product by the consumer or purchaser.
  if(!empty($values['f_8'])) {
    $variables['f_8_title'] = t('We have considered the likely abuse / unintended use of the product by the consumer in the following ways:');
    $variables['f_8'] = $values['f_8'];
  }

}
