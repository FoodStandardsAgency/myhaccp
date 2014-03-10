<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_principle_4().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_principle_4(&$variables) {
  $stage = 'principle_4';
  $values = $variables['data'][$stage];

}

/**
 *
 * Return monitoring procedures for a hazard.
 *
 * @param string $h_key
 *   The key of the Hazard.
 */

function myhaccp_principle_4_m($h_key) {
  $data = mforms_get_vals('myhaccp', 'principle_4');
  $values = $data['principle_4'];

  $content ='';

  if($h_key) {
    // 1. What monitoring activities are going to take place at this CCP?
    if(!empty($values[$h_key]['4_1'])) {
      $content .= '<p>' . nl2br($values[$h_key]['4_1']) . '</p><br />';
    }

    // 2. Specify how frequently the monitoring activities are to be carried out.
    if(!empty($values[$h_key]['4_2'])) {
      $content .= '<p>Monitoring activity frequency: ' . nl2br($values[$h_key]['4_2']) . '</p><br />';
    }

    // 3. Define how the monitoring activities are carried out.
    if(!empty($values[$h_key]['4_3'])) {
      $content .= '<p>How the monitoring activities are carried out: ' . nl2br($values[$h_key]['4_3']) . '</p><br />';
    }

    // 4. Who is responsible for monitoring actions at this CCP?
    if(!empty($values[$h_key]['4_4'])) {
      $content .= '<p>The following people are responsible for monitoring actions at this CCP: ' . nl2br($values[$h_key]['4_4']) . '</p><br />';
    }

    // 5. Please state the name and job title of the deputy if applicable:
    if(!empty($values[$h_key]['4_5'])) {
      $content .= '<p>The deputy is: ' . $values[$h_key]['4_5'] . '</p><br />';
    }

    // 6. Where are the results of monitoring recorded?
    if(!empty($values[$h_key]['4_6'])) {
      $content .= '<p>The results of monitoring are recorded: ' . $values[$h_key]['4_6'] . '</p><br />';
    }

    // 7. Will the monitoring records be checked and signed off by anyone?
    if(!empty($values[$h_key]['4_7']) && $values[$h_key]['4_7'] == 'yes') {
      if(!empty($values[$h_key]['4_7a']) && !empty($values[$h_key]['4_7b'])) {
        $content .= '<p>Monitoring records will be checked and signed off by <strong>' . $values[$h_key]['4_7a'] . '</strong> at the frequency of: <strong>' . $values[$h_key]['4_7b'] .  '</strong></p><br />';
      }
    } elseif(!empty($values[$h_key]['4_7']) && $values[$h_key]['4_7'] == 'no') {
      $content .= '<p>Monitoring records will not be checked and signed off by anyone.</p><br />';
    }

    return $content;

  }

}
