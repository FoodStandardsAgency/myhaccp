<?php

/**
 * @file
 * Theme function for stage 1.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Process function for appendix a.
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template to display.
 */
function process_appendix_a($study, $mpdf, $section) {
  $data = $study->getStage('preparatory_g')->getData();
  $preparatory_g = $data['preparatory_g'];

  // Check we have some data for this form item.
  if (empty($preparatory_g['g_2'])) {
    return;
  }

  // Attempt to load the file.
  $file = is_array($preparatory_g['g_2']) && array_key_exists('fid', $preparatory_g['g_2']) ? file_load($preparatory_g['g_2']['fid']) : file_load($preparatory_g['g_2']);

  if (empty($file)) {
    // If the file couldn't be loaded then log a watchdog error.
    watchdog('myhaccp', 'Whilst rendering the PDF, the flow diagram could not be loaded.', array(), WATCHDOG_ERROR);
    return;
  }

  // Check if this document is a PDF in which case it needs special handling.
  if ($file->filemime == 'application/pdf') {
    prepare_pdf_merge($study, $mpdf, $section);
    return;
  }

  // Insert a blank page with the header.
  $mpdf->AddPageByArray(array());

  $output = '<section>';
  $output .= '<h1>' . $section['title'] . '</h1>';
  $output .= '<p>' . t('The flow diagram begins on the next page.') . '</p>';
  $output .= '</section>';

  $mpdf->WriteHTML($output, 2);

  // Prepare an image derivative of the flow diagram image
  // at a reasonable maximum size (2048px wide).
  // Due to issues with private file permissions (see case 12347) we need to
  // make a copy of the image somewhere it can be processed as an anonymous
  // user.
  $image_url = drupal_realpath($file->uri);
  $extension = pathinfo($image_url, PATHINFO_EXTENSION);
  // Store the file name in a global so we can remove it later.
  global $_myhaccp_temp_file_name;
  // Prepare a filename in the temporary directory for a copy of the file.
  $_myhaccp_temp_file_name = file_directory_temp() . '/' . md5($file->uri) . '.' . $extension;
  // Output the image derivative into the temporary file location.

  $orientation = $file->metadata['width'] > $file->metadata['height'] ? 'L' : 'P';
  $style = $orientation == 'P' ? image_style_load('pdf_flow_diagram') : image_style_load('pdf_flow_diagram_landscape');
  $success = file_exists($_myhaccp_temp_file_name) || image_style_create_derivative($style, $file->uri, $_myhaccp_temp_file_name);
  if (!$success) {
    watchdog('myhaccp', 'There was a problem creating the image derivative for the PDF in the temp directory.', array(), WATCHDOG_ERROR);
  }
  // Prepare the output.
  $output = '<section class="page"><div class="flow-diagram-container">
    <img src="' . $_myhaccp_temp_file_name . '" /></div></section>';

  $mpdf->addPagebyArray(array(
    'orientation' => $orientation,
  ));

  // Write the page output.
  $mpdf->WriteHTML($output, 2);
}

/**
 * Renders the PDF as Appendix A.
 */
function prepare_pdf_merge($study, $mpdf, $section) {

  $data = $study->getStage('preparatory_g')->getData();
  $preparatory_g = $data['preparatory_g'];

  // Check we have some data for this form item.
  if (empty($preparatory_g['g_2'])) {
    return;
  }

  // Attempt to load the file.
  $file = is_array($preparatory_g['g_2']) && array_key_exists('fid', $preparatory_g['g_2']) ? file_load($preparatory_g['g_2']['fid']) : file_load($preparatory_g['g_2']);

  if (empty($file)) {
    return;
  }

  if ($file->filemime != 'application/pdf') {
    return;
  }

  $pdf_url = drupal_realpath($file->uri);

  $mpdf->SetImportUse();
  $page_count = $mpdf->SetSourceFile($pdf_url);
  $page = 1;

  // Insert a blank page with the header.
  $mpdf->AddPageByArray(array());

  $output = '<section>';
  $output .= '<h1>' . $section['title'] . '</h1>';
  $output .= '<p>' . t('The flow diagram begins on the next page.') . '</p>';
  $output .= '</section>';

  $mpdf->WriteHTML($output, 2);

  // Iterate over all the pages (most likely just 1).
  while ($page <= $page_count) {

    $output = '<section>';

    // Import the page and make use of it.
    $template_id = $mpdf->ImportPage($page);
    $dimensions = $mpdf->getTemplateSize($template_id);
    $mpdf->SetPageTemplate($template_id);
    $orientation = $dimensions['w'] > $dimensions['h'] ? 'L' : 'P';
    $mpdf->addPagebyArray(array(
      'orientation' => $orientation,
      'sheet-size' => $orientation == 'L' ? array($dimensions['h'], $dimensions['w']) : array($dimensions['w'], $dimensions['h']),
    ));
    $page ++;
    $output .= '</section>';

    $mpdf->WriteHTML($output, 2);
  }
}