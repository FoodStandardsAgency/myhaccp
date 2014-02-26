<?php

function preparatory_intro(&$form_state, &$next_step) {

  // Define following step callback. If none set, that implies it is
  // the last step.
  $next_step = 'preparatory_a';

  // Set the page title.
  $stages = new Stages();
  $stage = $stages->getStage(__FUNCTION__);
  drupal_set_title($stage->title, PASS_THROUGH);

  // Get the node output.
  $node = node_load(35);
  $node_output = node_view($node);

  $form = array();

  $form['preparatory_intro'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $form['preparatory_intro']['node'] = array(
    '#markup' => drupal_render($node_output),
  );

  return $form;
}
