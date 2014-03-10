<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_preparatory_g().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_preparatory_g(&$variables) {
  $stage = 'preparatory_g';
  $values = $variables['data'][$stage];

  // Flow diagram file
  // @todo - Create a full-page image style
  $file = file_load($values['g_2']);
  $image = image_load($file->uri);
  $variables['flow_diagram_file'] = array(
  'file' => array(
    '#theme' => 'image_style',
    '#style_name' => 'large',
    '#path' => $image->source,
    '#width' => $image->info['width'],
    '#height' => $image->info['height'],
    ),
  );

  // Base 64 encode method to work with PDF.
  $image_url = file_create_url($file->uri);
  $image_uri = file_get_contents($file->uri);
  $variables['flow_diagram_data'] = base64_encode($image_uri);
  //$variables['imagestring'] = '<img src="data:image/gif;base64,' . $variables['flow_diagram_data'] . '" />';


  // 1. Have you completed a flow diagram?
  if($values['g_1'] == TRUE) {
    $variables['g_1'] = t('We have completed a flow diagram covering all steps in the manufacturing process of this product.');
  }

  // Hard copy location
  if(!empty($values['g_3'])) {
    $variables['g_3'] = $values['g_3'];
  }

}
