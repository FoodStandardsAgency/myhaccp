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
  if(!empty($values['6_1'])) {
    $variables['p_6_1'] = nl2br($values['6_1']);
  }

  // 2. Who is responsible for ensuring the contents of the HACCP plan are validated?
  // 3. Is this the same person who will formally sign off the whole HACCP plan (which may contain several HACCP studies)?
  // 3a. Who will formally sign off the HACCP plan?
  if(!empty($values['6_3']) &&  $values['6_3'] == 'no') {
    $variables['p_6_2'] =  '<p><strong>' . nl2br($values['6_2']) . '</strong>' . t(' is responsible for ensuring the contents of the HACCP plan are validated.') . '</p>';
    $variables['p_6_3'] = '<p><strong>' .  $values['6_3a'] . '</strong>' . t(' will formally sign off the HACCP plan.') . '</p>';
  } elseif (!empty($values['6_3']) && $values['6_3'] == 'yes') {
    $variables['p_6_2'] = '<p><strong>' . nl2br($values['6_2']) . '</strong>' . t(' is responsible for ensuring the contents of the HACCP plan are validated and will  also formally sign off the HACCP plan.') . '</p>';
  }

  $variables['p_6_4_title'] = t('The following verification activities are undertaken:');

  // 4. Verification activities
  $content = '';

  // Internal audits.
  $activities_ia = myhaccp_prepare_checkboxes_output('principle_6', '6_4.1', $values);
  if(!empty($activities_ia)) {
    $content .= '<h4>' . t('Internal audits of') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $activities_ia);
    $content .= '</li></ul>';
  }

  // External auditing programmes.
  $activities_ea = myhaccp_prepare_checkboxes_output('principle_6', '6_4.2', $values);
  if(!empty($activities_ea)) {
    $content .= '<h4>' . t('External auditing programmes') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $activities_ea);
    $content .= '</li></ul>';
  }

  // Finished product
  $activities_fp = myhaccp_prepare_checkboxes_output('principle_6', '6_4.3', $values);
  if(!empty($activities_fp)) {
    $content .= '<h4>' . t('Finished product') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $activities_fp);
    $content .= '</li></ul>';
  }

  // Interim product.
  $activities_ip = myhaccp_prepare_checkboxes_output('principle_6', '6_4.4', $values);
  if(!empty($activities_ip)) {
    $content .= '<h4>' . t('Finished product') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $activities_ip);
    $content .= '</li></ul>';
  }

  // Other.
  $activities_other = myhaccp_prepare_checkboxes_output('principle_6', '6_4.5', $values);
  if(!empty($activities_other)) {
    $content .= '<h4>' . t('Finished product') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $activities_other);
    $content .= '</li></ul>';
  }

  // Reviewing.
  $activities_reviewing = myhaccp_prepare_checkboxes_output('principle_6', '6_4.5', $values);
  if(!empty($ia)) {
    $content .= '<h4>' . t('Finished product') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $activities_reviewing);
    $content .= '</li></ul>';
  }

  // 5. Other verification activities
  if (!empty($values['6_5'])) {
    $activities_other = explode("\r\n", trim($values['6_5']));
    $content .= '<h4>' . t('Other verification activities') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $activities_other);
    $content .= '</li></ul>';
  }

  // Add all checkbox answers to the theme variable.
  $variables['p_6_4'] = $content;

  // 6. Are all verification records maintained?
  if(!empty($values['6_6']) && $values['6_6'] == 'yes') {
    $variables['p_6_6'] = '<p>' . t('All verification records are maintained') . '</p>';
  }

  // 7. How often is the whole HACCP plan formally reviewed?
  if(!empty($values['6_7'])) {
    $variables['p_6_7'] = t('The HACCP system is formally reviewed <strong>') . $values['6_7'] . '</strong>.';
  }

  // 8. Who is responsible for carrying out a formal annual review?
  if(!empty($values['6_8'])) {
    $variables['p_6_8'] = '<strong>' . $values['6_8'] . t('</strong> is responsible for carrying out a formal annual review.');
  }

  // 9. Mark any of the following 'triggers' that will initiate a review in your organisation
  $triggers = myhaccp_prepare_checkboxes_output('principle_6', '6_9', $values);
  $trigger_content = '';
  if(!empty($triggers)) {
    $trigger_content .= '<h4>' . t('The following triggers will initiate a review in the organisation:') . '</h4>';
    $trigger_content .= '<ul><li>';
    $trigger_content .= implode('</li><li>', $triggers);
    $trigger_content .= '</li></ul>';
    $variables['p_6_9'] = $trigger_content;
  }

  // 10. List any other mechanisms which are in place to automatically 'trigger' a review.
  if(!empty($values['6_10'])) {
    $variables['p_6_10'] = '<p><strong>Other mechanisms that will automatically trigger a review:</strong> ' . $values['6_10'] . '</p>';
  }

  // 11. Are all records from reviews documented, brought to the attention of senior management (for companies where this is appropriate) and used to keep the HACCP plan up-to-date?
  if(!empty($values['6_11']) && $values['6_11'] == 'yes') {
    $variables['p_6_11'] = t('All records from reviews are documented, brought to the attention of senior management and used to keep the HACCP plan up-to-date.');
  }
}
