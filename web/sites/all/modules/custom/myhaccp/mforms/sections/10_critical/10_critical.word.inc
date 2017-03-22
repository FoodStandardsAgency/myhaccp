<?php

/**
 * @file
 * Theme function for stage 10.
 *
 * Prepares the passed form_state data and processes it for output.
 */

use \PhpOffice\PhpWord\Shared\Html;

/**
 * Preprocess function for 10_critical.
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_word_10_critical($study, $section) {
  /** @var \PhpOffice\PhpWord\Element\Section $section */
  $data = $study->getStage('principle_3')->getData();
  $principle_3 = $data['principle_3'];

  if (myhaccp_check_ccps() == FALSE) {
    $variables['p_3_table'] = '<h3>' . t('There are no Critical Control Points') . '</h3>';
    return;
  }
  else {
    $section->addTitle(t('The following critical limits have been established for the CCPs.'), 4);
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
    array('data' => t('Step Name.')),
    array('data' => t('Hazard')),
    array('data' => t('Critical limit')),
    array('data' => t('How was the critical limit determined?')),
    array('data' => t('Will the critical limit control the specific hazard?')),
    array('data' => t('Can the critical limit be measured or observed in real time?')),
  );

  foreach ($header as $header_item) {
    $table->addCell(NULL, $cell_style)->addText($header_item['data'], array(
      'bold' => TRUE,
    ));
  }

  $rows = array();

  // Generate table row for each hazard.
  foreach ($principle_3 as $h_key => $ccp_hazard) {
    // Only generate a row if there is a control measure set.
    if (!empty($hazards->hazards[$h_key]->controlMeasure)) {
      $rows[] = array(
        // Step No.
        array('data' => $hazards->hazards[$h_key]->step->no),
        // Step Name.
        array('data' => check_plain($hazards->hazards[$h_key]->step->name)),
        // Hazard.
        array('data' => $hazards->hazards[$h_key]->name),
        // Critical limit.
        array('data' => nl2p(check_plain($ccp_hazard['3_1'], FALSE))),
        // How was the critical limit determined?
        array('data' => nl2p(check_plain($ccp_hazard['3_2'], FALSE))),
        // Will the critical limit control the specific hazard?
        array(
          'data' => $ccp_hazard['3_3'] == 'yes' ? t('Yes', array(), array(
            'context' => 'Will the critical limit control the specific hazard?',
          )) : t('No', array(), array(
            'context' => 'Will the critical limit control the specific hazard?',
          )),
        ),
        // Can the critical limit be measured or observed in real time?
        array('data' => $ccp_hazard['3_4'] == 'yes' ? t('Yes') : t('No')),
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
