<?php

/**
 * @file
 * Theme function for stage 1.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Preprocess function for 01_management.
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_word_01_management($study, $section) {
  /** @var \PhpOffice\PhpWord\Element\Section $section */
  $data = $study->getStage('preparatory_b')->getData();
  $preparatory_b = $data['preparatory_b'];
  // Iterate over the checkboxes fetching their labels.
  $names = myhaccp_prepare_checkboxes_output('preparatory_b', 'b_1', $preparatory_b);

  $variables = array();

  // b_1 Logic: IF 'I am the management and can confirm that I am committed.'
  // is selected.
  if (in_array('N/A - I am the management and can confirm that I am committed.', $names)) {
    $variables['b_1_title'] = t('I am the management and can confirm that I am committed to food safety management based on HACCP.');
    // Don't show any of the checkboxes output.
    $variables['b_1'] = array();
  }
  else {
    $variables['b_1_title'] = t('The following evidence shows the support of senior management to food safety management based on HACCP:');
    $variables['b_1'] = $names;
  }
  // b_2.
  $variables['b_2_title'] = t('Other evidence of management commitment');
  $variables['b_2'] = $preparatory_b['b_2'] ? $preparatory_b['b_2'] : '';

  // Output to section.
  $section->addTitle(htmlspecialchars($variables['b_1_title']), 3);
  foreach ($variables['b_1'] as $list_item) {
    $section->addListItem(htmlspecialchars($list_item), 0, 'fs', NULL, 'ps');
  }
  if ($variables['b_2']) {
    $section->addTitle(htmlspecialchars($variables['b_2_title']), 3);
    $section->addText($variables['b_2'], 'fs', 'ps');
  }
}
