<?php

/**
 * @file
 * Theme function for stage 8.
 *
 * Prepares the passed form_state data and processes it for output.
 */

use \PhpOffice\PhpWord\Shared\Html;

/**
 * Preprocess function for 08_control.
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_word_08_control($study, $section) {
  /** @var \PhpOffice\PhpWord\Element\Section $section */
  $data = $study->getStage('principle_1_3')->getData();
  $principle_1_3 = $data['principle_1_3'];

  // Get details of all Hazards.
  $hazards = Hazards::getInstance();
  $by_step = $hazards->getHazardsByStep();

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
    array('data' => t('Step Name.')),
    array('data' => t('Hazard')),
    array('data' => t('Hazard Description')),
    array('data' => t('Control Measures')),
  );

  foreach ($header as $header_item) {
    $table->addCell(NULL, $cell_style)->addText($header_item['data'], array(
      'bold' => TRUE,
    ));
  }

  $rows = array();

  // Generate table row for each hazard.
  foreach ($principle_1_3['instance_table'] as $h_key => $controlled_hazard) {
    // Only generate a row if there is a control measure set.
    if (!empty($hazards->hazards[$h_key]->controlMeasure)) {
      $rows[] = array(
        // Step No.
        array('data' => $hazards->hazards[$h_key]->step->no),
        // Step Name.
        array('data' => $hazards->hazards[$h_key]->step->name),
        // Hazard.
        array('data' => $hazards->hazards[$h_key]->name),
        // Hazard Description.
        array('data' => nl2p($hazards->hazards[$h_key]->description, FALSE)),
        // Control Measure.
        array('data' => nl2p($hazards->hazards[$h_key]->controlMeasure, FALSE)),
      );
    }
  }

  foreach ($rows as $row) {
    $table->addRow();
    foreach($row as $cell_content) {
      $cell = $table->addCell(NULL);
      Html::addHtml($cell, $cell_content['data']);
    }
  }

}
