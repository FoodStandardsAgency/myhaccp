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
function myhaccp_preprocess_principle_3(&$variables) {
  $stage = 'principle_3';
  $values = $variables['data'][$stage];

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
  foreach ($values as $h_key => $ccp_hazard) {
    // Only generate a row if there is a control measure set.
    if(!empty($hazards->hazards[$h_key]->controlMeasure)) {
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
        array('data' => ucwords($ccp_hazard['3_3'])),
        // Can the critical limit be measured or observed in real time?
        array('data' => ucwords($ccp_hazard['3_4']))
      );
    }
  }

  // Generate the table through a theme function.
  $variables['p_3_table'] = theme('table', array('header' => $header, 'rows' => $rows));


}

/**
 *
 * Return formatted critical limit information for a hazard.
 *
 * @param string $h_key
 *   The key of the Hazard.
 */
function myhaccp_principle_3_cl($h_key) {
  $data = mforms_get_vals('myhaccp', 'principle_3');
  $values = $data['principle_3'];

  $content ='';
  if($h_key) {
    // 1. What is the critical limit for this critical control point (what separates safe from potentially unsafe product)?
    if(!empty($values[$h_key]['3_1'])) {
      $content .= '<p><strong>' . $values[$h_key]['3_1'] . '</strong></p><br />';
    }

    // Is there a target value?
    if(!empty($values[$h_key]['3_6'])) {
      $content .= '<p><strong>Target value:</strong> ' . $values[$h_key]['3_6'] . '</p><br />';
    }

    if(!empty($values[$h_key]['3_7'])) {
      $content .= '<p><strong>Tolerances:</strong> ' . $values[$h_key]['3_7'] . '</p>';
    }

    return $content;
  }
}
