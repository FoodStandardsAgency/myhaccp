<?php

/**
 * Outputs a study as a PDF.
 */
function myhaccp_output_pdf($iid) {
  // Get the dependency injection container.
  global $container;
  $configuration = $container['configuration'];
  $keys = array_keys($configuration->getMachineNames());

  $study = myhaccp_study_get_stages_data($keys, $iid);
  if (!empty($study)) {
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

    // Determine the orientation of the pages and where page breaks occur.
    $breaks = array(
      'preparatory_c_1' => 'P',
      'preparatory_d' => 'P',
      'preparatory_e' => 'P',
      'preparatory_g' => 'P',
      'principle_1_1' => 'L',
      'principle_1_2' => 'L',
      'principle_1_3' => 'L',
      'principle_2_1' => 'L',
      'principle_3' => 'L',
      'principle_5' => 'L',
      'principle_6' => 'P',
      'principle_7' => 'P',
    );

    // Prepare each page.
    foreach ($study as $stage => $data) {
      // We need to fake the page title on principle 5.
      if ($stage == 'principle_5') {
        $mpdf->SetTopMargin('25');
        $mpdf->SetHTMLHeader('<h1>The HACCP Plan</h1>');
      }
      else {
        // Reset back to normal.
        $mpdf->SetTopMargin('12');
        $mpdf->SetHTMLHeader('');
      }
      // Check for a page break.
      if (isset($breaks[$stage])) {
        // Get the orientation.
        $orientation = $breaks[$stage];
        $mpdf->AddPage($orientation);
      }

      $output = theme($stage, array('data' => $data));
      $mpdf->WriteHTML($output, 2);
    }

    // Write the output and then exit.
    $mpdf->Output();
    drupal_exit('tool');
  }
}
