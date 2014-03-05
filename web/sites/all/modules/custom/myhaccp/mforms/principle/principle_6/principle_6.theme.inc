<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_principle_6().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_principle_6(&$variables) {
  $stage = 'principle_6';
  $values = $variables['data'][$stage];

  // 1. Document your validation study in the space below.
  $variables['p_6_1'] = $values['6_1'];

  // 2. Who is responsible for ensuring the contents of the HACCP plan are validated?
  // 3. Is this the same person who will formally sign off the whole HACCP plan (which may contain several HACCP studies)?
  // 3a. Who will formally sign off the HACCP plan?
  if($values['6_3'] == 'no') {
    $variables['p_6_2'] =  '<p><strong>' . $values['6_2'] . '</strong>' . t(' is responsible for ensuring the contents of the HACCP plan are validated.') . '</p>';
    $variables['p_6_3'] = '<p><strong>' .  $values['6_3a'] . '</strong>' . t(' will formally sign off the HACCP plan.') . '</p>';
  } elseif ($values['6_3'] == 'yes') {
    $variables['p_6_2'] = '<p><strong>' . $values['6_2'] . '</strong>' . t(' is responsible for ensuring the contents of the HACCP plan are validated and will  also formally sign off the HACCP plan.') . '</p>';
  }

  $variables['p_6_4_title'] = t('The following verification activities are undertaken:');

  // 4. Verification activities
<<<<<<< Updated upstream
  // $activities = myhaccp_prepare_checkboxes_output('principle_6', '6_4.6_4_1', $values);

  // dpm($activities);
=======
  $activities = myhaccp_prepare_checkboxes_output('principle_6', '6_4.6_4_1', $values);
>>>>>>> Stashed changes

  $content = '';
  foreach($values['6_4'] as $key => $activity_group) {
    switch ($key) {
      // Internal audits.
      case '1':
        $content .= '<h4>' . t('Internal audits of') . '</h4>';
        $content .= '<ul><li>';
        $content .= implode('</li><li>', $activity_group);
        $content .= '</li></ul>';
        break;
      // External auditing programmes.
      case '2':
        $content .= '<h4>' . t('External auditing programmes') . '</h4>';
        $content .= '<ul><li>';
        $content .= implode('</li><li>', $activity_group);
        $content .= '</li></ul>';
        break;
      // Finished product.
      case '3':
        $content .= '<h4>' . t('Finished product') . '</h4>';
        $content .= '<ul><li>';
        $content .= implode('</li><li>', $activity_group);
        $content .= '</li></ul>';
        break;
      // Interim product.
      case '4':
        $content .= '<h4>' . t('Interim product') . '</h4>';
        $content .= '<ul><li>';
        $content .= implode('</li><li>', $activity_group);
        $content .= '</li></ul>';
        break;
      // Other.
      case '5':
        $content .= '<h4>' . t('Other') . '</h4>';
        $content .= '<ul><li>';
        $content .= implode('</li><li>', $activity_group);
        $content .= '</li></ul>';
        break;
      // Reviewing.
      case '6':
        $content .= '<h4>' . t('Reviewing') . '</h4>';
        $content .= '<ul><li>';
        $content .= implode('</li><li>', $activity_group);
        $content .= '</li></ul>';
    }
  }

  // 5. Other verification activities
  if (!empty($values['6_5'])) {
    $content .= '<h4>' . t('Other verification activities') . '</h4><p>' . $values['6_5'] . '</p>';
  }

  $variables['p_6_4'] = $content;

  // @todo need the checkbox labels here

  // 7. How often is the whole HACCP plan formally reviewed?
  $variables['p_6_7'] = t('The HACCP system is formally reviewed <strong>') . $values['6_7'] . '</strong>.';

  // 8. Who is responsible for carrying out a formal annual review?
  $variables['p_6_8'] = '<strong>' . $values['6_8'] . t('</strong> is responsible for carrying out a formal annual review.');

  // 9. Mark any of the following 'triggers' that will initiate a review in your organisation
  if(!empty($values['6_9'])) {
    $variables['p_6_9'] = '<h3>' . t('The following triggers will initiate a review in the organisation:') . '</h3><ul><li>';
    $variables['p_6_9'] .= implode('</li><li>', $values['6_9']);
    $variables['p_6_9'] .= '</ul>';
  }

  // 10. List any other mechanisms which are in place to automatically 'trigger' a review.
  $variables['p_6_10'] = '<h4>Other mechanisms that will automatically trigger a review</h4><p>' . $values['6_10'] . '</p>';

  // 11. Are all records from reviews documented, brought to the attention of senior management (for companies where this is appropriate) and used to keep the HACCP plan up-to-date?
  if($values['6_11'] == 'yes') {
    $variables['p_6_11'] = t('All records from reviews are documented, brought to the attention of senior management and used to keep the HACCP plan up-to-date.');
  }
}
