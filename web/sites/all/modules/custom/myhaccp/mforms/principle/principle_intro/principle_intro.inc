<?php

function principle_intro(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'principle_a';

  // Get the dependency injection container.
  global $container;
  // Get the current study.
  $study = $container['study'];
  // Get the stage.
  $stage = $study->getCurrentStage();
  drupal_set_title($stage->title, PASS_THROUGH);

  // Get the node output.
  $node = node_load(38);
  $node->title = NULL;
  $node_output = node_view($node, 'full');

  $form = array();

  $form['principle_intro']['node'] = array(
    '#markup' => drupal_render($node_output),
  );

  return $form;
}
