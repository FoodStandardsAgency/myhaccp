<?php

/**
 * Theme function to render the fields in a table.
 *
 * Principle 1 Question 1.
 */
function theme_myhaccp_1_2_table($variables) {
  $element = $variables['element'];

  $rows = array();
  foreach (element_children($element) as $key) {
    $rows[] = array(
      array('data' => $element[$key]['name']['#value']),
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
    'hazard_desc' => t('Hazard Description !tip !help', array(
      '!tip' => _help_tip(),
      '!help' => '<div class="help-text">' . t("Provide a detailed description of the hazard. Think about this stage carefully. It is common to make errors here and this will lead to implications further on. By describing the hazard in more detail it will help you later when you specify the control. Be aware that there may be more than one 'descriptor' for a hazard. If you identify more than one descriptor (this is quite common) you will have to go back to <strong>Principle 1.1</strong> and add an additional hazard, this time however it should have a descriptor in brackets after it (i.e. Salmonella spp (introduction) Salmonella spp (growth).</br> !link", array(
          '!link' => myhaccp_prepare_more_link(17),
        )) . '</div>'
    )),
    'severity' => array(
      'data' => t('Severity (1-3) !tip !help', array(
        '!tip' => _help_tip(),
        '!help' => '<div class="help-text">' . t("Rate on scale of 1 - 3 (1 = minor, 3 = long-term illness leading to death or death). !link", array(
          '!link' => myhaccp_prepare_more_link(17),
        )) . '</div>'
        )),
      'class' => array('severity'),
    ),
    'likelihood' => array(
      'data' => t('Likelihood (1-3) !tip !help', array(
        '!tip' => _help_tip(),
        '!help' => '<div class="help-text">' . t("Rate on scale of 1-3 (1=unlikely to occur but might, 3=definately will occur (at some time if it hasn’t occurred in the past). !link", array(
            '!link' => myhaccp_prepare_more_link(17),
          )) . '</div>'
        )),
      'class' => array('likelihood'),
    ),
    'significance' => array(
      'data' => t('Significance <span>(S x L)</span> !tip !help', array(
        '!tip' => _help_tip(),
        '!help' => '<div class="help-text">' . t("Severity score multiplied by likelihood score. !link", array(
            '!link' => myhaccp_prepare_more_link(17),
          )) . '</div>'
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
function theme_myhaccp_1_3_table($variables) {
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
      'data' => t('Control Measure !tip !help', array(
        '!tip' => _help_tip(27),
        '!help' => '<div class="help-text">For each significant hazard state the control measure (an action and/or activity that is required to prevent, eliminate or reduce the occurrence of the hazard to an acceptable level). ' . myhaccp_prepare_more_link(27) . '</div>'
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
function theme_myhaccp_2_2_table($variables) {
  $element = $variables['element'];

  $data = mforms_get_vals('myhaccp', 'principle_2_1');

  $decision_tree_value = array_get($data, 'principle_2_1.2_1_1', FALSE);
  $decision_tree = $decision_tree_value == 'yes' ? TRUE : FALSE;

  $rows = array();

  foreach (element_children($element) as $key) {
    $row = array(
      array('data' => $element[$key]['process_step']),
      array('data' => $element[$key]['hazard']),
      array('data' => $element[$key]['control_measure']),
    );
    if ($decision_tree) {
      $row[] = array('data' => $element[$key]['decision_tree']);
    }
    $row[] = array('data' => $element[$key]['ccp']);
    $rows[] = $row;
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
      'data' => t('Control Measure', array(
        '!tip' => _help_tip(28),
      )),
      'class' => array('control-measure'),
    ),
    'decision_tree' => array(
      'data' => t('Decision Tree Q\'s !tip !help', array(
        '!tip' => _help_tip(28),
         '!help' => '<div class="help-text">Be very careful to answer the questions correctly.' . myhaccp_prepare_more_link(28) . '</div>'
      )),
      'class' => array('decision-tree'),
    ),
    'ccp' => array(
      'data' => t('CCP? !tip !help', array(
        '!tip' => _help_tip(28),
        '!help' => '<div class="help-text">Providing you have answered  the  questions to the decision tree correctly , and entered the answers  into the system  correctly this will show whether the control of the hazard is regarded as a critical control point or not according to Campden or Codex.</div>'
      )),
      'class' => array('ccp'),
    ),
  );

  // If not using a decision tree then don't show anything for that column.
  if (!$decision_tree) {
    unset($header['decision_tree']);
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Theme function for showing a preview image thumbnail for uploaded diagrams.
 *
 * @param array $variables
 *   The available variables.
 *
 * @return string
 *   The rendered HTML output.
 */
function theme_myhaccp_preview_diagram($variables) {
  $element = $variables['element'];

  if (isset($element['#file']->uri)) {
    $image = theme('image_style', array(
      'style_name' => 'thumbnail',
      'path' => $element['#file']->uri,
    ));
    return $image;
  }
}
