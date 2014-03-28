<!DOCTYPE html>
  <!--[if lte IE 6]><html class="no-js ie6 oldie" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"><![endif]-->
  <!--[if IE 7]><html class="no-js ie7 oldie" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"><![endif]-->
  <!--[if IE 8]><html class="no-js ie8 oldie" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"><![endif]-->
  <!--[if (gte IE 9)|(gt IEMobile 7)]>
  <html class="no-js ie" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces; ?>><![endif]-->
  <!--[if !IE]><!--><html class="no-js" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces; ?>><!--<![endif]-->
<?php print $cleanup_poorthemers_helper; ?>
<head>
<title><?php print $head_title; ?></title>
<?php print $head; ?>
<?php print $appletouchicon; ?>
<?php if(theme_get_setting('cleanup_mobile')){  ?>
<meta name="MobileOptimized" content="width">
<meta name="HandheldFriendly" content="true"><?php } ?>
<?php if(theme_get_setting('cleanup_viewport')){  ?><meta name="viewport" content="width=device-width, initial-scale=1"><?php } ?>
<?php if(theme_get_setting('cleanup_viewport_maximumscale')){  ?><meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1.0"><?php } ?>
<?php print $styles; ?>
<?php if(theme_get_setting('cleanup_respondjs')) { ?>
<!--[if lt IE 9]>
  <script src="<?php print $cleanup_path; ?>/js/respond.min.js"></script>
<![endif]-->
<?php } ?>
<!--[if lt IE 9]>
  <script src="<?php print $cleanup_path; ?>/js/html5.js"></script>
<![endif]-->
<?php print $selectivizr; ?>
<?php
  if(!theme_get_setting('cleanup_script_place_footer')) {
    print $scripts;
  }
?>
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
<a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
<?php print $page_top; //stuff from modules always render first ?>
<?php print $page; // uses the page.tpl ?>
<?php
  if(theme_get_setting('cleanup_script_place_footer')) {
    print $scripts;
  }
?>
<?php print $page_bottom; //stuff from modules always render last ?>
</body>
</html>

