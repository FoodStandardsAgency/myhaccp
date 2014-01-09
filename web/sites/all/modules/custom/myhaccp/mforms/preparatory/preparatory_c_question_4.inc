<?php

function preparatory_c_question_4(&$form_state, &$next_step) {

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
  $form['#attributes']['class'][] = 'pcq4';

  // Wrap the form section in a fieldset.
  $form['container'] = array(
    '#type' => 'fieldset',
  );

  $form['container']['prep_c_q4_title'] = array(
    '#markup' => '<div class="label">' . t('1. What hazards will the HACCP plan cover? !tip', array(
      '!tip' => _help_tip(),
    )) . '</div>',
  );

  // Physical hazards.

  $form['container']['prep_c_q4']['physical_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'physical',
    ),
  );

  $form['container']['prep_c_q4']['physical_container']['physical'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Physical'),
    '#options' => drupal_map_assoc(
      array(
        t('Glass and brittle plastic'),
        t('Metal'),
        t('Wood'),
        t('Bone'),
        t('Fragments'),
        t('Item'),
      )
    ),
    '#default_value' => isset($values['physical']) ? $values['physical'] : array(),
  );

  $form['container']['prep_c_q4']['physical_container']['physical_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => isset($values['physical_other']) ? $values['physical_other'] : NULL
  );

  // Chemical.

  $form['container']['prep_c_q4']['chemical_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'physical',
    ),
  );

  $form['container']['prep_c_q4']['chemical_container']['chemical'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Chemical'),
    '#options' => drupal_map_assoc(
      array(
        t('Glass and brittle plastic'),
        t('Metal'),
        t('Wood'),
        t('Bone'),
        t('Fragments'),
        t('Item'),
      )
    ),
    '#default_value' => isset($values['chemical']) ? $values['chemical'] : array(),
  );

  $form['container']['prep_c_q4']['chemical_container']['chemical_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => isset($values['chemical_other']) ? $values['chemical_other'] : NULL
  );

  // Biological.

  $form['container']['prep_c_q4']['biological_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'physical',
    ),
  );

  $form['container']['prep_c_q4']['biological_container']['biological'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Biological'),
    '#options' => drupal_map_assoc(
      array(
        t('Glass and brittle plastic'),
        t('Metal'),
        t('Wood'),
        t('Bone'),
        t('Fragments'),
        t('Item'),
      )
    ),
    '#default_value' => isset($values['biological']) ? $values['biological'] : array(),
  );

  $form['container']['prep_c_q4']['biological_container']['biological_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => isset($values['biological_other']) ? $values['biological_other'] : NULL
  );

  // Allergens.

  $form['container']['prep_c_q4']['allergens_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'physical',
    ),
  );

  $form['container']['prep_c_q4']['allergens_container']['allergens'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Allergens'),
    '#options' => drupal_map_assoc(
      array(
        t('Glass and brittle plastic'),
        t('Metal'),
        t('Wood'),
        t('Bone'),
        t('Fragments'),
        t('Item'),
      )
    ),
    '#default_value' => isset($values['allergens']) ? $values['allergens'] : array(),
  );

  $form['container']['prep_c_q4']['allergens_container']['allergens_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => isset($values['allergens_other']) ? $values['allergens_other'] : NULL
  );

  return $form;
}
