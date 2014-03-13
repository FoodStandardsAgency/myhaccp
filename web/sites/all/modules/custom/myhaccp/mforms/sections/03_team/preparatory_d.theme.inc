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

  // Generate a table of team members
  if(!empty($instances)) {

    // First the table headers
    $header = array(
      array('data' => t('Role')),
      array('data' => t('Name')),
      array('data' => t('Training')),
      array('data' => t('Qualifications')),
      array('data' => t('Experience'))
    );

    // Now the table rows
    foreach ($instances as $instance) {
      $role = !empty($instance['d_3']) ? $instance['d_3'] : '';
      $name = !empty($instance['d_1']) ? $instance['d_1'] : '';
      $training = !empty($instance['wrapper']['d_4']) ? $instance['wrapper']['d_4'] : '';
      $qualifications = !empty($instance['wrapper']['d_5']) ? $instance['wrapper']['d_5'] : '';
      $experience = !empty($instance['wrapper']['d_5']) ? $instance['wrapper']['d_6'] : '';

      // Generate a single item from training, experience and qualifications questions
      // $experience = implode('<br />', array_filter($instance['wrapper']));

      $rows[] = array(
        array('data' => $role),
        array('data' => $name),
        array('data' => $training),
        array('data' => $qualifications),
        array('data' => $experience)
      );
    }

    // Generate the table through a theme function
    $variables['d_1_team'] = theme('table', array('header' => $header, 'rows' => $rows));
  }

  // Team skills
  if (!empty($values['team_skills']) && $values['team_skills'] == 'Yes') {
    $variables['d_1_team_skills'] = '<p>' . t('We confirm that the team have sufficient skills (scientific/technical knowledge and HACCP expertise) to ensure that the HACCP study will be effective.') . '</p>';
  } elseif(!empty($values['team_skills']) && !empty($values['team_no_skills']) && $values['team_skills'] == 'No') {
    $variables['d_1_team_skills'] = '<p>' . t('The team do not have sufficient skills (scientific/technical knowledge and HACCP expertise) to ensure that the HACCP study will be effective. We plan to address this issue in the following way:') . '</p><p>' . $values['team_no_skills'] . '</p>';
  }

}
