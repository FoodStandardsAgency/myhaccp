<?php

/**
 * @file
 * Principle intro stage.
 */

/**
 * Principle intro.
 */
function principle_intro(&$form_state, &$next_step) {

  $default_content = '
<h2>Note to developers</h2>
<p>Default content for this page can be set by creating a Basic Page and setting 
  the node in the myhaccp module -> mforms/principle_intro/principle_intro.inc 
  file on line 34 or editing the $default_content variable on line 13.</p>
<p>The default content for the FSA site can be viewed here: 
  <a href="https://myhaccp.food.gov.uk/node/38">https://myhaccp.food.gov.uk/node/38</a></p>  ';
  
  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_a';

  // Get the dependency injection container.
  global $_myhaccp_container;
  // Get the current study.
  $study = $_myhaccp_container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  drupal_set_title($stage->title, PASS_THROUGH);

  // Get the node output.
  $node = node_load(38);
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

  $form = array();

  $form['principle_intro']['node'] = array(
    '#markup' => drupal_render($node_output),
  );

  return $form;
}
