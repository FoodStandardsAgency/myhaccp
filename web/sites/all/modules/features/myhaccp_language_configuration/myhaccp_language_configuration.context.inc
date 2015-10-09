<?php
/**
 * @file
 * myhaccp_language_configuration.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function myhaccp_language_configuration_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'myhaccp_language_blocks';
  $context->description = 'Positions language blocks.';
  $context->tag = 'Block';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'locale-language' => array(
          'module' => 'locale',
          'delta' => 'language',
          'region' => 'header_utility',
          'weight' => '20',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Block');
  t('Positions language blocks.');
  $export['myhaccp_language_blocks'] = $context;

  return $export;
}
