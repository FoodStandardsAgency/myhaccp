<?php
/*
Nukes the js
*/
function cleanup_js_alter(&$js) {

  //cleanup removes classes all over so a tiny fix to contextual links is needed ... ups
  if(module_exists('contextual')){
    $contextual_path = drupal_get_path('module', 'contextual');
    if (isset($js[$contextual_path . '/contextual.js'])) {
      $js[$contextual_path . '/contextual.js']['data'] = drupal_get_path('theme', 'cleanup') . '/js/contextual.js';
    }
  }

  //js from core modules
  if (theme_get_setting('cleanup_js_nuke_module')){
    foreach ($js as $file => $value) {
      if (strpos($file, 'modules/') !== FALSE) {
        unset($js[$file]);
      }
    }
  }
  //js from contrib
  if (theme_get_setting('cleanup_js_nuke_module_contrib')){
    foreach ($js as $file => $value) {
      if (strpos($file, '/modules/') !== FALSE) {
        unset($js[$file]);
      }
    }
  }

  if (theme_get_setting('cleanup_js_nuke_misc')){
    foreach ($js as $file => $value) {
      if (strpos($file, 'misc/') !== FALSE) {
        unset($js[$file]);
      }
    }
  }


  //freeform css class killing :)
  $js_kill_list = explode("\n", theme_get_setting('cleanup_js_freeform'));

  //grap the css and run through em
  if(theme_get_setting('cleanup_js_freeform')){
    foreach ($js as $file => $value) {
      //grap the kill list and do that on each file
      foreach ($js_kill_list as $key => $jsfilemustdie) {
        if (strpos($file, $jsfilemustdie) !== FALSE) {
         unset($js[$file]);
        }
      }
    }
  }

  if(theme_get_setting('cleanup_js_jquery_latest')){
    if (isset($js['misc/jquery.js'])) {
      $js['misc/jquery.js']['data'] = drupal_get_path('theme', 'cleanup') . '/js/jquery-1.8.2.min.js';
      $js['misc/jquery.js']['weight'] = -100;
    }
  }


  //http://www.metaltoad.com/blog/mobile-drupal-optimization-results
  if(theme_get_setting('cleanup_js_jquerycdn')){
    $version = theme_get_setting('cleanup_js_jquerycdn_version');
    if (isset($js['misc/jquery.js'])) {
      $js['misc/jquery.js']['data'] ='http://ajax.googleapis.com/ajax/libs/jquery/' . $version . '/jquery.min.js';
      $js['misc/jquery.js']['type'] = 'external';
      $js['misc/jquery.js']['weight'] = -100;
    }
  }


  if(theme_get_setting('cleanup_js_onefile')){
    uasort($js, 'drupal_sort_css_js');
    $i = 0;
    foreach ($js as $name => $script) {
      $js[$name]['weight'] = $i++;
      $js[$name]['group'] = JS_DEFAULT;
      $js[$name]['every_page'] = FALSE;
    }
  }

}

