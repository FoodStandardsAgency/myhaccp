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
  $values = myhaccp_prepare_values($data, $form_state);

  drupal_set_title('Preparatory Stage C: Define scope of the study, <br/>Question 4', PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'pcq4';

  // Wrap the form section in a fieldset.
  $form['container'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
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
    '#default_value' => array_get($values, 'container.prep_c_q4.physical_container.physical', array()),
  );

  $form['container']['prep_c_q4']['physical_container']['physical_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'container.prep_c_q4.physical_container.physical_other', FALSE),
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
    '#default_value' => array_get($values, 'container.prep_c_q4.chemical_container.chemical', array()),
  );

  $form['container']['prep_c_q4']['chemical_container']['chemical_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'container.prep_c_q4.chemical_container.chemical_other', FALSE),
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
    '#default_value' => array_get($values, 'container.prep_c_q4.biological_container.biological', array()),
  );

  $form['container']['prep_c_q4']['biological_container']['biological_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'container.prep_c_q4.biological_container.biological_other', FALSE),
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
    '#default_value' => array_get($values, 'container.prep_c_q4.allergens_container.allergens', array()),
  );

  $form['container']['prep_c_q4']['allergens_container']['allergens_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'container.prep_c_q4.allergens_container.allergens_other', FALSE),
  );

  $form['#validate'][] = 'preparatory_c_question_4_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_c_question_4_validate($form, &$form_state) {
  // Assume this form is invalid.
  $invalid = TRUE;
  $values = $form_state['values'];

  // Validation: Some content.
  $checks = array(
    $physical = _checkboxes_field_is_empty($values, 'container.prep_c_q4.physical_container.physical'),
    $chemical = _checkboxes_field_is_empty($values, 'container.prep_c_q4.chemical_container.chemical'),
    $biological = _checkboxes_field_is_empty($values, 'container.prep_c_q4.biological_container.biological'),
    $allergens = _checkboxes_field_is_empty($values, 'container.prep_c_q4.allergens_container.allergens'),
    $physical_other = _text_field_is_empty($values, 'container.prep_c_q4.physical_container.physical_other'),
    $chemical_other = _text_field_is_empty($values, 'container.prep_c_q4.chemical_container.chemical_other'),
    $biological_other = _text_field_is_empty($values, 'container.prep_c_q4.biological_container.biological_other'),
    $allergens_other = _text_field_is_empty($values, 'container.prep_c_q4.allergens_container.allergens_other'),
  );

  // Iterate through all the field checks and if we get any FALSE returns it
  // means we have some content in a field. This will no longer invalidate the
  // form.
  foreach ($checks as $check) {
    if ($check == FALSE) {
      $invalid = FALSE;
    }
  }

  if ($invalid == TRUE) {
    $message = t('Q4: Add some content.');
    myhacpp_prepare_validation('global', $message, $form_state);
  }

  // Check to see whether we have failed validation and therefore should store
  // it in the database or whether we have passed and therefore clear validation
  // errors.
  if ($invalid == FALSE) {
    // Remove any stored validation.
    myhaccp_clear_validation($form_state);
  }
}
