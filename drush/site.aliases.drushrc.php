<?php

if (!isset($drush_major_version)) {
  $drush_version_components = explode('.', DRUSH_VERSION);
  $drush_major_version = $drush_version_components[0];
}
// Site foodmyhaccp, environment dev.
$aliases['dev'] = array(
  'root' => '/var/www/html/foodmyhaccp.dev/docroot',
  'ac-site' => 'foodmyhaccp',
  'ac-env' => 'dev',
  'ac-realm' => 'prod',
  'uri' => 'foodmyhaccpdev.prod.acquia-sites.com',
  'remote-host' => 'foodmyhaccpdev.ssh.prod.acquia-sites.com',
  'remote-user' => 'foodmyhaccp.dev',
  'path-aliases' => array(
    '%drush-script' => 'drush' . $drush_major_version,
  ),
);
$aliases['dev.livedev'] = array(
  'parent' => '@foodmyhaccp.dev',
  'root' => '/mnt/gfs/foodmyhaccp.dev/livedev/docroot',
);

if (!isset($drush_major_version)) {
  $drush_version_components = explode('.', DRUSH_VERSION);
  $drush_major_version = $drush_version_components[0];
}
// Site foodmyhaccp, environment prod.
$aliases['prod'] = array(
  'root' => '/var/www/html/foodmyhaccp.prod/docroot',
  'ac-site' => 'foodmyhaccp',
  'ac-env' => 'prod',
  'ac-realm' => 'prod',
  'uri' => 'foodmyhaccp.prod.acquia-sites.com',
  'remote-host' => 'foodmyhaccp.ssh.prod.acquia-sites.com',
  'remote-user' => 'foodmyhaccp.prod',
  'path-aliases' => array(
    '%drush-script' => 'drush' . $drush_major_version,
  ),
);
$aliases['prod.livedev'] = array(
  'parent' => '@foodmyhaccp.prod',
  'root' => '/mnt/gfs/foodmyhaccp.prod/livedev/docroot',
);

if (!isset($drush_major_version)) {
  $drush_version_components = explode('.', DRUSH_VERSION);
  $drush_major_version = $drush_version_components[0];
}
// Site foodmyhaccp, environment ra.
$aliases['ra'] = array(
  'root' => '/var/www/html/foodmyhaccp.ra/docroot',
  'ac-site' => 'foodmyhaccp',
  'ac-env' => 'ra',
  'ac-realm' => 'prod',
  'uri' => 'foodmyhaccpra.prod.acquia-sites.com',
  'remote-host' => 'foodmyhaccpra.ssh.prod.acquia-sites.com',
  'remote-user' => 'foodmyhaccp.ra',
  'path-aliases' => array(
    '%drush-script' => 'drush' . $drush_major_version,
  ),
);
$aliases['ra.livedev'] = array(
  'parent' => '@foodmyhaccp.ra',
  'root' => '/mnt/gfs/foodmyhaccp.ra/livedev/docroot',
);

if (!isset($drush_major_version)) {
  $drush_version_components = explode('.', DRUSH_VERSION);
  $drush_major_version = $drush_version_components[0];
}
// Site foodmyhaccp, environment test.
$aliases['test'] = array(
  'root' => '/var/www/html/foodmyhaccp.test/docroot',
  'ac-site' => 'foodmyhaccp',
  'ac-env' => 'test',
  'ac-realm' => 'prod',
  'uri' => 'foodmyhaccpstg.prod.acquia-sites.com',
  'remote-host' => 'foodmyhaccpstg.ssh.prod.acquia-sites.com',
  'remote-user' => 'foodmyhaccp.test',
  'path-aliases' => array(
    '%drush-script' => 'drush' . $drush_major_version,
  ),
);
$aliases['test.livedev'] = array(
  'parent' => '@foodmyhaccp.test',
  'root' => '/mnt/gfs/foodmyhaccp.test/livedev/docroot',
);
