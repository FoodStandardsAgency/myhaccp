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
      // Critical limit information for hazard.
      $critical_limit = myhaccp_principle_3_cl($h_key);

      // Monitoring procedures information for hazard.
      $monitoring_procedures = myhaccp_principle_4_m($h_key);

      // Corrective action information for hazard.
      $corrective_action = myhaccp_principle_5_mp($h_key);

      $rows[] = array(
        // Process step
        array('data' => $hazards->hazards[$h_key]->step->name),
        // Step no.
        array('data' => $hazards->hazards[$h_key]->step->no),
        // Hazard.
        array('data' => $hazards->hazards[$h_key]->name),
        // Control measure.
        array('data' => nl2br($hazards->hazards[$h_key]->controlMeasure)),
        // Critical limit.
        array('data' => $critical_limit),
        // Monitoring procedures
        array('data' => $monitoring_procedures),
        // Corrective action
        array('data' => $corrective_action)
      );
    }
  }

  // Generate the table through a theme function.
  $variables['p_5_table'] = theme('table', array('header' => $header, 'rows' => $rows));

}

/**
 *
 * Return formatted critical limit information for a hazard.
 *
 * @param string $h_key
 *   The key of the Hazard.
 */
function myhaccp_principle_5_mp($h_key) {
  $data = mforms_get_vals('myhaccp', 'principle_5');
  $values = $data['principle_5'];

  $content ='';

  if($h_key) {
    // 1. Corrective action to be taken.
    if(!empty($values[$h_key]['5_1'])) {
      $content .= '<p>Corrective action to be taken: ' . nl2br($values[$h_key]['5_1']) . '</p>';
    }

    // 2. Detail personnel who have the authority to take the stated corrective action.
    if(!empty($values[$h_key]['5_2'])) {
      $content .= '<p>Personnel who have the authority to take the stated corrective action: ' . nl2br($values[$h_key]['5_2']) . '</p>';
    }

    // 3. What happens to the product created during the period that a CCP was out of control? Detail any variation in handling this product that relates to, a parameter, eg degree of control lost.
    if(!empty($values[$h_key]['5_3'])) {
      $content .= '<p>' . nl2br($values[$h_key]['5_3']) . '</p>';
    }

    // 4. Where are you going to document what you have done with the product produced during the time period that a CCP was 'out of control' (for example since the last good check)?
    if(!empty($values[$h_key]['5_4'])) {
      $content .= '<p>' . nl2br($values[$h_key]['5_4']) . '</p>';
    }

    // 5. Are all personnel (identified in any of the steps from 1-6 for all CCP’s) trained and competent for performing the activities stated?
    if(!empty($values[$h_key]['5_5']) && $values[$h_key]['5_5'] == 'yes') {
      $content .= '<p>' . t('All personnel are trained and competent for performing the activities stated.') . '</p>';
    }

    // 6. Are records of competency maintained?
    if(!empty($values[$h_key]['5_6']) && $values[$h_key]['5_6'] == 'yes') {
      $content .= '<p>' . t('Records of competancy are maintained.') . '</p>';
    }

    return $content;

  }

}
