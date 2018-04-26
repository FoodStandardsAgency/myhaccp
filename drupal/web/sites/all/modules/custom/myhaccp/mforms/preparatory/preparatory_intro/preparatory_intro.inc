<?php

/**
 * @file
 * Preparatory Intro stage form and validation handler.
 */

/**
 * Preparatory Intro.
 */
function preparatory_intro(&$form_state, &$next_step) {

  $default_content = '
<h2>Note to developers</h2>
<p>Default content for this page can be set by creating a Basic Page and setting 
  the node in the myhaccp module -> mforms/preparatory_intro/preparatory_intro.inc 
  file on line 31 or editing the $default_content variable on line 13.</p>
<p>The default content for the FSA site can be viewed here: 
  <a href="https://myhaccp.food.gov.uk/node/37">https://myhaccp.food.gov.uk/node/37</a></p>  ';

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_a';

  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  drupal_set_title($stage->title, PASS_THROUGH);

  // Get the node output.
  $node = node_load(37);
  if (!$node) {
    $node = new stdClass();
    $node->type = "page";
    $node->nid = 1000;
    $node->created = time();
    $node->language = 'en';
    $node->promote = 0;
    $node->sticky = 0;
    $node->status = 1;
    node_object_prepare($node);
    $node->body['en'][] = array(
      'value' => $default_content,
      'format' => 'full_html',
    );
  }
  $node->title = NULL;
  $node_output = node_view($node, 'full');

  // Retrieve submitted values. This comes in handy when back action
  // occurred and we need to display values that were originally submitted.
  $data = mforms_get_vals('myhaccp', 'preparatory_intro');

  // If we have the data it means we arrived here from back action, so show
  // them in form as default values.
  $values = myhaccp_prepare_values($data, $form_state);

  $form = array();

  $form['preparatory_intro'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#attributes' => array(
      'class' => array(
        'stage-fieldset',
      ),
    ),
  );

  $form['preparatory_intro']['study_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name of your study'),
    '#help_text' => t("The study name will be shown on your output document as well as on your studies overview page and is used to tell studies apart from each other. It can be the name of your product or anything else that makes sense to you."),
    '#default_value' => isset($_GET['new']) && $_GET['new'] == 'true' ? '' : array_get($values, 'preparatory_intro.study_name', FALSE),
    '#attributes' => array(
      'data-parsley-error-message' => t('Please name your study.'),
      'data-parsley-required' => TRUE,
      'autofocus' => TRUE,
    ),
  );

  $form['preparatory_intro']['node'] = array(
    '#markup' => drupal_render($node_output),
  );

  $form['#validate'][] = __FUNCTION__ . '_validate';

  return $form;
}

/**
 * Validation handler.
 */
function preparatory_intro_validate($form, &$form_state) {
  // Some oddity with the
  $form_state['values'] = array_merge($form_state['values'], $_POST);
  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  $validator = $stage->getValidator();
  $validator->setFormState($form_state);
  $validator->setForm($form);

  // Validation: Some content.
  $checks = array(
    'preparatory_intro.study_name' => 'fieldIsNotEmpty',
  );

  foreach ($checks as $target => $method) {
    $validator->validate($method, $target);
  }

  $validator->setErrorMessages();
  $form_state = $validator->getFormState();
}
