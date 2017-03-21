<?php

/**
 * @file
 * Theme function for stage 6.
 *
 * Prepares the passed form_state data and processes it for output.
 */

use \PhpOffice\PhpWord\Shared\Html;

/**
 * Preprocess function for 06_identify.
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_word_06_identify($study, $section) {
  /** @var \PhpOffice\PhpWord\Element\Section $section */
  $data = $study->getStage('principle_1_1')->getData();
  $principle_1_1 = $data['principle_1_1'];

  $steps = array();

  // Find all steps.
  // Arrays with 'instance' in the key are a step.
  foreach ($principle_1_1 as $key => $value) {
    if (strpos($key, 'instance') === 0) {
      $steps[] = $value;
    }
  }

  $table = $section->addTable(array(
    'borderSize' => 1,
    'borderColor' => 'DDDDDD',
    'cellMargin' => 80,
    'width' => 100 * 50,
    'unit' => 'pct',
  ));
  $table->addRow();
  $cell_style = array('valign' => 'center', 'bgColor' => 'EEEEEE');

  // Now generate a table of hazards per step.
  // First the table headers.
  $header = array(
    array('data' => t('Step No.')),
    array('data' => t('Step Name')),
    array('data' => t('Biological')),
    array('data' => t('Chemical')),
    array('data' => t('Physical')),
    array('data' => t('Allergens')),
  );

  foreach ($header as $header_item) {
    $table->addCell(NULL, $cell_style)->addText($header_item['data'], array(
      'bold' => TRUE,
    ));
  }

  $rows = array();

  // Now the table rows.
  foreach ($steps as $step) {
    // Steps must have a number and name.
    if (!empty($step['wrapper']['step_no']) && !empty($step['wrapper']['step_name'])) {
      // Split hazards on new lines using <br />.
      $biological = nl2p($step['hazards_wrapper']['biological'], FALSE);
      $chemical = nl2p($step['hazards_wrapper']['chemical'], FALSE);
      $physical = nl2p($step['hazards_wrapper']['physical'], FALSE);
      $allergens = nl2p($step['hazards_wrapper']['allergens'], FALSE);

      $rows[] = array(
        // Step No.
        array('data' => $step['wrapper']['step_no']),
        // Step Name.
        array('data' => $step['wrapper']['step_name']),
        // Biological.
        array('data' => $biological),
        // Chemical.
        array('data' => $chemical),
        // Physical.
        array('data' => $physical),
        // Allergens.
        array('data' => $allergens),
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
