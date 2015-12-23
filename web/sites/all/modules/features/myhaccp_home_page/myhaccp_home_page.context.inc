<?php
/**
 * @file
 * myhaccp_home_page.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function myhaccp_home_page_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'homepage_blocks';
  $context->description = 'Positions the home page blocks.';
  $context->tag = 'Layout';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'bean-homepage_intro' => array(
          'module' => 'bean',
          'delta' => 'homepage_intro',
          'region' => 'content',
          'weight' => '-10',
        ),
        'bean-homepage_first' => array(
          'module' => 'bean',
          'delta' => 'homepage_first',
          'region' => 'content',
          'weight' => '-9',
        ),
        'bean-homepage_second' => array(
          'module' => 'bean',
          'delta' => 'homepage_second',
          'region' => 'content',
          'weight' => '-8',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Layout');
  t('Positions the home page blocks.');
  $export['homepage_blocks'] = $context;

  return $export;
}
