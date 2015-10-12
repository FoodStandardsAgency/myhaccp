<?php

/**
 * @file
 * Theme function for stage 6.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_06_identify().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_06_identify(&$variables) {
  $study = $variables['study'];
  $data = $study->getStage('principle_1_1')->getData();
  $principle_1_1 = $data['principle_1_1'];

  $steps = array();

  // Find all steps.
  // Arrays with 'instance' in the key are a step.
  foreach ($principle_1_1 as $key => $value) {
    if (strpos($key, 'instance') === 0) {
      $steps[] = $value;
    }
  }

  // Now generate a table of hazards per step.

  // First the table headers.
  $header = array(
    array('data' => t('Step No.')),
    array('data' => t('Step Name')),
    array('data' => t('Biological')),
    array('data' => t('Chemical')),
    array('data' => t('Physical')),
    array('data' => t('Allergens'))
  );

  // Now the table rows.
  foreach ($steps as $step) {
    // Steps must have a number and name.
    if (!empty($step['wrapper']['step_no']) && !empty($step['wrapper']['step_name'])) {
      // Split hazards on new lines using <br />
      $biological = nl2br($step['hazards_wrapper']['biological']);
      $chemical = nl2br($step['hazards_wrapper']['chemical']);
      $physical = nl2br($step['hazards_wrapper']['physical']);
      $allergens = nl2br($step['hazards_wrapper']['allergens']);

      $rows[] = array(
        // Step No.
        array('data' => $step['wrapper']['step_no']),
        // Step Name.
        array('data' => $step['wrapper']['step_name']),
        // Biological.
        array('data' => $biological),
        // Chemical.
        array('data' => $chemical),
        // Physical.
        array('data' => $physical),
        // Allergens.
        array('data' => $allergens)
      );
    }
  }

  // Generate the table through a theme function.
  $variables['p_1_hazard_tables'] = theme('table', array('header' => $header, 'rows' => $rows));

}
