<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_principle_2_2().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_principle_2_2(&$variables) {
  $stage = 'principle_2_2';
  $values = $variables['data'][$stage];

  // Get details of all Hazards.
  $hazards = Hazards::getInstance();

  // Table header.
  $header = array(
    array('data' => t('Step No.')),
    array('data' => t('Hazard')),
    array('data' => t('Control Measures')),
    array('data' => t('Decision Tree')),
    array('data' => t('CCP?'))
  );

  // Generate table row for each hazard.
  foreach ($values['instance_table'] as $h_key => $controlled_hazard) {
    // Format Questions & Answers to Decision Tree.
    $qa = '';
    foreach ($controlled_hazard['decision_tree'] as $q => $answer) {
      if(!empty($answer)) {
        $qa .= '<strong>' . $q . ':</strong> ' . ucwords($answer) . '<br />';
      }
    }

    // Uppercase CCP answer.
    if(!empty($controlled_hazard['ccp'])) {
      $ccp = ucwords($controlled_hazard['ccp']);
    }

    $rows[] = array(
      // Step No.
      array('data' => $hazards->hazards[$h_key]->step->no),
      // Hazard.
      array('data' => $hazards->hazards[$h_key]->name),
      // Control Measures.
      array('data' => $hazards->hazards[$h_key]->controlMeasure),
      // Decision Tree question answers
      array('data' => $qa),
      // CCP?
      array('data' => $ccp)
    );
  }

  // Generate the table through a theme function.
  $variables['p_2_2_table'] = theme('table', array('header' => $header, 'rows' => $rows));

}
