<?php

function preparatory_f(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_g';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  drupal_set_title('Preparatory Stage F: Describe the product', PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'prep-e';

  // Wrap the form section in a fieldset.
  $form['container'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // 1. Name of the product?
  $form['container']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('1. Name of the product: !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.name', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify the name of the product.'),
    ),
  );

  // 2. Physical properties.
  $form['container']['young'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('2. Is the product designed for the young? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.young', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify if the product is designed for the young.'),
    ),
  );

  // 3. Product processed description.
  $form['container']['elderly'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('3. Is the product designed for the elderly? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.elderly', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify if the product is designed for the elderly.'),
    ),
  );

  // 4. Product processed description.
  $form['container']['pregnant'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('4. Is the product designed for pregnant ladies? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.pregnant', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify if the product is designed for pregnant ladies.'),
    ),
  );

  // 5. Product stored and distributed.
  $form['container']['immuno'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('5. Is the product designed for the immunosuppressed / immunocompromised? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.immuno', array()),
    '#help_text' => t('State how the product should be kept  (during storage and distribution of the product) e.g. product to be kept chilled, frozen or heated.'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify if the product is designed for the immunosuppressed / immunocompromised.'),
    ),
  );

  // 6. State the shelf-life of the product?
  $form['container']['allergies'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('6. Is the product suitable for people with allergies or intolerances? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.allergies', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify if the product is suitable for people with allergies or intolerances.'),
    ),
  );

  // 7. Are there any other groups of people that may consume your product that
  // require special consideration?
  $form['container']['special'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('7. Are there any other groups of people that may consume your product that require special consideration? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.special', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify if there are any other groups of people that may consume your product that require special consideration.'),
    ),
  );

  // 8. Is it possible that your product could be consumed by someone other
  // than those for whom it is intended?
  $form['container']['intended'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('8. Is it possible that your product could be consumed by someone other than those for whom it is intended? !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.intended', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify whether it is possible that your product could be consumed by someone other than those for whom it is intended'),
    ),
  );

  // 9. Detail below how you have considered the likely abuse / unintended use
  // of the product by the consumer.
  $form['container']['abuse'] = array(
    '#type' => 'textarea',
    '#title' => t('9. Detail below how you have considered the likely abuse / unintended use of the product by the consumer. !tip', array(
      '!tip' => _help_tip(),
    )),
    '#default_value' => array_get($values, 'container.abuse', array()),
    '#resizable' => FALSE,
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify how how you have considered the likely abuse / unintended use of the product by the consumer.'),
    ),
  );

  $form['#validate'][] = 'preparatory_f_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_f_validate($form, &$form_state) {
  // Assume this form is valid.
  $invalid = FALSE;
  $values = $form_state['values'];

  if ($invalid = _text_field_is_empty($values, 'container.name')) {
    $message = array_get($form, 'container.name.#attributes.data-parsley-error-message', NULL);
    myhacpp_prepare_validation('container[name]', $message, $form_state);
  }

  if ($invalid = _radios_field_is_empty($values, 'container.young')) {
    $message = array_get($form, 'container.young.#attributes.data-parsley-error-message', NULL);
    myhacpp_prepare_validation('container[young]', $message, $form_state);
  }

  if ($invalid = _radios_field_is_empty($values, 'container.elderly')) {
    $message = array_get($form, 'container.elderly.#attributes.data-parsley-error-message', NULL);
    myhacpp_prepare_validation('container[elderly]', $message, $form_state);
  }

  if ($invalid = _radios_field_is_empty($values, 'container.pregnant')) {
    $message = array_get($form, 'container.pregnant.#attributes.data-parsley-error-message', NULL);
    myhacpp_prepare_validation('container[pregnant]', $message, $form_state);
  }

  if ($invalid = _radios_field_is_empty($values, 'container.immuno')) {
    $message = array_get($form, 'container.immuno.#attributes.data-parsley-error-message', NULL);
    myhacpp_prepare_validation('container[immuno]', $message, $form_state);
  }

  if ($invalid = _radios_field_is_empty($values, 'container.allergies')) {
    $message = array_get($form, 'container.allergies.#attributes.data-parsley-error-message', NULL);
    myhacpp_prepare_validation('container[allergies]', $message, $form_state);
  }

  if ($invalid = _radios_field_is_empty($values, 'container.special')) {
    $message = array_get($form, 'container.special.#attributes.data-parsley-error-message', NULL);
    myhacpp_prepare_validation('container[special]', $message, $form_state);
  }

  if ($invalid = _radios_field_is_empty($values, 'container.intended')) {
    $message = array_get($form, 'container.intended.#attributes.data-parsley-error-message', NULL);
    myhacpp_prepare_validation('container[intended]', $message, $form_state);
  }

  if ($invalid = _text_field_is_empty($values, 'container.abuse')) {
    $message = array_get($form, 'container.abuse.#attributes.data-parsley-error-message', NULL);
    myhacpp_prepare_validation('container[abuse]', $message, $form_state);
  }

  // Check to see whether we have failed validation and therefore should store
  // it in the database or whether we have passed and therefore clear validation
  // errors.
  if ($invalid == FALSE) {
    // Remove any stored validation.
    myhaccp_clear_validation($form_state);
  }
}
