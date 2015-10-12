<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_principle_2_1().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_09_ccps(&$variables) {
  $study = $variables['study'];
  $data = $study->getStage('principle_2_1')->getData();
  $principle_2_1 = $data['principle_2_1'];

  $data = $study->getStage('principle_2_2')->getData();
  $principle_2_2 = $data['principle_2_2'];

  // 1. Are you using a decision tree?
  if (!empty($principle_2_1['2_1_1']) && $principle_2_1['2_1_1'] == 'yes') {
    $variables['p_2_1_1'] = '';
  }
  elseif (!empty($principle_2_1['2_1_1']) && $principle_2_1['2_1_1'] == 'no') {
    $variables['p_2_1_1'] = t('For this study we are not using a decision tree. We are deciding on our CCPS in the following ways:<br />');
    $variables['p_2_1_1'] .= $principle_2_1['2_1_1b'];
  }

  // 1a. Which decision tree are you using?
  if (!empty($principle_2_1['2_1_1a']) && $principle_2_1['2_1_1a'] == 'codex') {
    $variables['p_2_1_1a'] = t('For this study, we are using the <strong>Codex</strong> decision tree.');
  }
  elseif (!empty($principle_2_1['2_1_1a']) && $principle_2_1['2_1_1a'] == 'campden') {
    $variables['p_2_1_1a'] = t('For this study, we are using the <strong>Campden</strong> decision tree.');
  }

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
  foreach ($principle_2_2['instance_table'] as $h_key => $controlled_hazard) {
    // Format Questions & Answers to Decision Tree.
    $qa = '';
    // Its entirely possible the user has no decision tree so check first.
    if (isset($controlled_hazard['decision_tree']) && $controlled_hazard['decision_tree'] !== 'no') {
      foreach ($controlled_hazard['decision_tree'] as $q => $answer) {
        switch ($answer) {
          case 'yes':
            $answer = t('Yes');
            break;

          case 'no':
            $answer = t('No');
            break;

          default:
            $answer = t('N/A');
        }
        if (!empty($answer)) {
          $qa .= '<strong>' . $q . ':</strong> ' . $answer . '<br />';
        }
      }
    }

    // Uppercase CCP answer.
    if (!empty($controlled_hazard['ccp'])) {
      $ccp = $controlled_hazard['ccp'] == 'yes' ? t('Yes') : t('No');
    }

    $rows[] = array(
      // Step No.
      array('data' => $hazards->hazards[$h_key]->step->no),
      // Hazard.
      array('data' => $hazards->hazards[$h_key]->name),
      // Control Measures.
      array('data' => nl2br($hazards->hazards[$h_key]->controlMeasure)),
      // Decision Tree question answers.
      array('data' => $qa),
      // CCP?
      array('data' => $ccp)
    );
  }

  // Generate the table through a theme function.
  $variables['p_2_2_table'] = theme('table', array(
    'header' => $header,
    'rows' => $rows
  ));

}
