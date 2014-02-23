<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_principle_1_2().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_principle_1_2(&$variables) {
  // @todo add step no. and name to array

  $stage = 'principle_1_2';
  $values = $variables['data'][$stage];

  $header = array(
    array('data' => t('Hazard')),
    array('data' => t('Hazard Description')),
    array('data' => t('Severity 1-3')),
    array('data' => t('Likelihood')),
    array('data' => t('Significance'))
  );

  // Generate table for each step
  foreach ($values as $key => $step) {
    // Ignore this item if it's the threshold
    if ($key == 'threshold') {
      break;
    }

    // Reset the rows variable
    $rows = array();

    // Add each hazard to a new table row
    foreach ($step['instance_table'] as $hazard) {
      $rows[] = array(
        // Hazard
        array('data' => $hazard['name']),
        // Hazard Description
        array('data' => $hazard['description']),
        // Severity
        array('data' => $hazard['severity']),
        // Likelihood
        array('data' => $hazard['likelihood']),
        // Significance
        array('data' => $hazard['significance'])
      );

      // Generate the table through a theme function
      $step_ha_tables[$key] = theme('table', array('header' => $header, 'rows' => $rows));

      // Add the step name as a heading
      // @todo add step name, using key for the moment
      $step_ha_tables[$key] = '<h3>' . $key . '</h3>' . $step_ha_tables[$key];
    }

  }

  // Add all the tables together into one variable
  $variables['p_1_2_hazard_table'] = '<div>' . implode('</div><div>', $step_ha_tables) . '</div>';

  // Threshold
  $variables['p_1_2_threshold'] = t('The threshold, above which we consider the hazard to be \'significant\' is: <span class="p-1-2-threshold">') . $values['threshold'] . '</span>';
}
