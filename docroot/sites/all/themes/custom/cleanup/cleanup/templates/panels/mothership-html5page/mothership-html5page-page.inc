<?php

// Plugin definition
$plugin = array(
  'title' => t('HTML5 base'),
  'category' => t('cleanup'),
  'icon' =>  'cleanup-html5page.png',
  'theme' => 'cleanup-html5page',
  'css' =>   'cleanup-html5page.admin.css',
  'regions' => array(
    'top' => t('Top (<header>)'),
    'top_mobile' => t('Top - Mobile (<header>)'),
    'middle' => t('Middle (role="main")'),
    'bottom' => t('Bottom (<footer>)'),
  ),
);
