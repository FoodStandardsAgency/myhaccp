<?php

function preparatory_f(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_g';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'preparatory_f');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  drupal_set_title('Preparatory Stage F: Identify intended use of the product', PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'prep-f';

  // Wrap the form section in a fieldset.
  $form['preparatory_f'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  // 1. Name of the product?
  $form['preparatory_f']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('1. Name of the product:'),
    '#help_link' => 19,
    '#help_text' => t('Specify the name.'),
    '#default_value' => array_get($values, 'preparatory_f.name', FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify the name of the product.'),
    ),
  );

  // 2. Physical properties.
  $form['preparatory_f']['young'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('2. Is the product designed for the young?'),
    '#help_link' => 19,
    '#help_text' => t('Babies are more vulnerable to choking hazards certain products are not recommended to be consumed by babies e.g. honey.'),
    '#default_value' => array_get($values, 'preparatory_f.young', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify if the product is designed for the young.'),
    ),
  );

  // 3. Product processed description.
  $form['preparatory_f']['elderly'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('3. Is the product designed for the elderly?'),
    '#help_link' => 19,
    '#help_text' => t('Elderly people may require that food is of a smaller size than that to be consumed by non-vulnerable groups.'),
    '#default_value' => array_get($values, 'preparatory_f.elderly', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify if the product is designed for the elderly.'),
    ),
  );

  // 4. Product processed description.
  $form['preparatory_f']['pregnant'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('4. Is the product designed for pregnant ladies?'),
    '#help_link' => 19,
    '#help_text' => t('Certain foods should not be consumed by pregnant ladies because they contain certain microorganisms that may cause a still birth, miscarriage or severe illness.'),
    '#default_value' => array_get($values, 'preparatory_f.pregnant', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify if the product is designed for pregnant ladies.'),
    ),
  );

  // 5. Product stored and distributed.
  $form['preparatory_f']['immuno'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('5. Is the product designed for the immunosuppressed / immunocompromised?'),
    '#help_link' => 19,
    '#help_text' => t('Consider the use of low microbial diets to reduce the risk of foodborne disease.'),
    '#default_value' => array_get($values, 'preparatory_f.immuno', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify if the product is designed for the immunosuppressed / immunocompromised.'),
    ),
  );

  // 6. State the shelf-life of the product?
  $form['preparatory_f']['allergies'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('6. Is the product suitable for people with allergies or intolerances?'),
    '#help_link' => 19,
    '#help_text' => t('Does the product contain any ingredients from the list on substances or products causing allergies or intolerances.'),
    '#default_value' => array_get($values, 'preparatory_f.allergies', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify if the product is suitable for people with allergies or intolerances.'),
    ),
  );

  // 7. Are there any other groups of people that may consume your product that
  // require special consideration?
  $form['preparatory_f']['special'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('7. Are there any other groups of people that may consume your product that require special consideration?'),
    '#help_link' => 19,
    '#help_text' => t('List any others if not considered in steps 2-6.'),
    '#default_value' => array_get($values, 'preparatory_f.special', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify if there are any other groups of people that may consume your product that require special consideration.'),
    ),
  );

  // 8. Is it possible that your product could be consumed by someone other
  // than those for whom it is intended?
  $form['preparatory_f']['intended'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes'),
      'no' => t('No'),
    ),
    '#title' => t('8. Is it possible that your product could be consumed by someone other than those for whom it is intended?'),
    '#help_link' => 19,
    '#help_text' => t('Consider this for all vulnerable groups e.g. could a pregnant person consume your product? Could a baby be fed your product?'),
    '#default_value' => array_get($values, 'preparatory_f.intended', array()),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify whether it is possible that your product could be consumed by someone other than those for whom it is intended'),
    ),
  );

  // 9. Detail below how you have considered the likely abuse / unintended use
  // of the product by the consumer.
  $form['preparatory_f']['abuse'] = array(
    '#type' => 'textarea',
    '#title' => t('9. Detail below how you have considered the likely abuse / unintended use of the product by the consumer.'),
    '#help_link' => 19,
    '#help_text' => t('e.g. It could be possible that a very young child may be fed this product despite it being aimed at those over 36 months.'),
    '#default_value' => array_get($values, 'preparatory_f.abuse', FALSE),
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
  $validator = new validator($form, $form_state, 'preparatory_f');

  if ($validator->allFieldsAreEmpty()) {
    return;
  }

  $checks = array(
    'preparatory_f.name' => 'fieldIsNotEmpty',
    'preparatory_f.young' => 'fieldIsNotEmpty',
    'preparatory_f.elderly' => 'fieldIsNotEmpty',
    'preparatory_f.pregnant' => 'fieldIsNotEmpty',
    'preparatory_f.immuno' => 'fieldIsNotEmpty',
    'preparatory_f.allergies' => 'fieldIsNotEmpty',
    'preparatory_f.special' => 'fieldIsNotEmpty',
    'preparatory_f.intended' => 'fieldIsNotEmpty',
    'preparatory_f.abuse' => 'fieldIsNotEmpty',
  );

  foreach ($checks as $target => $method) {
    $validator->validate($method, $target);
  }

  $validator->setErrorMessages();
}
