<?php

/**
 * @file
 * Theme function for this stage.
 *
 * Prepares the passed form_state data and processes it for output.
 */

/**
 * Implements hook_preprocess_preparatory_c_1().
 *
 * Prepare the form_state data for presentation in the template file.
 *
 * @param array $variables
 *   Form state data to process into variables for the template
 *   to display.
 */
function myhaccp_preprocess_preparatory_c_2(&$variables) {
  $stage = 'preparatory_c_2';
  $values = $variables['data'][$stage]['wrapper'];
  $content = '';

  // Physical hazards.
  $physical_hazards = array();
  foreach ($values['physical_c_4']['physical'] as $key => $value) {
    if ($key === $value) {
      $physical_hazards[] = $value;
    }
  }
  if (array_get($values, 'physical_c_4.physical_other', FALSE)) {
    $physical_other = explode("\r\n", trim($values['physical_c_4']['physical_other']));
    $physical_hazards = array_merge($physical_hazards, $physical_other);
  }

  // Chemical hazards.
  $chemical_hazards = array();
  foreach ($values['chemical_c_4']['chemical'] as $key => $value) {
    if ($key === $value) {
      $chemical_hazards[] = $value;
    }
  }
  if (array_get($values, 'chemical_c_4.chemical_other', FALSE)) {
    $chemical_other = explode("\r\n", trim($values['chemical_c_4']['chemical_other']));
    $chemical_hazards = array_merge($chemical_hazards, $chemical_other);
  }

  // Biological hazards.
  $biological_hazards = array();
  foreach ($values['biological_c_4']['biological'] as $key => $value) {
    if ($key === $value) {
      $biological_hazards[] = $value;
    }
  }
  if (array_get($values, 'biological_c_4.biological_other', FALSE)) {
    $biological_other = explode("\r\n", trim($values['biological_c_4']['biological_other']));
    $biological_hazards = array_merge($biological_hazards, $biological_other);
  }

  // Allergens hazards.
  $allergens_hazards = array();
  foreach ($values['allergens_c_4']['allergens'] as $key => $value) {
    if ($key === $value) {
      $allergens_hazards[] = $value;
    }
  }
  if (array_get($values, 'allergens_c_4.allergens_other', FALSE)) {
    $allergens_other = explode("\r\n", trim($values['allergens_c_4']['allergens_other']));
    $allergens_hazards = array_merge($allergens_hazards, $allergens_other);
  }

  // c_4
  $variables['c_4_title'] = t('The HACCP plan will cover final product safety and will look at the following hazards:');

  if (!empty($physical_hazards)) {
    $physical_hazards = implode('</li><li>', $physical_hazards);
    $content .= '<div><p>' . t('Physical') . '</p><ul><li>' . $physical_hazards . '</li></ul></div>';
  }

  if (!empty($chemical_hazards)) {
    $chemical_hazards = implode('</li><li>', $chemical_hazards);
    $content .= '<div><p>' . t('Chemical') . '</p><ul><li>' . $chemical_hazards . '</li></ul></div>';
  }

  if (!empty($biological_hazards)) {
    $biological_hazards = implode('</li><li>', $biological_hazards);
    $content .= '<div><p>' . t('Biological') . '</p><ul><li>' . $biological_hazards . '</li></ul></div>';
  }

  if (!empty($allergens_hazards)) {
    $allergens_hazards = implode('</li><li>', $allergens_hazards);
    $content .= '<div><p>' . t('Allergens') . '</p><ul><li>' . $allergens_hazards . '</li></ul></div>';
  }

  // Finally we have the output.
  $variables['c_4'] = $content;
}
