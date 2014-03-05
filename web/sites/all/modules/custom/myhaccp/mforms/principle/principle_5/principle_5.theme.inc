<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_principle_5().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_principle_5(&$variables) {
  $stage = 'principle_5';
  $values = $variables['data'][$stage];

  // Get details of all Hazards.
  $hazards = Hazards::getInstance();
  $by_step = $hazards->getHazardsByStep();

  // Table header.
  $header = array(
    array('data' => t('Process step')),
    array('data' => t('Step no.')),
    array('data' => t('Hazard')),
    array('data' => t('Control measure')),
    array('data' => t('Critical limit')),
    array('data' => t('Monitoring procedures')),
    array('data' => t('Corrective action'))
  );

  foreach($hazards->hazards as $h_key => $hazard) {
    if($hazard->ccp) {
      // Critical limit.
      $critical_limit = myhaccp_principle_3_cl($h_key);

      $rows[] = array(
        // Process step
        array('data' => $hazards->hazards[$h_key]->step->name),
        // Step no.
        array('data' => $hazards->hazards[$h_key]->step->no),
        // Hazard.
        array('data' => $hazards->hazards[$h_key]->name),
        // Control measure.
        array('data' => $hazards->hazards[$h_key]->controlMeasure),
        // Critical limit.
        array('data' => $critical_limit),
        // Monitoring procedures
        array('data' => 'MP'),
        // Corrective action
        array('data' => 'CA')
      );
    }
  }

  // Generate the table through a theme function.
  $variables['p_5_table'] = theme('table', array('header' => $header, 'rows' => $rows));

}
