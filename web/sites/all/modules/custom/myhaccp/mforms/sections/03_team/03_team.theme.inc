<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_preparatory_d().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_03_team(&$variables) {
  $study = $variables['study'];
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

    // First the table headers.
    $header = array(
      array('data' => t('Role')),
      array('data' => t('Name')),
      array('data' => t('Training')),
      array('data' => t('Qualifications')),
      array('data' => t('Experience'))
    );

    // Now the table rows.
    foreach ($instances as $instance) {

      $role = !empty($instance['d_3']) ? $instance['d_3'] : '';
      $name = !empty($instance['d_1']) ? $instance['d_1'] : '';
      // Add 'internal' or 'external' below name.
      $name .= !empty($instance['d_2']) ? '<br /><em>(' . $instance['d_2'] . ')</em>' : '';
      $training = !empty($instance['wrapper']['d_4']) ? $instance['wrapper']['d_4'] : '';
      $qualifications = !empty($instance['wrapper']['d_5']) ? $instance['wrapper']['d_5'] : '';
      $experience = !empty($instance['wrapper']['d_5']) ? $instance['wrapper']['d_6'] : '';

      $rows[] = array(
        array('data' => $role),
        array('data' => $name),
        array('data' => $training),
        array('data' => $qualifications),
        array('data' => $experience)
      );
    }

    // Generate the table through a theme function.
    $variables['d_1_team'] = theme('table', array('header' => $header, 'rows' => $rows));
  }

  // Team skills.
  if (!empty($preparatory_d['team_skills']) && $preparatory_d['team_skills'] == 'Yes') {
    $variables['d_1_team_skills'] = '<p>' . t('We confirm that the team have sufficient skills (scientific/technical knowledge and HACCP expertise) to ensure that the HACCP study will be effective.') . '</p>';
  }
  elseif (!empty($preparatory_d['team_skills']) && !empty($preparatory_d['team_no_skills']) && $preparatory_d['team_skills'] == 'No') {
    $variables['d_1_team_skills'] = '<p>' . t('The team do not have sufficient skills (scientific/technical knowledge and HACCP expertise) to ensure that the HACCP study will be effective. We plan to address this issue in the following way:') . '</p><p>' . $preparatory_d['team_no_skills'] . '</p>';
  }

}
