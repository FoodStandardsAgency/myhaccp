<?php

/**
 * @file
 * Preparatory E stage form and validation handler.
 */

/**
 * Preparatory E.
 */
function preparatory_e(&$form_state, &$next_step) {
  // @ignore comment_comment_eg:function

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_f';

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'preparatory_e');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  drupal_set_title($stage->title, PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'prep-e';

  // Wrap the form section in a fieldset.
  $form['preparatory_e'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array(
      'class' => array(
        'stage-fieldset',
      ),
    ),
  );

  $form['preparatory_e']['intro'] = array(
    '#prefix' => '<p class="intro">',
    '#suffix' => '</p>',
    '#markup' => t('This requires a full description of the product. This will help understanding of the presented hazards with the product/process and on what it relies on for safety.'),
  );

  // 1. Ingredients.
  $form['preparatory_e']['e_1'] = array(
    '#type' => 'textarea',
    '#title' => t('1. List all the ingredients and the name of the supplier for each one.'),
    '#help_link' => 18,
    '#help_text' => t('A full description of the finished product  or intermediate product (depending what your HACCP study covers should be provided.  This should include every ingredient that is used in the product and the supplier.'),
    '#default_value' => array_get($values, 'preparatory_e.e_1', FALSE),
    '#resizable' => FALSE,
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please list all the ingredients and the supplier for each.'),
    ),
  );

  // 2. Physical properties.
  $form['preparatory_e']['e_2'] = array(
    '#type' => 'textarea',
    '#title' => t('2. State the physical properties of the product (a<sub>w</sub>,pH,emulsion).'),
    '#help_link' => 18,
    '#help_text' => t('E.g. a<sub>w</sub> 0.93, pH 4.5.'),
    '#default_value' => array_get($values, 'preparatory_e.e_2', FALSE),
    '#resizable' => FALSE,
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state the physical properties of the product.'),
    ),
  );

  // 3. Product processed description.
  $form['preparatory_e']['e_3'] = array(
    '#type' => 'textarea',
    '#title' => t('3. Describe how the product is processed and/or other preservation methods used.'),
    '#help_link' => 18,
    '#help_text' => t('Has the product been sterilised, pasteurised, smoked?'),
    '#default_value' => array_get($values, 'preparatory_e.e_3', FALSE),
    '#resizable' => FALSE,
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please describe how the product has been processed.'),
    ),
  );

  // 4. Product processed description.
  $form['preparatory_e']['e_4'] = array(
    '#type' => 'textarea',
    '#title' => t('4. Describe how the product is packed and the packaging materials.'),
    '#help_link' => 18,
    '#help_text' => t('e.g. Is it packed into glass bottles, flexible pouches, aseptically packed?'),
    '#default_value' => array_get($values, 'preparatory_e.e_4', FALSE),
    '#resizable' => FALSE,
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please describe how the product was packed and the packaging materials.'),
    ),
  );

  // 5. Product stored and distributed.
  $form['preparatory_e']['e_5'] = array(
    '#type' => 'textarea',
    '#title' => t('5. How is the product going to be stored and distributed?'),
    '#help_link' => 18,
    '#default_value' => array_get($values, 'preparatory_e.e_5', FALSE),
    '#resizable' => FALSE,
    '#help_text' => t('e.g. Is it to be stored frozen , ambient or chilled? Is it to be distributed frozen, ambient or chilled.'),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please describe how the product is going to be stored and distributed.'),
    ),
  );

  // 6. State the shelf-life of the product?
  $form['preparatory_e']['e_6'] = array(
    '#type' => 'textarea',
    '#title' => t('6. What is the shelf-life of the product?'),
    '#help_link' => 18,
    '#help_text' => t('Under the  prescribed conditions what is the use by date or best before date e.g. Use By 3 months from date of purchase or best before  4 months from date of manufacture.'),
    '#default_value' => array_get($values, 'preparatory_e.e_6', FALSE),
    '#resizable' => FALSE,
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state the shelf-life of the product.'),
    ),
  );

  // 7. State instructions for product use.
  $form['preparatory_e']['e_7'] = array(
    '#type' => 'textarea',
    '#title' => t('7. State what your advice is to the purchaser for storing, handling and preparing the product.'),
    '#help_link' => 18,
    '#help_text' => t('e.g. store in a cool place away from direct light, defrost thoroughly before cooking, cook for 15 minutes at 220°C.'),
    '#default_value' => array_get($values, 'preparatory_e.e_7', FALSE),
    '#resizable' => FALSE,
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state how the product is to be stored and handling and storage instructions.'),
    ),
  );

  $form['#validate'][] = __FUNCTION__ . '_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_e_validate($form, &$form_state) {
  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  $validator = $stage->getValidator();
  $validator->setFormState($form_state);
  $validator->setForm($form);

  if ($validator->pagerButtonUsed() && $validator->allFieldsAreEmpty()) {
    return;
  }

  $checks = array(
    'preparatory_e.e_1' => 'fieldIsNotEmpty',
    'preparatory_e.e_2' => 'fieldIsNotEmpty',
    'preparatory_e.e_3' => 'fieldIsNotEmpty',
    'preparatory_e.e_4' => 'fieldIsNotEmpty',
    'preparatory_e.e_5' => 'fieldIsNotEmpty',
    'preparatory_e.e_6' => 'fieldIsNotEmpty',
    'preparatory_e.e_7' => 'fieldIsNotEmpty',
  );

  foreach ($checks as $target => $method) {
    $validator->validate($method, $target);
  }

  $validator->setErrorMessages();
  $form_state = $validator->getFormState();
}
