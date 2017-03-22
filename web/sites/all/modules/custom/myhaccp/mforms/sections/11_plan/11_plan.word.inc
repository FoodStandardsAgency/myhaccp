<?php

/**
 * @file
 * Theme function for stage 11.
 *
 * Prepares the passed form_state data and processes it for output.
 */

use \PhpOffice\PhpWord\Shared\Html;

/**
 * Preprocess function for 11_plan.
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_word_11_plan($study, $section) {
  /** @var \PhpOffice\PhpWord\Element\Section $section */
  $data = $study->getStage('principle_5')->getData();
  $principle_5 = $data['principle_5'];

  if (myhaccp_check_ccps() == FALSE) {
    $variables['p_5_table'] = '<h3>' . t('There are no Critical Control Points') . '</h3>';
    return;
  }

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
    array('data' => t('Process step')),
    array('data' => t('Step no.')),
    array('data' => t('Hazard')),
    array('data' => t('Control measure')),
    array('data' => t('Critical limit')),
    array('data' => t('Monitoring procedures')),
    array('data' => t('Corrective action')),
  );

  foreach ($header as $header_item) {
    $table->addCell(NULL, $cell_style)->addText($header_item['data'], array(
      'bold' => TRUE,
    ));
  }

  $rows = array();

  foreach ($hazards->hazards as $h_key => $hazard) {
    if ($hazard->ccp) {
      // Critical limit information for hazard.
      $critical_limit = _principle_3_cl($study, $h_key);

      // Monitoring procedures information for hazard.
      $monitoring_procedures = _principle_4_m($study, $h_key);

      // Corrective action information for hazard.
      $corrective_action = _principle_5_mp($study, $h_key);

      $rows[] = array(
        // Process step.
        array('data' => $hazards->hazards[$h_key]->step->name),
        // Step no.
        array('data' => $hazards->hazards[$h_key]->step->no),
        // Hazard.
        array('data' => $hazards->hazards[$h_key]->name),
        // Control measure.
        array('data' => nl2p(check_plain($hazards->hazards[$h_key]->controlMeasure), FALSE)),
        // Critical limit.
        array('data' => $critical_limit),
        // Monitoring procedures.
        array('data' => $monitoring_procedures),
        // Corrective action.
        array('data' => $corrective_action),
      );
    }
  }

  foreach ($rows as $row) {
    $table->addRow();
    foreach ($row as $cell_content) {
      $cell = $table->addCell(NULL);
      Html::addHtml($cell, $cell_content['data']);
    }
  }
}

/**
 * Returns formatted critical limit information for a hazard.
 *
 * @param Study $study
 *   The study object.
 * @param string $h_key
 *   The key of the Hazard.
 *
 * @return string
 *   The prepared HTML output.
 */
function _principle_3_cl(Study $study, $h_key) {
  $data = $study->getStage('principle_3')->getData();
  $principle_3 = $data['principle_3'];

  $content = '';
  if ($h_key) {
    // 1. What is the critical limit for this critical control
    // point (what separates safe from potentially unsafe product)?
    if (!empty($principle_3[$h_key]['3_1'])) {
      $content .= '<p><strong>' . check_plain($principle_3[$h_key]['3_1']) . '</strong></p>';
    }

    // Is there a target value?
    if (!empty($values[$h_key]['3_6'])) {
      $content .= '<p><strong>Target value:</strong> ' . check_plain($principle_3[$h_key]['3_6']) . '</p>';
    }

    if (!empty($values[$h_key]['3_7'])) {
      $content .= '<p><strong>Tolerances:</strong> ' . check_plain($principle_3[$h_key]['3_7']) . '</p>';
    }

    return $content;
  }
}


/**
 * Returns monitoring procedures for a hazard.
 *
 * @param Study $study
 *   The study object.
 * @param string $h_key
 *   The key of the Hazard.
 *
 * @return string
 *   The prepared HTML output.
 */
function _principle_4_m(Study $study, $h_key) {
  $data = $study->getStage('principle_4')->getData();
  $principle_4 = $data['principle_4'];

  $content = '';

  if ($h_key) {
    // 1. What monitoring activities are going to take place at this CCP?
    if (!empty($principle_4[$h_key]['4_1'])) {
      $content .= '<p>' . nl2br(strip_tags(htmlspecialchars($principle_4[$h_key]['4_1'])), TRUE) . '</p>';
    }

    // 2. Specify how frequently the monitoring activities are to be carried out.
    if (!empty($principle_4[$h_key]['4_2'])) {
      $content .= '<p>' . t('Monitoring activity frequency') . ': ' . nl2br(strip_tags(htmlspecialchars($principle_4[$h_key]['4_2'])), TRUE) . '</p>';
    }

    // 3. Define how the monitoring activities are carried out.
    if (!empty($principle_4[$h_key]['4_3'])) {
      $content .= '<p>' . t('How the monitoring activities are carried out') . ': ' . nl2br(strip_tags(htmlspecialchars($principle_4[$h_key]['4_3'])), TRUE) . '</p>';
    }

    // 4. Who is responsible for monitoring actions at this CCP?
    if (!empty($principle_4[$h_key]['4_4'])) {
      $content .= '<p>' . t('The following people are responsible for monitoring actions at this CCP') . ': ' . nl2br(strip_tags(htmlspecialchars($principle_4[$h_key]['4_4'])), TRUE) . '</p>';
    }

    // 5. Please state the name and job title of the deputy if applicable:
    if (!empty($principle_4[$h_key]['4_5'])) {
      $content .= '<p>' . t('The deputy is') . ': ' . strip_tags(htmlspecialchars($principle_4[$h_key]['4_5'])) . '</p>';
    }

    // 6. Where are the results of monitoring recorded?
    if (!empty($principle_4[$h_key]['4_6'])) {
      $content .= '<p>' . t('The results of monitoring are recorded') . ': ' . strip_tags(htmlspecialchars($principle_4[$h_key]['4_6'])) . '</p>';
    }

    // 7. Will the monitoring records be checked and signed off by anyone?
    if (!empty($principle_4[$h_key]['4_7']) && $principle_4[$h_key]['4_7'] == 'yes') {
      if (!empty($principle_4[$h_key]['4_7a']) && !empty($principle_4[$h_key]['4_7b'])) {
        $content .= '<p>' . t('Monitoring records will be checked and signed off by') . ' <strong>' . $principle_4[$h_key]['4_7a'] . '</strong> ' . t('at the frequency of') . ': <strong>' . $principle_4[$h_key]['4_7b'] . '</strong></p>';
      }
    }
    elseif (!empty($principle_4[$h_key]['4_7']) && $principle_4[$h_key]['4_7'] == 'no') {
      $content .= '<p>' . t('Monitoring records will not be checked and signed off by anyone.') . '</p>';
    }

    return $content;

  }

}

/**
 * Returns formatted critical limit information for a hazard.
 *
 * @param Study $study
 *   The study object.
 * @param string $h_key
 *   The key of the Hazard.
 *
 * @return string
 *   The prepared HTML output.
 */
function _principle_5_mp(Study $study, $h_key) {
  $data = $study->getStage('principle_5')->getData();
  $principle_5 = $data['principle_5'];

  $content = '';

  if ($h_key) {
    // 1. Corrective action to be taken.
    if (!empty($principle_5[$h_key]['5_1'])) {
      $content .= '<p>' . t('Corrective action to be taken') . ': ' . nl2br(strip_tags(htmlspecialchars($principle_5[$h_key]['5_1'])), TRUE) . '</p>';
    }

    // 2. Detail personnel who have the authority to take the stated
    // corrective action.
    if (!empty($principle_5[$h_key]['5_2'])) {
      $content .= '<p>' . t('Personnel who have the authority to take the stated corrective action') . ': ' . nl2br(strip_tags(htmlspecialchars($principle_5[$h_key]['5_2'])), TRUE) . '</p>';
    }

    // 3. What happens to the product created during the period that a CCP was
    // out of control? Detail any variation in handling this product that
    // relates to, a parameter, eg degree of control lost.
    if (!empty($principle_5[$h_key]['5_3'])) {
      $content .= '<p>' . nl2br(strip_tags(htmlspecialchars($principle_5[$h_key]['5_3'])), TRUE) . '</p>';
    }

    // 4. Where are you going to document what you have done with the product
    // produced during the time period that a CCP was 'out of control' (for
    // example since the last good check)?
    if (!empty($principle_5[$h_key]['5_4'])) {
      $content .= '<p>' . t('Actions for product produced when the CPP was out of control will be recorded in') . ': ' . nl2br(strip_tags(htmlspecialchars($principle_5[$h_key]['5_4'])), TRUE) . '</p>';
    }

    // 5. Are all personnel (identified in any of the steps from 1-6 for all
    // CCP’s) trained and competent for performing the activities stated?
    if (!empty($principle_5[$h_key]['5_5']) && $principle_5[$h_key]['5_5'] == 'yes') {
      $content .= '<p>' . t('All personnel are trained and competent for performing the activities stated.') . '</p>';
    }

    // 6. Are records of competency maintained?
    if (!empty($principle_5[$h_key]['5_6']) && $principle_5[$h_key]['5_6'] == 'yes') {
      $content .= '<p>' . t('Records of competency are maintained.') . '</p>';
    }

    return $content;

  }
}
