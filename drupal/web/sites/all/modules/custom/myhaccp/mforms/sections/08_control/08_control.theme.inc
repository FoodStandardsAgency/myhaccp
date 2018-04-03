<?php

/**
 * @file
 * Theme function for stage 8.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Preprocess function for 08_control.
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_08_control(&$variables) {
  $study = $variables['study'];
  $data = $study->getStage('principle_1_3')->getData();
  $principle_1_3 = $data['principle_1_3'];

  // Get details of all Hazards.
  $hazards = Hazards::getInstance();
  $by_step = $hazards->getHazardsByStep();

  // Table header.
  $header = array(
    array('data' => t('Step No.')),
    array('data' => t('Step Name.')),
    array('data' => t('Hazard')),
    array('data' => t('Hazard Description')),
    array('data' => t('Control Measures')),
  );

  // Generate table row for each hazard.
  foreach ($principle_1_3['instance_table'] as $h_key => $controlled_hazard) {
    // Only generate a row if there is a control measure set.
    if (!empty($hazards->hazards[$h_key]->controlMeasure)) {
      $rows[] = array(
        // Step No.
        array('data' => $hazards->hazards[$h_key]->step->no),
        // Step Name.
        array('data' => $hazards->hazards[$h_key]->step->name),
        // Hazard.
        array('data' => $hazards->hazards[$h_key]->name),
        // Hazard Description.
        array('data' => nl2br($hazards->hazards[$h_key]->description)),
        // Control Measure.
        array('data' => nl2br($hazards->hazards[$h_key]->controlMeasure)),
      );
    }
  }

  // Generate the table through a theme function.
  $variables['p_1_3_table'] = theme('table', array('header' => $header, 'rows' => $rows));

}
