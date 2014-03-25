<?php

/**
 * Outputs a study as a PDF.
 */
function myhaccp_output_pdf($iid) {
  // Get the dependency injection container.
  global $container;
  $configuration = $container['configuration'];

  $study = new Study();
  $study->setIID($iid);
  myhaccp_initialise_study($study);
  // Initialise mforms so we have access to its functions. This is needed
  // when loading the forms to access the checkbox labels for example.
  myhaccp_myhaccp_mforms_init();
  // Set the session IID.
  $_SESSION['iid'] = $iid;

  if (!empty($study)) {
    // Get the study name.
    $name = $study->getName();
    $filename = transliteration_clean_filename($name . '.pdf');
    // Load the mPDF library and start a new PDF.
    $path = libraries_get_path('mpdf');
    include_once $path . '/mpdf.php';
    $mpdf = new mPDF('', 'A4');
    // Get the stylesheets involved.
    $style_path = drupal_get_path('theme', 'myhaccp');
    $stylesheet = file_get_contents($style_path . '/css/pdf-style.css');
    $mpdf->list_indent_first_level = 1;
    // These could be used to help with tables not breaking across pages.
    $mpdf->shrink_tables_to_fit = 1.2;
    $mpdf->WriteHTML($stylesheet, 1);

    $sections = $configuration->getPDFSections();

    // Prepare the cover page.
    $mpdf->AddPage('', '', 1, '', 'on');
    $date = format_date(time(), 'custom', 'd/m/Y');
    $cover = '<div class="front-page"><h1 class="study-name">MyHACCP Study: ' . $name . '</h1>';
    $cover .= '<h3 class="origin">This document was created using the MyHACCP web tool.</h3>';
    $cover .= '<p>http://myhaccp.food.gov.uk</p>';
    $cover .= '<p>Date generated: ' . $date . '</p>';
    $cover .= '<p>Business name: </p></div>';
    // Write the cover to the PDF.
    $mpdf->WriteHTML($cover, 2);
    $mpdf->AddPage('', '', 1, '', 'off');

    // Add page count to footer.
    $mpdf->SetHTMLFooter('<footer class="pdf-footer">{PAGENO} / {nb}</footer>');
    // Prepare each page.
    foreach ($sections as $key => $section) {
      $output = '<section class="page">';
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
        $output .= '<section class="page error"><h3>One or more stages that contribute to this section do not pass validation, so the content for this section cannot be displayed.</h3><p>Please return to your HACCP study review pages to find and correct the problem.</p></section>';
      }

      $output .= '</section>';



      $mpdf->WriteHTML($output, 2);
    }

    // Write the output and then exit.
    $mpdf->Output($filename, 'I');
    // Documentation for output: http://mpdf1.com/manual/index.php?tid=125
    drupal_exit('tool');
  }
}
