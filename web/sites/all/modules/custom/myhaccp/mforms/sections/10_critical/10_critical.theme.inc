<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_principle_3().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_10_critical(&$variables) {
  $study = $variables['study'];
  $data = $study->getStage('principle_3')->getData();
  $principle_3 = $data['principle_3'];

  // Get details of all Hazards.
  $hazards = Hazards::getInstance();

  // Table header.
  $header = array(
    array('data' => t('Step No.')),
    array('data' => t('Step Name.')),
    array('data' => t('Hazard')),
    array('data' => t('Critical limit')),
    array('data' => t('How was the critical limit determined?')),
    array('data' => t('Will the critical limit control the specific hazard?')),
    array('data' => t('Can the critical limit be measured or observed in real time?'))
  );

  // Generate table row for each hazard.
  foreach ($principle_3 as $h_key => $ccp_hazard) {
    // Only generate a row if there is a control measure set.
    if (!empty($hazards->hazards[$h_key]->controlMeasure)) {
      $rows[] = array(
        // Step No.
        array('data' => $hazards->hazards[$h_key]->step->no),
        // Step Name.
        array('data' => $hazards->hazards[$h_key]->step->name),
        // Hazard.
        array('data' => $hazards->hazards[$h_key]->name),
        // Critical limit.
        array('data' => nl2br($ccp_hazard['3_1'])),
        // How was the critical limit determined?
        array('data' => nl2br($ccp_hazard['3_2'])),
        // Will the critical limit control the specific hazard?
        array('data' => $ccp_hazard['3_3'] == 'yes' ? t('Yes', array(), array('context' => 'Will the critical limit control the specific hazard?')) : t('No', array(), array('context' => 'Will the critical limit control the specific hazard?'))),
        // Can the critical limit be measured or observed in real time?
        array('data' => $ccp_hazard['3_4'] == 'yes' ? t('Yes') : t('No'))
      );
    }
  }

  // Generate the table through a theme function.
  $variables['p_3_table'] = theme('table', array('header' => $header, 'rows' => $rows));
}
