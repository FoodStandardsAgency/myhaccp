<?php
// This file is for common configurations across ALL environments

if (file_exists('/var/www/site-php')) {
  require('/var/www/site-php/foodmyhaccp/foodmyhaccp-settings.inc');
}

// Default Memcache.
$conf['cache_backends'][] = DRUPAL_ROOT . 'sites/all/modules/contrib/memcache/memcache.inc';
$conf['cache_default_class'] = 'MemCacheDrupal';
// The 'cache_form' bin must be assigned no non-volatile storage.
$conf['cache_class_cache_form'] = 'DrupalDatabaseCache';
$conf['memcache_key_prefix'] = 'myhaccp';
$conf['memcache_bins'] = array(
  'cache' => 'default',
  'cache_filter' => 'default',
  'cache_menu' => 'default'
);
# Move semaphore out of the database and into memory for performance purposes
$conf['lock_inc'] = DRUPAL_ROOT . 'sites/all/modules/contrib/memcache/memcache-lock.inc';
$conf['memcache_stampede_protection'] = TRUE;
$conf['memcache_pagecache_header'] = TRUE;

// Acquia config.
if (isset($_ENV['AH_SITE_ENVIRONMENT'])) {
  $env = $_ENV['AH_SITE_ENVIRONMENT'];

  $files_private_conf_path = conf_path();
  $conf['file_private_path'] = '/mnt/files/' . $_ENV['AH_SITE_GROUP'] . '.' . $_ENV['AH_SITE_ENVIRONMENT'] . '/' . $files_private_conf_path . '/files-private';

  $conf['print_pdf_autoconfig'] = 0;

  if (isset($conf['memcache_servers'])) {
    $conf['memcache_stampede_protection_ignore'] = array(
      // Ignore some cids in 'cache_bootstrap'.
      'cache_bootstrap' => array(
        'module_implements',
        'variables',
        'lookup_cache',
        'schema:runtime:*',
        'theme_registry:runtime:*',
        '_drupal_file_scan_cache',
      ),
      // Ignore all cids in the 'cache' bin starting with 'i18n:string:'
      'cache' => array(
        'i18n:string:*',
      ),
      // Disable stampede protection for the entire 'cache_path' and 'cache_rules'
      // bins.
      'cache_path',
      'cache_rules',
    );
  }
}
else {
// WKV_ENV_SITE is a legacy environment indicator.
  $env = getenv('WKV_SITE_ENV');
}

switch ($env) {
  case "prod":
    $conf['simple_environment_indicator'] = '#d4000f Prod';
    $conf['reverse_proxy_addresses'] = array('127.0.0.1');
    $conf['varnish_control_terminal'] = '127.0.0.1:6082';
    $conf['varnish_version'] = "4";

    $base_domain = "https://myhaccp.fsa.prod.wunder.io";

    break;

  case "local":
    #  Folder so far not used for any filetypes (but future might be different)
    $conf['simple_environment_indicator'] = '#88b700 Local';
    $conf['stage_file_proxy_origin'] = 'https://myhaccp.food.gov.uk';

    $conf['preprocess_css'] = '0';
    $conf['preprocess_js'] = '0';
    // $cookie_domain = '.ddev.local.';
    $conf['reverse_proxy_addresses'] = array('127.0.0.1');
    $conf['varnish_control_terminal'] = '127.0.0.1:6082';
    // $base_domain = "https://myhaccp.ddev.local";

    $conf['file_private_path'] = "/var/www/html/docroot/sites/default/files/private";

    $conf['memcache_servers'] = array(
      'memcached:11211' => 'default',
    );
    break;
}

// Varnish
$conf['cache_backends'][] = 'sites/all/modules/contrib/varnish/varnish.cache.inc';
$conf['cache_class_cache_page'] = 'VarnishCache';
$conf['cache_class_cache_form'] = 'DrupalDatabaseCache';
$conf['page_cache_invoke_hooks'] = false;

// Varnish reverse proxy on localhost
$conf['reverse_proxy'] = true;

// Varnish reverse proxy on localhost
$conf['varnish_version'] = "4";
$conf['varnish_control_key'] = getenv('VARNISH_CONTROL_KEY');
# PHP-cli has extremely high limits/timeouts for large cron imports, migration etc.
// ini_set('mysql.connect_timeout', 7200);
// ini_set('default_socket_timeout', 7200);
// ini_set('memory_limit', '512M');


if (php_sapi_name() == 'cli') {
  # Big memory limits for migration/imports etc. Max exec time will be unlimited automatically.
  // ini_set('memory_limit', '2G');

  # The base_url may be modified by domain, but we need some base_url for drush purges,
  # that otherwise suppose the hostname is "default". Varnish purges with that assumption will fail.
  # Only for drush. Domain-module may want to alter this per subdomain.
  $base_url = $base_domain;
}
else {
  # Admin-pages occasionally have very heavy actions. Upping time limit for admin pages to 5 minutes.
  # Other page views (except cli) are limited to 45 seconds.
  // if (arg(0) == 'admin') {
  //     ini_set('max_execution_time', 300); //300 seconds = 5 minutes
  //     ini_set('memory_limit', '1G');
  // }
}

# Session lengt
ini_set('session.gc_probability', 1);
ini_set('session.gc_divisor', 100);
ini_set('session.gc_maxlifetime', 259200); // 3 days
ini_set('session.cookie_lifetime', 259200); // 3 days

// if (drupal_is_cli() && extension_loaded('newrelic')) {
//     newrelic_ignore_transaction();
// }

/* We will use /drupal/vagrant/tmp for temporary folders,
    and /drupal/vagrant/private for private files (if we need any in future).

    The folders need to be created manually:
      sudo mkdir /vagrant/drupal/tmp; sudo chmod -R a+rw /vagrant/drupal/tmp
      sudo mkdir /vagrant/drupal/private; sudo chmod -R a+rw /vagrant/drupal/private
*/
# Shared /tmp-folder. Best to use a Drupal specific folder.
// $conf['file_temporary_path'] = "/tmp";

# Folder so far not used for any filetypes (but future might be different)

// if (!empty($_SERVER['SERVER_ADDR'])) {
//     // This should return last section of IP, such as "198". (dont want/need to expose more info).
//     //drupal_add_http_header('X-Webserver', end(explode('.', $_SERVER['SERVER_ADDR'])));
//     $pcs = explode('.', $_SERVER['SERVER_ADDR']);
//     header('X-Webserver: '. end($pcs));
// }

// Automatically generated include for settings managed by ddev.
$ddev_settings = dirname(__FILE__) . '/settings.ddev.php';
if (is_readable($ddev_settings)) {
  require $ddev_settings;
}
