<?php

/**
 * @file
 * Principle 6 stage form and validation handler.
 */

/**
 * Principle 6.
 */
function principle_6(&$form_state, &$next_step) {
  // @ignore comment_comment_eg:function

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_7';

  // Retrieve submitted values.
  $data = mforms_get_vals('myhaccp', 'principle_6');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default vals.
  $values = myhaccp_prepare_values($data, $form_state);

  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  drupal_set_title($stage->title, PASS_THROUGH);

  $form = array();
  $form['#attributes']['class'][] = 'principle-6';

  // Wrap the form section in a fieldset.
  $form['principle_6'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array(
      'class' => array(
        'stage-fieldset',
      ),
    ),
  );

  // Create the fieldset container.
  $form['principle_6'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array(
      'class' => array(
        'stage-fieldset',
      ),
    ),
  );

  // Introductory text.
  $form['principle_6']['intro'] = array(
    '#prefix' => '<p class="intro">',
    '#suffix' => '</p>',
    '#markup' => t('Verification is the principle which confirms that the HACCP plan, if followed, will produce safe food. First you need to validate the HACCP system to ensure that it is fit for purpose and effectively controls the hazards you identified. This is to be carried out prior to implementation and before the product is placed on the market.'),
  );

  // Now the form fields.
  $form['principle_6']['6_1'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('1. Document your validation study in the space below.'),
    '#help_text' => t('Provide details of all validation studies carried out.'),
    '#help_link' => 32,
    '#default_value' => array_get($values, "principle_6.6_1", FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please add documentation of your validation study.'),
    ),
  );

  $form['principle_6']['6_2'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('2. Who is responsible for ensuring the contents of the whole HACCP plan (this may include several HACCP studies) are validated?'),
    '#help_text' => t('Enter the name of the person  responsible.'),
    '#help_link' => 32,
    '#default_value' => array_get($values, "principle_6.6_2", FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state who is responsible for ensuring the contents of the HACCP plan are validated.'),
    ),
  );

  $form['principle_6']['6_3'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes', array(), array('context' => 'Is this the same person who will formally sign off the whole HACCP plan?')),
      'no' => t('No', array(), array('context' => 'Is this the same person who will formally sign off the whole HACCP plan?')),
    ),
    '#title' => t('3. Is this the same person who will formally sign off the whole HACCP plan (which may contain several HACCP studies)?'),
    '#help_text' => t('Enter the name of the person.'),
    '#help_link' => 32,
    '#default_value' => array_get($values, "principle_6.6_3", FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please indicate if this is the same person who will formally sign off the HACCP plan.'),
    ),
  );

  $form['principle_6']['6_3a'] = array(
    '#type' => 'textfield',
    '#title' => t('3a. Who will formally sign off the HACCP plan?'),
    '#default_value' => array_get($values, "principle_6.6_3a", FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('Please state who is responsible for ensuring the contents of the HACCP plan are validated.'),
    ),
    '#states' => array(
      'visible' => array(
        ':input[name="principle_6[6_3]"]' => array('value' => 'no'),
      ),
    ),
  );

  $form['principle_6']['6_4'] = array(
    '#type' => 'container',
    '#prefix' => '<div class="label">' . t('4. What verification activities do you carry out? Mark all those that apply.') . '</div>',
  );

  $form['principle_6']['6_4']['1'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Internal audits of'),
    '#options' => array(
      'ccps' => t('Critical Control Points'),
      'prerequisites' => t('Prerequisites'),
      'records' => t('Records of monitoring'),
      'corrective' => t('Corrective actions'),
    ),
    '#default_value' => array_get($values, "principle_6.6_4.1", array()),
  );

  $form['principle_6']['6_4']['2'] = array(
    '#type' => 'checkboxes',
    '#title' => t('External auditing programmes'),
    '#options' => array(
      'supplier' => t('Supplier audits'),
    ),
    '#default_value' => array_get($values, "principle_6.6_4.2", array()),
  );

  $form['principle_6']['6_4']['3'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Finished product'),
    '#options' => array(
      'microbial' => t('Microbiological testing'),
      'chemical' => t('Chemical testing'),
    ),
    '#default_value' => array_get($values, "principle_6.6_4.3", array()),
  );

  $form['principle_6']['6_4']['4'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Interim product'),
    '#options' => array(
      'microbial' => t('Microbiological testing'),
      'chemical' => t('Chemical testing'),
    ),
    '#default_value' => array_get($values, "principle_6.6_4.4", array()),
  );

  $form['principle_6']['6_4']['5'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Other'),
    '#options' => array(
      'monitoring' => t('Environmental monitoring of production area'),
      'findings' => t('Addressing the findings of customer and third party audits'),
      'third_party' => t('Third party certification(SOFHT, BRC)'),
      'trending' => t('Trending and analysing customer complaints'),
      'buy' => t('Product buy - back(buying your product from end point in market place and sampling and testing it for unexpected safety problems'),
    ),
    '#default_value' => array_get($values, "principle_6.6_4.5", array()),
  );

  $form['principle_6']['6_4']['6'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Reviewing'),
    '#options' => array(
      'deviations' => t('Deviations'),
      'corrective' => t('Corrective actions'),
      'disposal' => t('Product disposal'),
      'rework' => t('Rework'),
      'trending' => t('Trending of monitoring results'),
    ),
    '#default_value' => array_get($values, "principle_6.6_4.6", array()),
  );

  $form['principle_6']['6_5'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#title' => t('5. List any other verification activities carried out in your organisation.'),
    '#help_text' => t('If you carry out additional verification activities not listed above, record them here.'),
    '#help_link' => 32,
    '#default_value' => array_get($values, "principle_6.6_5", FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('Please list any other verification activities carried out in your organisation.'),
    ),
  );

  $form['principle_6']['6_6'] = array(
    '#type' => 'radios',
    '#options' => array(
      'yes' => t('Yes', array(), array('context' => 'Are all verification records maintained?')),
      'no' => t('No', array(), array('context' => 'Are all verification records maintained?')),
    ),
    '#title' => t('6. Are all verification records maintained?'),
    '#help_text' => t('You should keep verification records for a minimum of the life of a product  plus an extension period of ‘typically’ 3 months.  You must take into consideration abuse of your product and may wish to keep records for a longer period.'),
    '#help_link' => 32,
    '#default_value' => array_get($values, "principle_6.6_6", FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please confirm that all verification records are maintained.'),
    ),
  );

  $form['principle_6']['6_7'] = array(
    '#type' => 'textfield',
    '#title' => t('7. How often is the whole HACCP plan formally reviewed?'),
    '#help_text' => t('Is this annually, bi-annually or more frequently?'),
    '#help_link' => 32,
    '#default_value' => array_get($values, "principle_6.6_7", FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please detail how often the HACCP system is formally reviewed.'),
    ),
  );

  $form['principle_6']['6_8'] = array(
    '#type' => 'textfield',
    '#title' => t('8. Who is responsible for carrying out a formal annual review?'),
    '#help_text' => t('Provide name of individual responsible.'),
    '#help_link' => 32,
    '#default_value' => array_get($values, "principle_6.6_8", FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please state who is responsible for carrying out a formal annual review.'),
    ),
  );

  $form['principle_6']['6_9'] = array(
    '#type' => 'checkboxes',
    '#title' => t("9. Mark any of the following 'triggers' that will initiate a review in your organisation:"),
    '#options' => array(
      'advances' => t('Technological advances in production'),
      'controls' => t('New controls that become available'),
      'changes' => t('Change in raw material/ingredients/product formulation/packaging'),
      'changes_supplier' => t('Change of raw material supplier'),
      'changes_processing' => t('Change in processing system (e.g. changes in method of preservation – such as addition of preservatives, water activity changes, going from a sterilisation to a pasteurisation activity)'),
      'changes_layout' => t('Changes in layout and environment of the factory'),
      'modification' => t('Modification to process equipment (e.g. new equipment, modification of existing equipment)'),
      'changes_cleaning' => t('Changes in cleaning and disinfection programme (i.e. a change to any supporting prerequisite programme)'),
      'failuers' => t('Failures in the system, e.g. corrective actions or the need for product recall/withdrawal'),
      'changes_storage' => t('Changes in the storage and distribution systems'),
      'changes_staff' => t('Changes in staff levels and/or responsibilities'),
      'anticipated' => t('Anticipated change in use of product by customer/consumer'),
      'receipt' => t('Receipt of information from the market place indicating a health risk associated with the product'),
      'emergence' => t('Emergence of foodborne pathogens with public health significance'),
      'changes_legislation' => t('Changes in legislation'),
      'scientific' => t('New scientific/technical knowledge (e.g. new information on hazards and control measures)'),
      'unexpected' => t('Unexpected use of product by the consumer'),
      'changes_environmental' => t('Environmental changes/issues (i.e. local changes external to the food operation; climate changes)'),
    ),
    '#help_text' => t('If any of the items listed occur  your HACCP plan may not be valid and your product potentially unsafe.  In such a case it would be necessary to trigger a review.'),
    '#help_link' => 32,
    '#default_value' => array_get($values, "principle_6.6_9", array()),
  );

  $form['principle_6']['6_10'] = array(
    '#type' => 'textfield',
    '#title' => t("10. List any other mechanisms which are in place to automatically 'trigger' a review."),
    '#default_value' => array_get($values, "principle_6.6_10", FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('Please list any other mechanisms which are in place to automatically ‘trigger’ a review.'),
    ),
  );

  $form['principle_6']['6_11'] = array(
    '#type' => 'radios',
    '#title' => t('11. Are all records from reviews documented, brought to the attention of senior management (for companies where this is appropriate)  and used to keep the HACCP plan up-to-date?'),
    '#options' => array(
      'yes' => t('Yes', array(), array('context' => 'Are all records from reviews documented?')),
      'no' => t('No', array(), array('context' => 'Are all records from reviews documented?')),
    ),
    '#default_value' => array_get($values, "principle_6.6_11", FALSE),
    '#attributes' => array(
      'data-parsley-required' => 'true',
      'data-parsley-error-message' => t('Please specify if all records from reviews documented, brought to the attention of senior management (for companies where this is appropriate) and used to keep the HACCP plan up-to-date.'),
    ),
  );

  // Add the validation handler.
  $form['#validate'][] = 'principle_6_validate';

  return $form;
}

/**
 * Validation handler for Principle 2 Question 4.
 */
function principle_6_validate($form, &$form_state) {
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

  // Checks is an array with the key being the element being targeted (in dot
  // notation) and the value being the callback to use to check whether the
  // field is empty.
  $checks = array(
    'principle_6.6_1' => 'fieldIsNotEmpty',
    'principle_6.6_2' => 'fieldIsNotEmpty',
    'principle_6.6_3' => 'fieldIsNotEmpty',
    'principle_6.6_6' => 'fieldIsNotEmpty',
    'principle_6.6_7' => 'fieldIsNotEmpty',
    'principle_6.6_8' => 'fieldIsNotEmpty',
    'principle_6.6_11' => 'fieldIsNotEmpty',
  );

  foreach ($checks as $target => $method) {
    $validator->validate($method, $target);
  }

  // Now check if the radio button in 3 is set to yes.
  if (array_get($form_state['values'], "principle_6.6_3", FALSE) == 'no') {
    // Now check that the dependent fields 3a has something in it.
    $validator->validate('fieldIsNotEmpty', 'principle_6.6_3a');
  }

  $validator->setErrorMessages();
  $form_state = $validator->getFormState();
}
