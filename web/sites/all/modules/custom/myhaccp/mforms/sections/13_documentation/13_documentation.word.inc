<?php

/**
 * @file
 * Theme function for stage 13.
 *
 * Prepares the passed form_state data and processes it for output.
 */

use \PhpOffice\PhpWord\Shared\Html;

/**
 * Preprocess function for 13_documentation.
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_word_13_documentation($study, $section) {
  /** @var \PhpOffice\PhpWord\Element\Section $section */
  $data = $study->getStage('principle_7')->getData();
  $principle_7 = $data['principle_7'];

  // 1. Select all forms of documentation relating to this HACCP
  // study that your business retains.
  $documentation = myhaccp_prepare_checkboxes_output('principle_7', '7_1', $principle_7);
  $content = '';
  if (!empty($documentation)) {
    $content .= '<h4>' . t('Documentation relating to this HACCP study that the business retains:') . '</h4>';
    $content .= '<ul><li>';
    $content .= implode('</li><li>', $documentation);
    $content .= '</li></ul>';
    Html::addHtml($section, $content);
    $section->addTextBreak(1, 'fs', array('spaceAfter' => 0));
  }

  // 2. Provide details of any other supporting information (i.e. anything
  // else covered in your HACCP plan) that is retained.
  if (!empty($principle_7['7_2'])) {
    $section->addTitle(t('Other supporting information that is retained'), 3);
    Html::addHtml($section, nl2p($principle_7['7_2'], FALSE));
    $section->addTextBreak(1, 'fs', array('spaceAfter' => 0));
  }

  // 3. How is documentation controlled (up-dates / issue number)?
  if (!empty($principle_7['7_3'])) {
    $section->addTitle(t('Documentation control'), 3);
    Html::addHtml($section, nl2p($principle_7['7_3'], FALSE));
    $section->addTextBreak(1, 'fs', array('spaceAfter' => 0));
  }

  // 4. What is the maximum length of time that you retain this information for?
  if (!empty($principle_7['7_4'])) {
    $content = t('The maximum length of time we retain this information for is') . ' <strong>' . $principle_7['7_4'] . '</strong>';
    Html::addHtml($section, nl2p($content, FALSE));
    $section->addTextBreak(1, 'fs', array('spaceAfter' => 0));
  }

  // 5. Are the records accessible, accurate and up to date?
  if (!empty($principle_7['7_5'])) {
    if ($principle_7['7_5'] == 'yes') {
      $section->addText(t('All records are accessible, accurate and up to date.'), 'fs', 'ps');
    }
  }

}
