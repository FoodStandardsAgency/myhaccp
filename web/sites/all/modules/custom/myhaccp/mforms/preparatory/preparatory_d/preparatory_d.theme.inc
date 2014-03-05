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
function myhaccp_preprocess_preparatory_d(&$variables) {
  $stage = 'preparatory_d';
  $values = $variables['data'][$stage];

  $instances = array();

  // Find all instances
  // Each instance = one team member
  foreach($values as $key => $value) {
    if(strpos($key, 'instance') !== false) {
      $instances[] = $value;
    }
  }

  // Now generate a table of team members

  // First the table headers
  $header = array(
    array('data' => t('Role')),
    array('data' => t('Name')),
    array('data' => t('Training, experience & qualifications'))
  );

  // Now the table rows
  foreach ($instances as $instance) {
    // Generate a single item from training, experience and qualifications questions
    $experience = implode('<br />', array_filter($instance['wrapper']));
    $role = $instance['d_3'] ? $role : '';

    $rows[] = array(
      // Role
      array('data' => $role),
      // Name
      array('data' => $instance['d_1']),
      // Training, experience & qualifications
      array('data' => $experience)
    );
  }

  // Generate the table through a theme function
  $variables['d_1_team'] = theme('table', array('header' => $header, 'rows' => $rows));

  // Team skills
  if ($values['team_skills'] == 'Yes') {
    $variables['d_1_team_skills'] = t('We confirm that the team have sufficient skills (scientific/technical knowledge and HACCP expertise) to ensure that the HACCP study will be effective.');
  } else {
    $variables['d_1_team_skills'] = t('We cannot confirm that the team have sufficient skills (scientific/technical knowledge and HACCP expertise) to ensure that the HACCP study will be effective.');
  }

  // @todo - need another field adding for an explanation if d_1 = no.

}
