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
function myhaccp_preprocess_02_terms(&$variables) {
  // This section is made up of data from three stages.
  $study = $variables['study'];
  $data = $study->getStage('preparatory_a')->getData();
  $preparatory_a = $data['preparatory_a'];
  $data = $study->getStage('preparatory_c_1')->getData();
  $preparatory_c_1 = $data['preparatory_c_1'];
  $data = $study->getStage('preparatory_c_2')->getData();
  $preparatory_c_2 = $data['preparatory_c_2']['wrapper'];

  $content = '';

  $variables['c_intro'] = t('<p>This <strong>@c_1</strong> HACCP plan covers:<br/><strong>@c_2</strong></p><p>
It will start at <strong>@start</strong> through to <strong>@end</strong>.</p>',
    array(
      '@c_1' => $preparatory_c_1['c_1'],
      '@c_2' => $preparatory_c_1['c_2'],
      '@start' => $preparatory_c_1['c_3']['start'],
      '@end' => $preparatory_c_1['c_3']['end'],
    )
  );

  // Physical hazards.
  $physical_hazards = array();
  if (!empty($preparatory_c_2['physical_c_4']['physical'])) {
    foreach ($preparatory_c_2['physical_c_4']['physical'] as $key => $value) {
      if ($key === $value) {
        $physical_hazards[] = $value;
      }
    }
  }
  if (array_get($preparatory_c_2, 'physical_c_4.physical_other', FALSE)) {
    $physical_other = explode("\r\n", trim($values['physical_c_4']['physical_other']));
    $physical_hazards = array_merge($physical_hazards, $physical_other);
  }

  // Chemical hazards.
  $chemical_hazards = array();
  if (!empty($preparatory_c_2['chemical_c_4']['chemical'])) {
    foreach ($preparatory_c_2['chemical_c_4']['chemical'] as $key => $value) {
      if ($key === $value) {
        $chemical_hazards[] = $value;
      }
    }
  }
  if (array_get($preparatory_c_2, 'chemical_c_4.chemical_other', FALSE)) {
    $chemical_other = explode("\r\n", trim($values['chemical_c_4']['chemical_other']));
    $chemical_hazards = array_merge($chemical_hazards, $chemical_other);
  }

  // Biological hazards.
  $biological_hazards = array();
  if (!empty($preparatory_c_2['biological_c_4']['biological'])) {
    foreach ($preparatory_c_2['biological_c_4']['biological'] as $key => $value) {
      if ($key === $value) {
        $biological_hazards[] = $value;
      }
    }
  }
  if (array_get($preparatory_c_2, 'biological_c_4.biological_other', FALSE)) {
    $biological_other = explode("\r\n", trim($values['biological_c_4']['biological_other']));
    $biological_hazards = array_merge($biological_hazards, $biological_other);
  }

  // Allergens hazards.
  $allergens_hazards = array();
  if (!empty($preparatory_c_2['allergens_c_4']['allergens'])) {
    foreach ($preparatory_c_2['allergens_c_4']['allergens'] as $key => $value) {
      if ($key === $value) {
        $allergens_hazards[] = $value;
      }
    }
  }
  if (array_get($preparatory_c_2, 'allergens_c_4.allergens_other', FALSE)) {
    $allergens_other = explode("\r\n", trim($values['allergens_c_4']['allergens_other']));
    $allergens_hazards = array_merge($allergens_hazards, $allergens_other);
  }

  // c_4
  $variables['c_4_title'] = t('The HACCP plan will cover final product safety and will look at the following hazards:');

  if (!empty($physical_hazards)) {
    $physical_hazards = implode('</li><li>', $physical_hazards);
    $content .= '<div>' . t('<h4>Physical</h4>') . '<ul><li>' . $physical_hazards . '</li></ul></div>';
  }

  if (!empty($chemical_hazards)) {
    $chemical_hazards = implode('</li><li>', $chemical_hazards);
    $content .= '<div>' . t('<h4>Chemical</h4>') . '<ul><li>' . $chemical_hazards . '</li></ul></div>';
  }

  if (!empty($biological_hazards)) {
    $biological_hazards = implode('</li><li>', $biological_hazards);
    $content .= '<div>' . t('<h4>Biological</h4>') . '<ul><li>' . $biological_hazards . '</li></ul></div>';
  }

  if (!empty($allergens_hazards)) {
    $allergens_hazards = implode('</li><li>', $allergens_hazards);
    $content .= '<div>' . t('<h4>Allergens</h4>') . '<ul><li>' . $allergens_hazards . '</li></ul></div>';
  }

  // Finally we have the output.
  $variables['c_4'] = $content;

  // Iterate over the checkboxes fetching their labels.
  $names = myhaccp_prepare_checkboxes_output('preparatory_a', 'a_1', $preparatory_a);

  // a_1
  $variables['a_1_title'] = t('The company has in place a number of effective prerequisite programmes, including:');
  $variables['a_1'] = !empty($names) ? '<ul><li>' . implode('</li><li>', $names) . '</li></ul>' : '';
  // a_2
  $variables['a_2_title'] = t('The location of the above documents is:');
  $variables['a_2'] = $preparatory_a['a_2'] ? $preparatory_a['a_2'] : '';

}
