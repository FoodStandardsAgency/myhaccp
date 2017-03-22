<?php

/**
 * @file
 * Theme function for stage 7.
 *
 * Prepares the passed form_state data and processes it for output.
 */

use \PhpOffice\PhpWord\Shared\Html;

/**
 * Preprocess function for 07_severity.
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_word_07_severity($study, $section) {
  /** @var \PhpOffice\PhpWord\Element\Section $section */
  $data = $study->getStage('principle_1_2')->getData();
  $principle_1_2 = $data['principle_1_2'];

  // Get details of all Hazards.
  $hazards = Hazards::getInstance();
  $by_step = $hazards->getHazardsByStep();

  // Generate table for each step.
  foreach ($principle_1_2 as $key => $step) {
    // Ignore this item if it's the threshold.
    if ($key == 'threshold') {
      break;
    }

    $section->addTextBreak(1, 'fs', 'ps');

    // Add the step no. and name as a heading, from the $by_step object.
    $step_ha_tables[$key] = '<h3>' . $by_step[$key]['no'] . '. ' . $by_step[$key]['name'] . '</h3>';
    Html::addHtml($section, $step_ha_tables[$key]);

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
      array('data' => t('Hazard')),
      array('data' => t('Hazard Description')),
      array('data' => t('Severity')),
      array('data' => t('Likelihood')),
      array('data' => t('Significance')),
    );

    foreach ($header as $header_item) {
      $table->addCell(NULL, $cell_style)->addText($header_item['data'], array(
        'bold' => TRUE,
      ));
    }

    // Reset the rows variable.
    $rows = array();

    // Add each hazard to a new table row.
    foreach ($step['instance_table'] as $h_key => $hazard) {
      $rows[] = array(
        // Hazard name.
        array('data' => $hazards->hazards[$h_key]->name),
        // Hazard Description.
        array('data' => $hazard['description']),
        // Severity.
        array('data' => $hazard['severity']),
        // Likelihood.
        array('data' => $hazard['likelihood']),
        // Significance.
        array('data' => $hazard['significance']),
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

  // Threshold.
  if (!empty($principle_1_2['threshold'])) {
    // Put some space above it.
    $section->addTextBreak(1, 'fs', 'ps');

    $variables['p_1_2_threshold'] = '<p>' . t("The threshold, above which we consider the hazard to be 'significant' is: <strong>") . $principle_1_2['threshold'] . '</strong></p>';
    Html::addHtml($section, $variables['p_1_2_threshold']);
  }
}
