<?php

/**
 * @file
 * Theme function for stage 1.
 *
 * Prepares the passed form_state data and processes it for output.
 */

use \PhpOffice\PhpWord\Shared\Html;
use \PhpOffice\PhpWord\Shared\Converter;

/**
 * Process function for appendix a.
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param Study $study
 *   The study object.
 * @param $mpdf
 */
function myhaccp_word_appendix_a($study, $section, $phpWord) {
  /** @var \PhpOffice\PhpWord\Element\Section $section */
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

  // Insert a blank page with the header.
  $word_section = $phpWord->addSection(array(
    'orientation' => 'portrait',
    'marginTop' => Converter::inchToTwip(.6),
    'marginRight' => Converter::inchToTwip(.6),
    'marginBottom' => Converter::inchToTwip(.6),
    'marginLeft' => Converter::inchToTwip(.6),
  ));

  $output = '<section>';
  $output .= '<h2>' . $section['title'] . '</h2>';
  $output .= '<p>' . t('The flow diagram begins on the next page.') . '</p>';
  $output .= '</section>';

  Html::addHtml($word_section, $output);

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
  // We're unable to process PDF attachments.
  if ($file->filemime == 'application/pdf') {
    $orientation = 'portrait';
  }
  else {
    $orientation = $file->metadata['width'] > $file->metadata['height'] ? 'landscape' : 'portrait';
    $style = $orientation == 'portrait' ? image_style_load('pdf_flow_diagram') : image_style_load('pdf_flow_diagram_landscape');
    // Output the image derivative into the temporary file location.
    $success = file_exists($_myhaccp_temp_file_name) || image_style_create_derivative($style, $file->uri, $_myhaccp_temp_file_name);
    if (!$success) {
      watchdog('myhaccp', 'There was a problem creating the image derivative for the PDF in the temp directory.', array(), WATCHDOG_ERROR);
      // Don't add the image.
      _word_doc_image_error_message($word_section);
      return;
    }
  }
  // Add a new section and place the image.
  $word_section = $phpWord->addSection(array(
    'orientation' => $orientation,
    'marginTop' => Converter::inchToTwip(.6),
    'marginRight' => Converter::inchToTwip(.6),
    'marginBottom' => Converter::inchToTwip(.6),
    'marginLeft' => Converter::inchToTwip(.6),
  ));

  $image_height = $file->metadata['height'];
  $image_width = $file->metadata['width'];
  // Assuming 96 dpi (Windows).
  $dpi = 96;
  $image_height_inches = $file->metadata['height'] / $dpi;
  $image_width_inches = $file->metadata['width'] / $dpi;
  // The largest dimension an image can be (in inches).
  $max_dimension = 7.85;
  if ($orientation == 'landscape') {
    $ratio = $image_height / $image_width;
    // Avoid scaling up a small image.
    $width = $image_width_inches > $max_dimension ? $max_dimension : $image_width_inches;
    $height = $image_height_inches > $max_dimension ? $max_dimension * $ratio : $image_height_inches * $ratio;
  }
  else {
    $ratio = $image_width / $image_height;
    // Avoid scaling up a small image.
    $height = $image_height_inches > $max_dimension ? $max_dimension : $image_height_inches;
    $width = $image_width_inches > $max_dimension ? $max_dimension * $ratio : $image_width_inches * $ratio;
  }

  $word_section->addImage($_myhaccp_temp_file_name, array(
    'width'         => Converter::inchToPixel($width),
    'height'        => Converter::inchToPixel($height),
    'marginTop'     => 0,
    'marginLeft'    => 0,
    'wrappingStyle' => 'infront',
  ));
}

/**
 * Error message output in the document if a file doesn't embed.
 */
function _word_doc_image_error_message($word_section) {
  $output = '<h3>' . t('Replace this page with your flow diagram.') . '</h3>';
  $output .= '<p>' . t('There was a problem adding your uploaded flow diagram to the document. When printed, please replace this page with your printed flow diagram.') . '</p>';

  Html::addHtml($word_section, $output);
  return;
}