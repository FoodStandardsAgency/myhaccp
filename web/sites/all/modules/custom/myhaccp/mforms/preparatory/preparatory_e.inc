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
  $form['preparatory_e'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // 1. Ingredients.
  $form['preparatory_e']['ingredients'] = array(
    '#type' => 'textarea',
    '#title' => t('1. List all the ingredients with the supplier for each in brackets. !tip', array(
      '!tip' => _help_tip(18),
    )),
    '#help_text' => t('A full description of the finished product  or intermediate product (depending what your HACCP study covers should be provided.  This should include every ingredient that is used in the product and the supplier.'),
    '#default_value' => array_get($values, 'preparatory_e.ingredients', FALSE),
    '#resizable' => FALSE,
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please list all the ingredients and the supplier for each.'),
    ),
  );

  // 2. Physical properties.
  $form['preparatory_e']['properties'] = array(
    '#type' => 'textarea',
    '#title' => t('2. State the physical properties (a<sub>w</sub>,pH,emulsion). !tip', array(
      '!tip' => _help_tip(18),
    )),
    '#help_text' => t('E.g. a<sub>w</sub> 0.93, pH 4.5.'),
    '#default_value' => array_get($values, 'preparatory_e.properties', FALSE),
    '#resizable' => FALSE,
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state the physical properties of the product.'),
    ),
  );

  // 3. Product processed description.
  $form['preparatory_e']['processed'] = array(
    '#type' => 'textarea',
    '#title' => t('3. Describe how the product has been processed and/or other preservation methods. !tip', array(
      '!tip' => _help_tip(18),
    )),
    '#help_text' => t('Has the product been sterilised, pasteurised, smoked?'),
    '#default_value' => array_get($values, 'preparatory_e.properties', FALSE),
    '#resizable' => FALSE,
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please describe how the product has been processed.'),
    ),
  );

  // 4. Product processed description.
  $form['preparatory_e']['packed'] = array(
    '#type' => 'textarea',
    '#title' => t('4. How was the product packed and what are the packaging materials? !tip', array(
      '!tip' => _help_tip(18),
    )),
    '#help_text' => t('e.g. Is it packed into glass bottles, flexible pouches, aseptically packed?'),
    '#default_value' => array_get($values, 'preparatory_e.properties', FALSE),
    '#resizable' => FALSE,
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please describe how the product was packed and the packaging materials.'),
    ),
  );

  // 5. Product stored and distributed.
  $form['preparatory_e']['stored'] = array(
    '#type' => 'textarea',
    '#title' => t('5. How is the product going to be stored and distributed? !tip', array(
      '!tip' => _help_tip(18),
    )),
    '#default_value' => array_get($values, 'preparatory_e.properties', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('e.g. Is it to be stored frozen , ambient or chilled? Is it to be distributed frozen, ambient or chilled.'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please describe how the product is going to be stored and distributed.'),
    ),
  );

  // 6. State the shelf-life of the product?
  $form['preparatory_e']['shelf_life'] = array(
    '#type' => 'textarea',
    '#title' => t('6. State the shelf-life of the product. !tip', array(
      '!tip' => _help_tip(18),
    )),
    '#help_text' => t('Under the  prescribed conditions what is the use by date or best before date e.g. Use By 3 months from date of purchase or best before  4 months from date of manufacture.'),
    '#default_value' => array_get($values, 'preparatory_e.properties', FALSE),
    '#resizable' => FALSE,
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state the shelf-life of the product.'),
    ),
  );

  // 7. State instructions for product use.
  $form['preparatory_e']['handled'] = array(
    '#type' => 'textarea',
    '#title' => t('7. State how the product is to be stored and handled. !tip', array(
      '!tip' => _help_tip(18),
    )),
    '#help_text' => t('e.g. store in a cool place away from direct light, defrost thoroughly before cooking, cook for 15 minutes at 220°C.'),
    '#default_value' => array_get($values, 'preparatory_e.properties', FALSE),
    '#resizable' => FALSE,
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
    'preparatory_e.ingredients' => '_text_field_is_empty',
    'preparatory_e.properties' => '_text_field_is_empty',
    'preparatory_e.processed' => '_text_field_is_empty',
    'preparatory_e.packed' => '_text_field_is_empty',
    'preparatory_e.stored' => '_text_field_is_empty',
    'preparatory_e.shelf_life' => '_text_field_is_empty',
    'preparatory_e.handled' => '_text_field_is_empty',
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
