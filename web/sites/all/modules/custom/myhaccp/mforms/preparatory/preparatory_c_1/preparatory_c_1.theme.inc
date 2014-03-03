<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_preparatory_c_1().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_preparatory_c_1(&$variables) {
  $stage = 'preparatory_c_1';
  $values = $variables['data'][$stage];

  $variables['c_intro'] = t('This <strong>@c_1</strong> HACCP plan covers:<br/><strong>@c_2</strong><p>
It will start at <strong>@start</strong> through to <strong>@end</strong>.</p>',
    array(
      '@c_1' => $values['c_1'],
      '@c_2' => $values['c_2'],
      '@start' => $values['c_3']['start'],
      '@end' => $values['c_3']['end'],
    )
  );

}
