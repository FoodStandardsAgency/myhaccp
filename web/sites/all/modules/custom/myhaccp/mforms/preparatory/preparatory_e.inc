<?php

function preparatory_e(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_f';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'preparatory_e');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  drupal_set_title('Preparatory Stage E: Describe the product', PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'prep-e';

  // Wrap the form section in a fieldset.
  $form['prep_e'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // 1. Ingredients.
  $form['prep_e']['ingredients'] = array(
    '#type' => 'textarea',
    '#title' => t('1. List all the ingredients with the supplier for each in brackets. !tip', array(
      '!tip' => _help_tip(12),
    )),
    '#default_value' => array_get($values, 'prep_e.ingredients', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('List all ingredients e.g. Potatoes (Rangeman), Milk (Dairy Cream),  Green pepper (Lewis’s Wholesale Vegetables).'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please list all the ingredients and the supplier for each.'),
    ),
  );

  // 2. Physical properties.
  $form['prep_e']['properties'] = array(
    '#type' => 'textarea',
    '#title' => t('2. State the physical properties (A<sub>w</sub>,pH,emulsion). !tip', array(
      '!tip' => _help_tip(12),
    )),
    '#default_value' => array_get($values, 'prep_e.properties', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('Provide physical details of the product e.g. NaCL 10%, pH  less than or equal to 4.3, A<sub>w</sub> 0.912'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state the physical properties of the product.'),
    ),
  );

  // 3. Product processed description.
  $form['prep_e']['processed'] = array(
    '#type' => 'textarea',
    '#title' => t('3. Describe how the product has been processed and/or other preservation methods. !tip', array(
      '!tip' => _help_tip(12),
    )),
    '#default_value' => array_get($values, 'prep_e.properties', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('Has the product been heated and to what extent, what other preservation methods have been applied e.g. pasterising, brining, smoking.'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please describe how the product has been processed.'),
    ),
  );

  // 4. Product processed description.
  $form['prep_e']['packed'] = array(
    '#type' => 'textarea',
    '#title' => t('4. How was the product packed and what are the packaging materials? !tip', array(
      '!tip' => _help_tip(12),
    )),
    '#default_value' => array_get($values, 'prep_e.properties', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('Examples include vacuum packing, bottles and jars, packed in a protective atmosphere, canned, flexible packaging (be specific bags, pouches), trays.'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please describe how the product was packed and the packaging materials.'),
    ),
  );

  // 5. Product stored and distributed.
  $form['prep_e']['stored'] = array(
    '#type' => 'textarea',
    '#title' => t('5. How is the product going to be stored and distributed? !tip', array(
      '!tip' => _help_tip(12),
    )),
    '#default_value' => array_get($values, 'prep_e.properties', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('State how the product should be kept (during storage and distribution of the product) e.g. product to be kept chilled, frozen or heated.'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please describe how the product is going to be stored and distributed.'),
    ),
  );

  // 6. State the shelf-life of the product?
  $form['prep_e']['shelf_life'] = array(
    '#type' => 'textarea',
    '#title' => t('6. State the shelf-life of the product. !tip', array(
      '!tip' => _help_tip(12),
    )),
    '#default_value' => array_get($values, 'prep_e.properties', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('State either the use by or the best-before date.'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state the shelf-life of the product.'),
    ),
  );

  // 7. State instructions for product use.
  $form['prep_e']['handled'] = array(
    '#type' => 'textarea',
    '#title' => t('7. State how the product is to be stored and handled. !tip', array(
      '!tip' => _help_tip(12),
    )),
    '#default_value' => array_get($values, 'prep_e.properties', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('State how the product is to be stored e.g. in the fridge, at room temperature, kept frozen. State what should be done with it prior to consumption e.g. if product is to be defrosted prior to cooking. Instructions for how the product should be cooked.'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state how the product is to be stored and handling and storage instructions.'),
    ),
  );

  $form['#validate'][] = 'preparatory_e_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_e_validate($form, &$form_state) {
  $invalid = array();

  // Checks is an array with the key being the element being targeted (in dot
  // notation) and the value being the callback to use to check whether the
  // field is empty.
  $checks = array(
    'prep_e.ingredients' => '_text_field_is_empty',
    'prep_e.properties' => '_text_field_is_empty',
    'prep_e.processed' => '_text_field_is_empty',
    'prep_e.packed' => '_text_field_is_empty',
    'prep_e.stored' => '_text_field_is_empty',
    'prep_e.shelf_life' => '_text_field_is_empty',
    'prep_e.handled' => '_text_field_is_empty',
  );

  foreach ($checks as $target => $callback) {
    $invalid[] = _check_validation($callback, $target, $form, $form_state);
  }

  // Check to see whether we have failed validation and therefore should store
  // it in the database or whether we have passed and therefore clear validation
  // errors.
  if (!in_array(TRUE, $invalid)) {
    // Remove any stored validation.
    myhaccp_clear_validation($form_state);
  }
}
