<?php
//kpr(get_defined_vars());
//kpr($theme_hook_suggestions);
//template naming
//page--[CONTENT TYPE].tpl.php
?>
<?php if( theme_get_setting('cleanup_poorthemers_helper') ){ ?>
<!-- page.tpl.php-->
<?php } ?>

<?php print $cleanup_poorthemers_helper; ?>

<header role="banner">
  <div class="header-wrapper">
    <div class="header-inside">

      <?php if($page['header_utility']): ?>
        <div class="header-utility">
          <?php print render($page['header_utility']); ?>
        </div>
      <?php endif; ?>

      <div class="site-details">
        <?php if ($logo): ?>
          <div class="logo">
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
            <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
          </a>
          </div>
        <?php endif; ?>

        <?php if($site_name): ?>
          <h1><?php print $site_name; ?></h1>
        <?php endif; ?>
        <?php if ($site_slogan): ?>
          <h2><?php print $site_slogan; ?></h2>
        <?php endif; ?>

      </div>

      <?php if($page['header']): ?>
        <div class="header-region">
          <?php print render($page['header']); ?>
        </div>
      <?php endif; ?>

    </div>
  </div>
</header>

<div class="page">

  <div class="main-wrapper">

    <?php if($page['content_pre']): ?>
      <div class="pre-content">
        <?php print render($page['content_pre']); ?>
      </div>
    <?php endif; ?>

    <div role="main" id="main-content">
      <?php print render($title_prefix); ?>
      <?php if ($title): ?>
        <h1><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>

      <?php if (isset($tabs['#primary'][0]) || isset($tabs['#secondary'][0])): ?>
        <nav class="tabs"><?php print render($tabs); ?></nav>
      <?php endif; ?>

      <?php if($page['highlighted'] OR $messages){ ?>
        <div class="drupal-messages">
        <?php print render($page['highlighted']); ?>
        <?php print $messages; ?>
        </div>
      <?php } ?>

      <?php print render($page['content']); ?>

      <?php print render($page['content_post']); ?>

    </div><!-- /main-->

    <?php if ($page['sidebar_first']): ?>
      <div class="region-sidebar-first">
      <?php print render($page['sidebar_first']); ?>
      </div>
    <?php endif; ?>

    <?php if ($page['sidebar_second']): ?>
      <div class="region-sidebar-second">
        <?php print render($page['sidebar_second']); ?>
      </div>
    <?php endif; ?>
  </div>
</div><!-- /page-->

<footer role="contentinfo">
  <div class="footer-wrapper">
    <div class="footer-inside">
      <?php print render($page['footer']); ?>
    </div>
  </div>
</footer>

