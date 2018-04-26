<?php
// This file is for common configurations across ALL environments

switch (getenv("WKV_SITE_ENV")) {
case "prod":
    ini_set('error_reporting', !E_NOTICE & !E_WARNING);
    $conf['simple_environment_indicator'] = '#d4000f Prod';
    $conf['reverse_proxy_addresses'] = array('127.0.0.1');
    $conf['varnish_control_terminal'] = '127.0.0.1:6082';
    $conf['varnish_version'] = "4";

    # Warden settings.
    # Shared secret between the site and Warden server.
    $conf['warden_token'] = 'aCsTnss8YMAPzU6COnaYKFcr7BTiir';
    # Location of your Warden server. No trailing slash.
    $conf['warden_server_host_path'] = 'https://warden.wunder.io';
    # Allow external callbacks to the site. When set to false pressing refresh site data in
    # Warden will not work
    $conf['warden_allow_requests'] = true;
    # Basic HTTP authorization credentials.
    $conf['warden_http_username'] = 'warden';
    $conf['warden_http_password'] = 'wunder';
    # IP address of the Warden server. Only these IP addresses will be allowed to make callback # requests
    $conf['warden_public_allow_ips'] = '83.136.254.41,2a04:3541:1000:0500:d456:61ff:fee3:7d8d';
    $base_domain = "https://myhaccp.fsa.prod.wunder.io";


    break;

case "local":
    #  Folder so far not used for any filetypes (but future might be different)
    $conf['simple_environment_indicator'] = '#88b700 Local';

    $conf['stage_file_proxy_origin'] = 'https://myhaccp.fsa.prod.wunder.io';
    $conf['stage_file_proxy_hotlink'] = true;

    $conf['preprocess_css'] = '0';
    $conf['preprocess_js'] = '0';
    $cookie_domain = '.local.';
    $conf['reverse_proxy_addresses'] = array('127.0.0.1');
    $conf['varnish_control_terminal'] = '127.0.0.1:6082';
    $base_domain = "https://local.myhaccp.com";
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
ini_set('mysql.connect_timeout', 7200);
ini_set('default_socket_timeout', 7200);
ini_set('memory_limit', '512M');


if (php_sapi_name() == 'cli') {
    # Big memory limits for migration/imports etc. Max exec time will be unlimited automatically.
    ini_set('memory_limit', '2G');

    # The base_url may be modified by domain, but we need some base_url for drush purges,
    # that otherwise suppose the hostname is "default". Varnish purges with that assumption will fail.
    # Only for drush. Domain-module may want to alter this per subdomain.
    $base_url = $base_domain;
} else {
    # Admin-pages occasionally have very heavy actions. Upping time limit for admin pages to 5 minutes.
    # Other page views (except cli) are limited to 45 seconds.
    if (arg(0) == 'admin') {
        ini_set('max_execution_time', 300); //300 seconds = 5 minutes
        ini_set('memory_limit', '1G');
    }
}

# Session lengt
ini_set('session.gc_probability', 1);
ini_set('session.gc_divisor', 100);
ini_set('session.gc_maxlifetime', 259200); // 3 days
ini_set('session.cookie_lifetime', 259200); // 3 days

$databases = array (
  'default' =>
  array (
    'default' =>
    array (
      'database' => getenv('DB_NAME_DRUPAL'),
      'username' => getenv('DB_USER_DRUPAL'),
      'password' => getenv('DB_PASS_DRUPAL'),
      'host'     => getenv('DB_HOST_DRUPAL'),
      'port'     => '',
      'driver'   => 'mysql',
      'prefix'   => '',
    ),
  ),
);

if (drupal_is_cli() && extension_loaded('newrelic')) {
    newrelic_ignore_transaction();
}

/* We will use /drupal/vagrant/tmp for temporary folders,
    and /drupal/vagrant/private for private files (if we need any in future).

    The folders need to be created manually:
      sudo mkdir /vagrant/drupal/tmp; sudo chmod -R a+rw /vagrant/drupal/tmp
      sudo mkdir /vagrant/drupal/private; sudo chmod -R a+rw /vagrant/drupal/private
*/
# Shared /tmp-folder. Best to use a Drupal specific folder.
$conf['file_temporary_path'] = "/tmp";

# Folder so far not used for any filetypes (but future might be different)

if (!empty($_SERVER['SERVER_ADDR'])) {
    // This should return last section of IP, such as "198". (dont want/need to expose more info).
    //drupal_add_http_header('X-Webserver', end(explode('.', $_SERVER['SERVER_ADDR'])));
    $pcs = explode('.', $_SERVER['SERVER_ADDR']);
    header('X-Webserver: '. end($pcs));
}
