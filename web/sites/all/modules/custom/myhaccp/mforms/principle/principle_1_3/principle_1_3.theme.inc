<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_principle_1_3().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_principle_1_3(&$variables) {
  $stage = 'principle_1_3';
  $values = $variables['data'][$stage];

  // Get details of all Hazards.
  $hazards = Hazards::getInstance();
  $by_step = $hazards->getHazardsByStep();

  // Table header.
  $header = array(
    array('data' => t('Step No.')),
    array('data' => t('Hazard')),
    array('data' => t('Hazard Description')),
    array('data' => t('Significance (S x L)')),
    array('data' => t('Control Measures'))
  );

  // Generate table row for each hazard.
  foreach ($values['instance_table'] as $h_key => $controlled_hazards) {
    $rows[] = array(
      // Step No.
      array('data' => $hazards->hazards[$h_key]->step->no),
      // Hazard.
      array('data' => $hazards->hazards[$h_key]->name),
      // Hazard Description.
      array('data' => $hazards->hazards[$h_key]->description),
      // Significance.
      array('data' => $hazards->hazards[$h_key]->significance),
      // Control Measure.
      array('data' => $hazards->hazards[$h_key]->controlMeasure)
    );
  }

  // Generate the table through a theme function.
  $variables['p_1_3_table'] = theme('table', array('header' => $header, 'rows' => $rows));

}
