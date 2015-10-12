<?php
/**
 * @file
 * myhaccp_context.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function myhaccp_context_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'block_alert_notice';
  $context->description = 'Displays the most recent published notice block';
  $context->tag = 'Block';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'tool' => 'tool',
      ),
    ),
    'theme' => array(
      'values' => array(
        'myhaccp_theme' => 'myhaccp_theme',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'myhaccp_notices-notice' => array(
          'module' => 'myhaccp_notices',
          'delta' => 'notice',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Block');
  t('Displays the most recent published notice block');
  $export['block_alert_notice'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'block_help_library';
  $context->description = 'Positions the help library block.';
  $context->tag = 'Block';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'help/guidance' => 'help/guidance',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu_block-4' => array(
          'module' => 'menu_block',
          'delta' => '4',
          'region' => 'content',
          'weight' => '-1',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Block');
  t('Positions the help library block.');
  $export['block_help_library'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'block_prep_stages';
  $context->description = 'Positions the Preparatory Stages menu for the help pages.';
  $context->tag = 'Block';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'help/guidance/preparatory-stages' => 'help/guidance/preparatory-stages',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu_block-5' => array(
          'module' => 'menu_block',
          'delta' => '5',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Block');
  t('Positions the Preparatory Stages menu for the help pages.');
  $export['block_prep_stages'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'block_principles_stages';
  $context->description = 'Positions the Principles Stages menu for the help pages.';
  $context->tag = 'Block';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'help/guidance/principles' => 'help/guidance/principles',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu_block-6' => array(
          'module' => 'menu_block',
          'delta' => '6',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Block');
  t('Positions the Principles Stages menu for the help pages.');
  $export['block_principles_stages'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'sitewide_blocks';
  $context->description = 'Positions blocks for the MyHACCP theme.';
  $context->tag = 'Layout';
  $context->conditions = array(
    'theme' => array(
      'values' => array(
        'myhaccp_theme' => 'myhaccp_theme',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'system-main' => array(
          'module' => 'system',
          'delta' => 'main',
          'region' => 'content',
          'weight' => '0',
        ),
        'search-form' => array(
          'module' => 'search',
          'delta' => 'form',
          'region' => 'header_utility',
          'weight' => '-10',
        ),
        'system-user-menu' => array(
          'module' => 'system',
          'delta' => 'user-menu',
          'region' => 'header_utility',
          'weight' => '-9',
        ),
        'menu_block-1' => array(
          'module' => 'menu_block',
          'delta' => '1',
          'region' => 'header',
          'weight' => '-10',
        ),
        'bean-footer_gov' => array(
          'module' => 'bean',
          'delta' => 'footer_gov',
          'region' => 'footer',
          'weight' => '-25',
        ),
        'menu_block-7' => array(
          'module' => 'menu_block',
          'delta' => '7',
          'region' => 'footer',
          'weight' => '-24',
        ),
        'menu_block-8' => array(
          'module' => 'menu_block',
          'delta' => '8',
          'region' => 'footer',
          'weight' => '-23',
        ),
        'masquerade-masquerade' => array(
          'module' => 'masquerade',
          'delta' => 'masquerade',
          'region' => 'footer',
          'weight' => '-22',
        ),
        'menu_block-2' => array(
          'module' => 'menu_block',
          'delta' => '2',
          'region' => 'content_pre',
          'weight' => '-10',
        ),
        'system-help' => array(
          'module' => 'system',
          'delta' => 'help',
          'region' => 'help',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Layout');
  t('Positions blocks for the MyHACCP theme.');
  $export['sitewide_blocks'] = $context;

  return $export;
}
