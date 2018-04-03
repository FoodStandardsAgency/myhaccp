<?php
/**
 * @file
 * myhaccp_pdf_download.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function myhaccp_pdf_download_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'myhaccp_pdf_link';
  $context->description = 'Adds the pdf links block to the help pages.';
  $context->tag = 'Block';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'help/*' => 'help/*',
        'cymorth/*' => 'cymorth/*',
        'node/92' => 'node/92',
        'node/6' => 'node/6',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'print_ui-print-links' => array(
          'module' => 'print_ui',
          'delta' => 'print-links',
          'region' => 'content',
          'weight' => '20',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Adds the pdf links block to the help pages.');
  t('Block');
  $export['myhaccp_pdf_link'] = $context;

  return $export;
}
