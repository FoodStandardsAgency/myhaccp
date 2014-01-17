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
  $form['#attributes']['class'][] = 'prep-c-2';

  // Show global message on this form.
  $form['validation_messages'] = array(
    '#type' => 'container',
    '#id' => 'validation-messages',
    '#weight' => -10,
    '#attributes' => array(
      'data-validation-stage' => 'preparatory_c_question_4',
    ),
  );

  // Wrap the form section in a fieldset.
  $form['prep_c_q4'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $form['prep_c_q4']['wrapper_title'] = array(
    '#markup' => '<div class="label">' . t('1. What hazards will the HACCP plan cover? !tip', array(
      '!tip' => _help_tip(),
    )) . '</div>',
  );

  // Physical hazards.

  $form['prep_c_q4']['wrapper']['physical_prep_c_q4'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'physical',
    ),
  );

  $form['prep_c_q4']['wrapper']['physical_prep_c_q4']['physical'] = array(
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
    '#default_value' => array_get($values, 'prep_c_q4.wrapper.physical_prep_c_q4.physical', array()),
  );

  $form['prep_c_q4']['wrapper']['physical_prep_c_q4']['physical_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'prep_c_q4.wrapper.physical_prep_c_q4.physical_other', FALSE),
  );

  // Chemical.

  $form['prep_c_q4']['wrapper']['chemical_prep_c_q4'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'chemical',
    ),
  );

  $form['prep_c_q4']['wrapper']['chemical_prep_c_q4']['chemical'] = array(
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
    '#default_value' => array_get($values, 'prep_c_q4.wrapper.chemical_prep_c_q4.chemical', array()),
  );

  $form['prep_c_q4']['wrapper']['chemical_prep_c_q4']['chemical_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'prep_c_q4.wrapper.chemical_prep_c_q4.chemical_other', FALSE),
  );

  // Biological.

  $form['prep_c_q4']['wrapper']['biological_prep_c_q4'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'biological',
    ),
  );

  $form['prep_c_q4']['wrapper']['biological_prep_c_q4']['biological'] = array(
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
    '#default_value' => array_get($values, 'prep_c_q4.wrapper.biological_prep_c_q4.biological', array()),
  );

  $form['prep_c_q4']['wrapper']['biological_prep_c_q4']['biological_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'prep_c_q4.wrapper.biological_prep_c_q4.biological_other', FALSE),
  );

  // Allergens.

  $form['prep_c_q4']['wrapper']['allergens_prep_c_q4'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'allergens',
    ),
  );

  $form['prep_c_q4']['wrapper']['allergens_prep_c_q4']['allergens'] = array(
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
    '#default_value' => array_get($values, 'prep_c_q4.wrapper.allergens_prep_c_q4.allergens', array()),
  );

  $form['prep_c_q4']['wrapper']['allergens_prep_c_q4']['allergens_other'] = array(
    '#type' => 'textarea',
    '#title' => t('Other'),
    '#default_value' => array_get($values, 'prep_c_q4.wrapper.allergens_prep_c_q4.allergens_other', FALSE),
  );

  $form['#validate'][] = 'preparatory_c_question_4_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_c_question_4_validate($form, &$form_state) {
  $invalid = array();

  // Validation: Some content.
  $checks = array(
    'prep_c_q4.wrapper.physical_prep_c_q4.physical' => '_checkboxes_field_is_empty',
    'prep_c_q4.wrapper.chemical_prep_c_q4.chemical' => '_checkboxes_field_is_empty',
    'prep_c_q4.wrapper.biological_prep_c_q4.biological' => '_checkboxes_field_is_empty',
    'prep_c_q4.wrapper.allergens_prep_c_q4.allergens' => '_checkboxes_field_is_empty',
    'prep_c_q4.wrapper.physical_prep_c_q4.physical_other' => '_text_field_is_empty',
    'prep_c_q4.wrapper.chemical_prep_c_q4.chemical_other' => '_text_field_is_empty',
    'prep_c_q4.wrapper.biological_prep_c_q4.biological_other' => '_text_field_is_empty',
    'prep_c_q4.wrapper.allergens_prep_c_q4.allergens_other' => '_text_field_is_empty',
  );

  foreach ($checks as $target => $callback) {
    $invalid[] = _check_validation($callback, $target, $form, $form_state, TRUE);
  }

  if (!in_array(FALSE, $invalid)) {
    $message = t('Please add some content.');
    myhacpp_prepare_validation('global', array('preparatory_c_question_4' => $message), $form_state);
  }

  // Check to see whether we have failed validation and therefore should store
  // it in the database or whether we have passed and therefore clear validation
  // errors.
  if (!in_array(TRUE, $invalid)) {
    // Remove any stored validation.
    myhaccp_clear_validation($form_state);
  }
}
