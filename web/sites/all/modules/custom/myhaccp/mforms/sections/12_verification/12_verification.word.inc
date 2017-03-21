<?php

/**
 * @file
 * Theme function for stage 12.
 *
 * Prepares the passed form_state data and processes it for output.
 */

use \PhpOffice\PhpWord\Shared\Html;

/**
 * Preprocess function for principle_12_verification.
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_word_12_verification($study, $section) {
  /** @var \PhpOffice\PhpWord\Element\Section $section */
  $data = $study->getStage('principle_6')->getData();
  $principle_6 = $data['principle_6'];

  $section->addTitle(t('Validation study'), 3);

  // 1. Document your validation study in the space below.
  if (!empty($principle_6['6_1'])) {
    $variables['p_6_1'] = nl2p($principle_6['6_1'], FALSE);
    Html::addHtml($section, $variables['p_6_1']);
    $section->addTextBreak(1, 'fs', array('spaceAfter' => 0));
  }

  // 2. Who is responsible for ensuring the contents of the
  // HACCP plan are validated?
  // 3. Is this the same person who will formally sign off the
  // whole HACCP plan (which may contain several HACCP studies)?
  // 3a. Who will formally sign off the HACCP plan?
  if (!empty($principle_6['6_3']) && $principle_6['6_3'] == 'no') {
    $variables['p_6_2'] = '<p><strong>' . nl2br($principle_6['6_2'], TRUE) . '</strong> ' . t('is responsible for ensuring the contents of the HACCP plan are validated.') . '</p>';
    $variables['p_6_3'] = '<p><strong>' . $principle_6['6_3a'] . '</strong> ' . t('will formally sign off the HACCP plan.') . '</p>';
    Html::addHtml($section, $variables['p_6_2']);
    Html::addHtml($section, $variables['p_6_3']);
    $section->addTextBreak(1, 'fs', array('spaceAfter' => 0));
  }
  elseif (!empty($principle_6['6_3']) && $principle_6['6_3'] == 'yes') {
    $variables['p_6_2'] = '<p><strong>' . nl2br($principle_6['6_2']) . '</strong> ' . t('is responsible for ensuring the contents of the HACCP plan are validated and will also formally sign off the HACCP plan.') . '</p>';
    Html::addHtml($section, $variables['p_6_2']);
    $section->addTextBreak(1, 'fs', array('spaceAfter' => 0));
  }

  $variables['p_6_4_title'] = t('The following verification activities are undertaken:');

  $section->addTitle($variables['p_6_4_title'], 3);

  // 4. Verification activities.
  // Internal audits.
  $activities_ia = myhaccp_prepare_checkboxes_output('principle_6', '6_4.1', $principle_6);
  if (!empty($activities_ia)) {
    $content = '<h4>' . t('Internal audits of') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $activities_ia);
    $content .= '</li></ul>';
    $variables['p_6_4'][] = $content;
  }

  // External auditing programmes.
  $activities_ea = myhaccp_prepare_checkboxes_output('principle_6', '6_4.2', $principle_6);
  if (!empty($activities_ea)) {
    $content = '<h4>' . t('External auditing programmes') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $activities_ea);
    $content .= '</li></ul>';
    $variables['p_6_4'][] = $content;
  }

  // Finished product.
  $activities_fp = myhaccp_prepare_checkboxes_output('principle_6', '6_4.3', $principle_6);
  if (!empty($activities_fp)) {
    $content = '<h4>' . t('Finished product') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $activities_fp);
    $content .= '</li></ul>';
    $variables['p_6_4'][] = $content;
  }

  // Interim product.
  $activities_ip = myhaccp_prepare_checkboxes_output('principle_6', '6_4.4', $principle_6);
  if (!empty($activities_ip)) {
    $content = '<h4>' . t('Interim product') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $activities_ip);
    $content .= '</li></ul>';
    $variables['p_6_4'][] = $content;
  }

  // Other.
  $activities_other = myhaccp_prepare_checkboxes_output('principle_6', '6_4.5', $principle_6);
  if (!empty($activities_other)) {
    $content = '<h4>' . t('Other') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $activities_other);
    $content .= '</li></ul>';
    $variables['p_6_4'][] = $content;
  }

  // Reviewing.
  $activities_reviewing = myhaccp_prepare_checkboxes_output('principle_6', '6_4.6', $principle_6);
  if (!empty($activities_reviewing)) {
    $content = '<h4>' . t('Reviewing') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $activities_reviewing);
    $content .= '</li></ul>';
    $variables['p_6_4'][] = $content;
  }

  // 5. Other verification activities.
  if (!empty($principle_6['6_5'])) {
    $activities_other = explode("\r\n", trim($principle_6['6_5']));
    $content = '<h4>' . t('Other verification activities') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $activities_other);
    $content .= '</li></ul>';
    $variables['p_6_4'][] = $content;
  }

  foreach ($variables['p_6_4'] as $item) {
    Html::addHtml($section, $item);
    $section->addTextBreak(1, 'fs', array('spaceAfter' => 0));
  }

  // 6. Are all verification records maintained?
  if (!empty($principle_6['6_6']) && $principle_6['6_6'] == 'yes') {
    $variables['p_6_6'] = t('All verification records are maintained');
    Html::addHtml($section, '<p>' . $variables['p_6_6'] . '</p>');
    $section->addTextBreak(1, 'fs', array('spaceAfter' => 0));
  }

  // 7. How often is the whole HACCP plan formally reviewed?
  if (!empty($principle_6['6_7'])) {
    $variables['p_6_7'] = t('The HACCP system is formally reviewed <strong>') . $principle_6['6_7'] . '</strong>.';
    Html::addHtml($section, '<p>' . $variables['p_6_7'] . '</p>');
    $section->addTextBreak(1, 'fs', array('spaceAfter' => 0));
  }

  // 8. Who is responsible for carrying out a formal annual review?
  if (!empty($principle_6['6_8'])) {
    $variables['p_6_8'] = '<strong>' . $principle_6['6_8'] . t('</strong> is responsible for carrying out a formal annual review.');
    Html::addHtml($section, '<p>' . $variables['p_6_8'] . '</p>');
    $section->addTextBreak(1, 'fs', array('spaceAfter' => 0));
  }

  // 9. Mark any of the following 'triggers' that will initiate a
  // review in your organisation.
  $triggers = myhaccp_prepare_checkboxes_output('principle_6', '6_9', $principle_6);
  $trigger_content = '';
  if (!empty($triggers)) {
    $trigger_content .= '<h4>' . t('The following triggers will initiate a review in the organisation:') . '</h4>';
    $trigger_content .= '<ul><li>';
    $trigger_content .= implode('</li><li>', $triggers);
    $trigger_content .= '</li></ul>';
    $variables['p_6_9'] = $trigger_content;
    Html::addHtml($section, $variables['p_6_9']);
    $section->addTextBreak(1, 'fs', array('spaceAfter' => 0));
  }

  // 10. List any other mechanisms which are in place to
  // automatically 'trigger' a review.
  if (!empty($principle_6['6_10'])) {
    $variables['p_6_10'] = '<p><strong>' . t('Other mechanisms that will automatically trigger a review') . ':</strong> ' . $principle_6['6_10'] . '</p>';
    Html::addHtml($section, $variables['p_6_10']);
    $section->addTextBreak(1, 'fs', array('spaceAfter' => 0));
  }

  // 11. Are all records from reviews documented, brought to the
  // attention of senior management (for companies where this
  // is appropriate) and used to keep the HACCP plan up-to-date?
  if (!empty($principle_6['6_11']) && $principle_6['6_11'] == 'yes') {
    $section->addText(t('All records from reviews are documented, brought to the attention of senior management and used to keep the HACCP plan up-to-date.'), 'fs', 'ps');
  }
}