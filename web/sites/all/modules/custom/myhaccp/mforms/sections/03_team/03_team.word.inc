<?php

/**
 * @file
 * Theme function for stage 3.
 *
 * Prepares the passed form_state data and processes it for output.
 */

use \PhpOffice\PhpWord\Shared\Html;

/**
 * Preprocess function for 03_team.
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_word_03_team($study, $section) {
  /** @var \PhpOffice\PhpWord\Element\Section $section */
  $data = $study->getStage('preparatory_d')->getData();
  $preparatory_d = $data['preparatory_d'];

  $instances = array();

  // Find all instances.
  // Each instance = one team member.
  foreach ($preparatory_d as $key => $value) {
    if (strpos($key, 'instance') === 0) {
      $instances[] = $value;
    }
  }

  // Generate a table of team members.
  if (!empty($instances)) {

    $table = $section->addTable(array(
      'borderSize' => 1,
      'borderColor' => 'DDDDDD',
      'cellMargin' => 80,
      'width' => 100 * 50,
      'unit' => 'pct',
    ));
    $table->addRow();
    $cell_style = array('valign' => 'center', 'bgColor' => 'EEEEEE');

    // First the table headers.
    $header = array(
      array('data' => t('Role')),
      array('data' => t('Name')),
      array('data' => t('Training')),
      array('data' => t('Qualifications')),
      array('data' => t('Experience')),
    );

    foreach ($header as $header_item) {
      $table->addCell(NULL, $cell_style)->addText($header_item['data'], array(
        'bold' => TRUE,
      ));
    }

    $rows = array();

    // Now the table rows.
    foreach ($instances as $key => $instance) {
      // The first instance will always be the HACCP lead so provide the
      // the text.
      if ($key === 0) {
        $instance['d_2'] = t('internal');
        $instance['d_3'] = t('HACCP lead');
      }

      $role = !empty($instance['d_3']) ? $instance['d_3'] : '';
      $name = !empty($instance['d_1']) ? $instance['d_1'] : '';
      // Add 'internal' or 'external' below name.
      if (!empty($instance['d_2'])) {
        $internal_external = $instance['d_2'] == 'internal' ? t('Internal') : t('External');
        $name .= '<br /><em>(' . $internal_external . ')</em>';
      }
      $training = !empty($instance['wrapper']['d_4']) ? $instance['wrapper']['d_4'] : '';
      $qualifications = !empty($instance['wrapper']['d_5']) ? $instance['wrapper']['d_5'] : '';
      $experience = !empty($instance['wrapper']['d_5']) ? $instance['wrapper']['d_6'] : '';

      $rows[] = array(
        array('data' => $role),
        array('data' => $name),
        array('data' => $training),
        array('data' => $qualifications),
        array('data' => $experience),
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

  // Team skills.
  if (!empty($preparatory_d['team_skills']) && $preparatory_d['team_skills'] == 'Yes') {
    $variables['d_1_team_skills'] = '<p>' . t('We confirm that the team have sufficient skills (scientific/technical knowledge and HACCP expertise) to ensure that the HACCP study will be effective.') . '</p>';
  }
  elseif (!empty($preparatory_d['team_skills']) && !empty($preparatory_d['team_no_skills']) && $preparatory_d['team_skills'] == 'No') {
    $variables['d_1_team_skills'] = '<p>' . t('The team do not have sufficient skills (scientific/technical knowledge and HACCP expertise) to ensure that the HACCP study will be effective. We plan to address this issue in the following way:') . '</p><p>' . $preparatory_d['team_no_skills'] . '</p>';
  }

  $section->addTextBreak(1, 'fs', 'ps');
  Html::addHtml($section, $variables['d_1_team_skills']);

}
