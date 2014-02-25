<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_principle_6().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_principle_6(&$variables) {
  $stage = 'principle_6';
  $values = $variables['data'][$stage];

  // 1. Document your validation study in the space below.
  $variables['p_6_1'] = $values['6_1'];

  // 2. Who is responsible for ensuring the contents of the HACCP plan are validated?
  // 3. Is this the same person who will formally sign off the HACCP plan?
  // 3a. Who will formally sign off the HACCP plan?
  if($values['6_3'] == 'no') {
    $variables['p_6_2'] =  '<p><strong>' . $values['6_2'] . '</strong>' . t(' is responsible for ensuring the contents of the HACCP plan are validated.') . '</p>';
    $variables['p_6_3'] = '<p><strong>' .  $values['6_3a'] . '</strong>' . t(' will formally sign off the HACCP plan.') . '</p>';
  } elseif ($values['6_3'] == 'yes') {
    $variables['p_6_2'] = '<p><strong>' . $values['6_2'] . '</strong>' . t(' is responsible for ensuring the contents of the HACCP plan are validated and will  also formally sign off the HACCP plan.') . '</p>';
  }

  $variables['p_6_4_title'] = t('The following verification activities are undertaken:');

  // @todo need the checkbox labels here

  // 7. How often is the HACCP system formally reviewed?
  $variables['p_6_7'] = t('The HACCP system is formally reviewed <strong>') . $values['6_7'] . '</strong>.';

  // 8. Who is responsible for carrying out a formal annual review?
  $variables['p_6_8'] = '<strong>' . $values['6_8'] . t('</strong> is responsible for carrying out a formal annual review.');

}
