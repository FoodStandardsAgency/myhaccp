<?php

/**
 * @file
 * Handles the output of a study as a Word doc.
 */

use \PhpOffice\PhpWord\Shared\Html;
use \PhpOffice\PhpWord\Shared\Converter;

/**
 * Outputs a study as a Word doc.
 */
function myhaccp_output_word($iid) {
  // Get the dependency injection container.
  global $_myhaccp_container;
  $configuration = $_myhaccp_container['configuration'];
  require 'vendor/autoload.php';

  // Set the session IID.
  $_SESSION['iid'] = $iid;

  $study = new Study();
  $study->setIID($iid);
  myhaccp_initialise_study($study);
  // Initialise mforms so we have access to its functions. This is needed
  // when loading the forms to access the checkbox labels for example.
  myhaccp_myhaccp_mforms_init();

  if (!empty($study)) {
    // Get the study name.
    $name = $study->getName();
    // Get the study user.
    $user = $study->getCurrentStudyOwner();
    // Instantiate a new Business object.
    $business = new Business();
    // Set the user.
    $business->setUser($user);
    // Get the business name.
    $business_name = $business->getBusinessName();
    $filename = transliteration_clean_filename($name . '.docx');
    $phpWord = new \PhpOffice\PhpWord\PhpWord();
    \PhpOffice\PhpWord\Settings::setOutputEscapingEnabled(true);

    $word_section = $phpWord->addSection();
    // Set the PHPWord configuration and styles.
    $configuration->setPHPWordConfig($phpWord);

    // Get the sections for the document.
    $sections = $configuration->getPDFSections();

    $date = format_date(time(), 'custom', 'd/m/Y');
    $word_section->addTitle(t('MyHACCP Study') . ': ' . $name, 1);
    $word_section->addText(t('Business name') . ': ' . $business_name, array(
      'size' => 16,
      'bold' => TRUE,
    ));

    $cover_footer = '<footer class="front-page"><h3 class="origin">' . t('This document was created using the MyHACCP web tool.') . '</h3>';
    $cover_footer .= '<p>http://myhaccp.food.gov.uk</p>';
    $cover_footer .= '<p class="date">' . t('Date generated') . ': ' . $date . '</p></footer>';

    $footer = $word_section->addFooter();
    Html::addHTML($footer, $cover_footer);

    // Prepare each section.
    foreach ($sections as $key => $section) {

      // Skip appendixes as they'll be handled differently.
      if (isset($section['type']) && $section['type'] == 'appendix') {
        continue;
      }

      $word_section = $phpWord->addSection(array(
        'orientation' => isset($section['orientation']) && $section['orientation'] == 'L' ? 'landscape' : 'portrait',
        'marginTop' => Converter::inchToTwip(.6),
        'marginRight' => Converter::inchToTwip(.6),
        'marginBottom' => Converter::inchToTwip(.6),
        'marginLeft' => Converter::inchToTwip(.6),
      ));

      $word_section->addTitle(htmlspecialchars($section['title']), 2);
      // Reset the footer.
      $word_section->addFooter();

      // Check the validation status of the needed stages.
      $statuses = array();

      foreach ($section['validation'] as $stage_name) {
        $stage = $study->getStage($stage_name);
        $statuses[] = $stage->getStatus();
      }
      // If all statuses are valid then all good.
      if (count(array_keys($statuses, VALID)) == count($statuses)) {
        $include_path = drupal_get_path('module', 'myhaccp') . '/mforms/sections/' . $key . '/' . $key . '.word.inc';
        $function = 'myhaccp_word_' . $key;
        if (file_exists($include_path)) {
          include $include_path;
          if (function_exists($function)) {
            try {
              $function($study, $word_section);
            }
            catch (Exception $e) {
              throw new Exception('Error occurred in function ' . $function . ": \n\n" . $e);
            }
          }
        }
      }
      else {
        // There were some failed stages.
        $output = '<h3>' . t('One or more stages that contribute to this section do not pass validation, so the content for this section cannot be displayed.') . '</h3><p>' . t('Please return to your HACCP study review pages to find and correct the problem.') . '</p>';
        Html::addHtml($word_section, $output);
      }

    }

    // Process Appendixes.
    foreach ($sections as $key => $section) {
      // Skip non appendixes as they've already been handled.
      if (!isset($section['type']) || $section['type'] != 'appendix') {
        continue;
      }

      $include_path = drupal_get_path('module', 'myhaccp') . '/mforms/sections/' . $key . '/' . $key . '.word.inc';
      $function = 'myhaccp_word_' . $key;
      if (file_exists($include_path)) {
        include $include_path;
        if (function_exists($function)) {
          $function($study, $word_section);
        }
      }
    }

    header("Content-Description: File Transfer");
    header('Content-Disposition: attachment; filename="' . $filename . '"');
    header('Content-Type: application/vnd.openxmlformats-officedocument.wordprocessingml.document');
    header('Content-Transfer-Encoding: binary');
    header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
    header('Expires: 0');

    $objWriter = \PhpOffice\PhpWord\IOFactory::createWriter($phpWord, 'Word2007');
    $objWriter->save("php://output");

    global $_myhaccp_temp_file_name;
    if (file_exists($_myhaccp_temp_file_name)) {
      unlink($_myhaccp_temp_file_name);
    }
  }
}

/**
 * Determines whether there are any CCPs in principle 2.2.
 */
function myhaccp_check_ccps() {
  // Load principle 2.2.
  $principle_2_2 = mforms_get_vals('myhaccp', 'principle_2_2');
  $ccps = array();
  foreach ($principle_2_2['principle_2_2']['instance_table'] as $key => $item) {
    if ($item['ccp'] == 'yes') {
      $ccps[] = $key;
    }
  }
  return !empty($ccps);
}

/**
 * Similar to nl2br but creates paragraphs.
 */
function nl2p($string, $line_breaks = TRUE, $xml = TRUE) {

  $string = str_replace(array('<p>', '</p>', '<br>', '<br />'), '', $string);

  // It is conceivable that people might still want single line-breaks
  // without breaking into a new paragraph.
  if ($line_breaks == true) {
    return '<p>' . preg_replace(array(
        "/([\n]{2,})/i",
        "/([^>])\n([^<])/i"
      ), array(
        "</p>\n<p>",
        '$1<br' . ($xml == TRUE ? ' /' : '') . '>$2'
      ), trim($string)) . '</p>';
  }
  else {
    return '<p>' . preg_replace(
        array(
          "/([\n]{2,})/i",
          "/([\r\n]{3,})/i",
          "/([^>])\n([^<])/i",
          "/([\r]{1,})/i",
        ),
        array(
          "</p>\n<p>",
          "</p>\n<p>",
          '$1<br' . ($xml == TRUE ? ' /' : '') . '>$2',
          "</p>\n<p>",
        ),
        trim($string)) . '</p>';
  }
}