<?php

function preparatory_e(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_f';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  drupal_set_title('Preparatory Stage E: Describe the product', PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'prep-e';

  // Wrap the form section in a fieldset.
  $form['container'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // 1. Ingredients.
  $form['container']['ingredients'] = array(
    '#type' => 'textarea',
    '#title' => t('1. List all the ingredients with their origin in brackets. !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.ingredients', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('List all ingredients e.g. Potatoes (UK), milk (UK),  green pepper (Spain).'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please list all the ingredients.'),
    ),
  );

  // 2. Physical properties.
  $form['container']['properties'] = array(
    '#type' => 'textarea',
    '#title' => t('2. State the physical properties (A<sub>w</sub>,pH,emulsion). !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.properties', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('Provide physical details of the product e.g. NaCL 10%, pH  less than or equal to 4.3, Aw 0.912'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state the physical properties.'),
    ),
  );

  // 3. Product processed description.
  $form['container']['processed'] = array(
    '#type' => 'textarea',
    '#title' => t('3. Describe how the product has been processed and/or other preservation methods. !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.properties', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('Has the product been heated and to what extent, what other preservation methods have been applied e.g. pasterising, brining, smoking.'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please describe how the product has been processed.'),
    ),
  );

  // 4. Product processed description.
  $form['container']['packed'] = array(
    '#type' => 'textarea',
    '#title' => t('4. How was the product packed and what are the packaging materials? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.properties', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('Examples include vacuum packing, bottles and jars, packed in a protective atmosphere, canned, flexible packaging (be specific bags, pouches), trays.'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please describe how the product was packed and the packaging materials.'),
    ),
  );

  // 5. Product stored and distributed.
  $form['container']['stored'] = array(
    '#type' => 'textarea',
    '#title' => t('5. How is the product going to be stored and distributed? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.properties', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('State how the product should be kept  (during storage and distribution of the product) e.g. product to be kept chilled, frozen or heated.'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please describe how the product is going to be stored and distributed.'),
    ),
  );

  // 6. State the shelf-life of the product?
  $form['container']['shelf_life'] = array(
    '#type' => 'textarea',
    '#title' => t('6. State the shelf-life of the product. !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.properties', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('State either the use by or the best-before date.'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state the shelf-life of the product.'),
    ),
  );

  // 7. State instructions for product use.
  $form['container']['handled'] = array(
    '#type' => 'textarea',
    '#title' => t('7. State how the product is to be stored and handled. !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.properties', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('State how the product is to be stored e.g. in the fridge, at room temperature, kept frozen.  State what should be done with it prior to consumption e.g. if product is to be defrosted prior to cooking.  Instructions for how the product should be cooked.'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state how the product is to be stored and handling and storage instructions.'),
    ),
  );

  $form['#validate'][] = 'preparatory_e';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_e_validate($form, &$form_state) {
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
