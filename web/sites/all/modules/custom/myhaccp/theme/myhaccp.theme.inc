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
      array('data' => $element[$key]['details']),
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
      'data' => t('Significance <span>(S x L)</span> !tip', array(
        '!tip' => _help_tip(),
        )),
      'class' => array('significance'),
    ),
  );

  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Theme function to render the fields in a table.
 *
 * Principle 1 Question 3.
 */
function theme_myhacpp_p1q3_table($variables) {
  $element = $variables['element'];

  $rows = array();
  foreach (element_children($element) as $key) {
    $rows[] = array(
      array('data' => $element[$key]['process_step']),
      array('data' => $element[$key]['hazard']),
      array('data' => $element[$key]['control_measure']),
    );
  }

  // Build the table, with a row per hazard.
  // The table has 3 columns.
  $header = array(
    'process_step' => array(
      'data' => t('Process Step'),
      'class' => array('process-step'),
    ),
    'hazard' => array(
      'data' => t('Hazard'),
      'class' => array('hazard'),
    ),
    'control_measure' => array(
      'data' => t('Control Measure !tip', array(
        '!tip' => _help_tip(),
      )),
      'class' => array('control-measure'),
    ),
  );

  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Theme function to render the fields in a table.
 *
 * Principle 2 Question 4.
 */
function theme_myhacpp_p2q4_table($variables) {
  $element = $variables['element'];

  $rows = array();
  foreach (element_children($element) as $key) {
    $rows[] = array(
      array('data' => $element[$key]['process_step']),
      array('data' => $element[$key]['hazard']),
      array('data' => $element[$key]['control_measure']),
      array('data' => $element[$key]['decision_tree']),
      array('data' => $element[$key]['ccp']),
    );
  }

  // Build the table, with a row per hazard.
  // The table has 3 columns.
  $header = array(
    'process_step' => array(
      'data' => t('Process Step'),
      'class' => array('process-step'),
    ),
    'hazard' => array(
      'data' => t('Hazard'),
      'class' => array('hazard'),
    ),
    'control_measure' => array(
      'data' => t('Control Measure !tip', array(
        '!tip' => _help_tip(),
      )),
      'class' => array('control-measure'),
    ),
    'decision_tree' => array(
      'data' => t('Decision Tree Q\'s !tip', array(
        '!tip' => _help_tip(),
      )),
      'class' => array('decision-tree'),
    ),
    'ccp' => array(
      'data' => t('CCP? !tip', array(
        '!tip' => _help_tip(),
      )),
      'class' => array('ccp'),
    ),
  );

  return theme('table', array('header' => $header, 'rows' => $rows));
}
