<?php

/**
 * Outputs a study as a PDF.
 */
function myhaccp_output_pdf($iid) {
  $path = libraries_get_path('mpdf');
  include_once $path . '/mpdf.php';
  $mpdf = new mPDF();
  // Load the study.
  $study = myhaccp_study_get_all_stage_data($iid);
  if (!empty($study)) {
    $output = '';
    foreach ($study as $stage => $data) {
      $output .= theme($stage, array('data' => $data));
    }
    $mpdf->WriteHTML($output);
    $mpdf->Output();
    drupal_exit('tool');
  }
}
