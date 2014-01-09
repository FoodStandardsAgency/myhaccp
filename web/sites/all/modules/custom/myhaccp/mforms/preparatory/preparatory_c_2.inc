<?php

function preparatory_c(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_d';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  if (!empty($data)) {
    $values = $data;
  }
  elseif (isset($form_state['values'])) {
    $values = $form_state['values'];
  }

  drupal_set_title('Preparatory Stage: Define scope of the study, Question 4');

  $form = array();

  // Wrap the form section in a fieldset.
  $form['container'] = array(
    '#type' => 'fieldset',
  );

  $form['container']['prep_c_q1'] = array(
    '#type' => 'select',
    '#title' => t('1. What hazards will the HACCP plan cover? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#options' => drupal_map_assoc(
      array(
        t('Linear'),
        t('Modular'),
        t('Linear / Modular'),
        t('Generic'),
      )
    ),
    '#default_value' => isset($values['prep_c_q1']) ? $values['prep_c_q1'] : NULL
  );

  $form['container']['prep_c_q2'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('2. State the type of product you are producing and briefly how it is going to be packed: !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => isset($values['prep_c_q2']) ? $values['prep_c_q2'] : NULL
  );

  $form['container']['start_end'] = array(
    '#type' => 'container',
  );

  $form['container']['start_end']['title'] = array(
    '#markup' => '<div class="label">' . t('3. State start and end points of the HACCP plan: !tip', array(
      '!tip' => _help_tip(),
      )
    ) . '</div>',
  );

  $form['container']['start_end']['start'] = array(
    '#type' => 'textfield',
    '#title' => t('It will start at '),
    '#default_value' => isset($values['start']) ? $values['start'] : NULL
  );

  $form['container']['start_end']['end'] = array(
    '#type' => 'textfield',
    '#title' => t('Through to '),
    '#default_value' => isset($values['end']) ? $values['end'] : NULL
  );

  return $form;
}
