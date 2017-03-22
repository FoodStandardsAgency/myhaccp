<?php

/**
 * @file
 * Theme function for stage 9.
 *
 * Prepares the passed form_state data and processes it for output.
 */

use \PhpOffice\PhpWord\Shared\Html;

/**
 * Preprocess function for 09_ccps.
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_word_09_ccps($study, $section) {
  /** @var \PhpOffice\PhpWord\Element\Section $section */
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

  if (!empty($variables['p_2_1_1'])) {
    Html::addHtml($section, '<p>' . $variables['p_2_1_1'] . '</p>');
    $section->addTextBreak(1, 'fs', array('spaceAfter' => '100'));
  }

  if (!empty($variables['p_2_1_1a'])) {
    Html::addHtml($section, '<p>' . $variables['p_2_1_1a'] . '</p>');
    $section->addTextBreak(1, 'fs', array('spaceAfter' => '100'));
  }

  // Get details of all Hazards.
  $hazards = Hazards::getInstance();

  $table = $section->addTable(array(
    'borderSize' => 1,
    'borderColor' => 'DDDDDD',
    'cellMargin' => 80,
    'width' => 100 * 50,
    'unit' => 'pct',
  ));
  $table->addRow();
  $cell_style = array('valign' => 'center', 'bgColor' => 'EEEEEE');

  // Table header.
  $header = array(
    array('data' => t('Step No.')),
    array('data' => t('Hazard')),
    array('data' => t('Control Measures')),
    array('data' => t('Decision Tree')),
    array('data' => t('CCP?')),
  );

  foreach ($header as $header_item) {
    $table->addCell(NULL, $cell_style)->addText($header_item['data'], array(
      'bold' => TRUE,
    ));
  }

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
          $qa .= '<p><strong>' . $q . ':</strong> ' . $answer . '</p>';
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
      array('data' => nl2p($hazards->hazards[$h_key]->controlMeasure, FALSE)),
      // Decision Tree question answers.
      array('data' => $qa),
      // CCP?
      array('data' => $ccp),
    );
  }

  foreach ($rows as $row) {
    $table->addRow();
    foreach($row as $cell_content) {
      $cell = $table->addCell(NULL);
      Html::addHtml($cell, $cell_content['data']);
    }
  }

}
