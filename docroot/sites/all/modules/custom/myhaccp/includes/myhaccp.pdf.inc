<?php

/**
 * @file
 * Handles the output of a study as a PDF.
 */

 use Mpdf\Mpdf;

/**
 * Outputs a study as a PDF.
 */
function myhaccp_output_pdf($iid) {
  // Get the dependency injection container.
  global $_myhaccp_container;
  $configuration = $_myhaccp_container['configuration'];

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
    // Instantiate a new B  usiness object.
    $business = new Business();
    // Set the user.
    $business->setUser($user);
    // Get the business name.
    $business_name = $business->getBusinessName();
    $filename = transliteration_clean_filename($name . '.pdf');
    // Load the mPDF library and start a new PDF.
    $path = libraries_get_path('mpdf');
    require_once $path . '/vendor/autoload.php';
    $mpdf = new mPDF();
    // Get the stylesheets involved.
    $style_path = drupal_get_path('theme', 'myhaccp_theme');
    $stylesheet = file_get_contents($style_path . '/css/pdf-style.css');
    $mpdf->list_indent_first_level = 1;
    // These could be used to help with tables not breaking across pages.
    $mpdf->shrink_tables_to_fit = 1.2;
    $mpdf->WriteHTML($stylesheet, 1);

    $sections = $configuration->getPDFSections();

    // Prepare the cover page.
    $mpdf->AddPageByArray(array(
      'resetpagenum' => 0,
      'suppress' => 'on',
    ));
    $date = format_date(time(), 'custom', 'd/m/Y');
    $cover = '<h1 class="study-name">' . t('MyHACCP Study') . ': ' . $name . '</h1>';
    $cover .= '<p class="business-name">' . t('Business name') . ': <span class="business-name--title">' . $business_name . '</span></p>';
    $cover_footer = '<footer class="front-page"><h3 class="origin">' . t('This document was created using the MyHACCP web tool.') . '</h3>';
    $cover_footer .= '<p>http://myhaccp.food.gov.uk</p>';
    $cover_footer .= '<p class="date">' . t('Date generated') . ': ' . $date . '</p></footer>';
    $mpdf->SetHTMLFooter($cover_footer);
    // Write the cover to the PDF.
    $mpdf->WriteHTML($cover, 2);

    $mpdf->AddPageByArray(array(
      'resetpagenum' => 1,
      'suppress' => 'off',
      'margin-top' => 40,
    ));

    // Reset the footer.
    $mpdf->SetHTMLFooter('');

    // Add page count to footer.
    $mpdf->SetHTMLFooter('<footer class="pdf-footer">{PAGENO} / {nbpg}</footer>');
    // Prepare each page.
    foreach ($sections as $key => $section) {
      // Skip appendixes as they'll be handled differently.
      if (isset($section['type']) && $section['type'] == 'appendix') {
        continue;
      }

      $output = '<section class="page section-' . str_replace('_', '-', $key) . '">';
      // We need to fake the page title for the plan section.
      if ($key == '11_plan') {
        $mpdf->SetTopMargin('25');
        $mpdf->SetHTMLHeader('<h1>' . $section['title'] . '</h1>');
      }
      else {
        // Reset back to normal.
        $mpdf->SetTopMargin('12');
        $mpdf->SetHTMLHeader('');
        $output .= '<h1>' . $section['title'] . '</h1>';
      }

      // Get the orientation.
      if ($key !== '01_management') {
        $mpdf->AddPage($section['orientation']);
      }

      // Check the validation status of the needed stages.
      $statuses = array();

      foreach ($section['validation'] as $stage_name) {
        $stage = $study->getStage($stage_name);
        $statuses[] = $stage->getStatus();
      }
      // If all statuses are valid then all good.
      if (count(array_keys($statuses, VALID)) == count($statuses)) {
        $output .= theme($key, array('study' => $study));
      }
      else {
        // There were some failed stages.
        $output .= '<section class="page error"><h3>' . t('One or more stages that contribute to this section do not pass validation, so the content for this section cannot be displayed.') . '</h3><p>' . t('Please return to your HACCP study review pages to find and correct the problem.') . '</p></section>';
      }

      $output .= '</section>';

      $mpdf->WriteHTML($output, 2);
    }

    // Process Appendixes.
    foreach ($sections as $key => $section) {
      // Skip non appendixes as they've already been handled.
      if (!isset($section['type']) || $section['type'] != 'appendix') {
        continue;
      }

      // Appendixes have a process function which gets called and handles the
      // output.
      if (isset($section['process_function'])) {
        $function = $section['process_function'];
        module_load_include('inc', 'myhaccp', 'mforms/sections/' . $key . '/' . $key);
        if (function_exists($function)) {
          $function($study, $mpdf, $section);
        }
      }
    }

    // Write the output and then exit.
    $mpdf->Output($filename, 'I');
    // Documentation for output: http://mpdf1.com/manual/index.php?tid=125
    // Before exiting delete the temporary file that we stored in a global
    // earlier in 05_process_theme.inc.
    global $_myhaccp_temp_file_name;
    if (file_exists($_myhaccp_temp_file_name)) {
      unlink($_myhaccp_temp_file_name);
    }
    drupal_exit('tool');
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
