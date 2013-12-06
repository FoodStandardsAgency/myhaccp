<?php

/**
 * Theme function to render the fields in a table.
 *
 * Principle 1 Question 1.
 */
function theme_myhacpp_p1q2_table($variables) {
  $element = $variables['element'];

  $rows = array();
  foreach (element_children($element) as $key) {
    $rows[] = array(
      array('data' => $element[$key]['name']),
      array('data' => $element[$key]['description']),
      array('data' => $element[$key]['severity']),
      array('data' => $element[$key]['likelihood']),
      array('data' => $element[$key]['significance']),
    );
  }

  // Build the table, with a row per hazard.
  // The table has 5 columns.
  $header = array(
    'hazard_name' => t('Hazard'),
    'hazard_desc' => t('Hazard Description'),
    'severity' => array(
      'data' => t('Severity (1-3) !tip', array(
        '!tip' => _help_tip(),
        )),
      'class' => array('severity'),
    ),
    'likelihood' => array(
      'data' => t('Likelihood (1-3) !tip', array(
        '!tip' => _help_tip(),
        )),
      'class' => array('likelihood'),
    ),
    'significance' => array(
      'data' => t('Significance (S x L) !tip', array(
        '!tip' => _help_tip(),
        )),
      'class' => array('significance'),
    ),
  );

  return theme('table', array('header' => $header, 'rows' => $rows));
}
