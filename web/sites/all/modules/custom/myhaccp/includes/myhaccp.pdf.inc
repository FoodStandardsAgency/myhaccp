<?php

/**
 * Outputs a study as a PDF.
 */
function myhaccp_output_pdf($iid) {
  // Load the study.
  $stages = new stages();
  $stages_keys = array_keys($stages->allStages);

  $study = myhaccp_study_get_stages_data($stages_keys, $iid);
  if (!empty($study)) {
    // Load the mPDF library and start a new PDF.
    $path = libraries_get_path('mpdf');
    include_once $path . '/mpdf.php';
    $mpdf = new mPDF('', 'A4');
    // Get the stylesheets involved.
    $style_path = drupal_get_path('theme', 'myhaccp');
    $stylesheet = file_get_contents($style_path . '/css/style.css');
    $mpdf->WriteHTML($stylesheet, 1);

    $output = '';
    // Prepare each page.
    foreach ($study as $stage => $data) {
      $output .= theme($stage, array('data' => $data));
    }
    $mpdf->WriteHTML($output, 2);

    // Write the output and then exit.
    $mpdf->Output();
    drupal_exit('tool');
  }
}
