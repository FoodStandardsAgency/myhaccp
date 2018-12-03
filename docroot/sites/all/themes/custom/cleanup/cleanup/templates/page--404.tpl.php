<?php
//kpr(get_defined_vars());
//kpr($theme_hook_suggestions);
//template naming
//page--[CONTENT TYPE].tpl.php
?>
<?php if( theme_get_setting('cleanup_poorthemers_helper') ){ ?>
<!--node.tpl.php-->
<?php } ?>

<?php print $cleanup_poorthemers_helper; ?>

<header role="banner">
  <div class="header-wrapper">
    <div class="header-inside">

      <?php if ($page['header_utility']): ?>
        <div class="header-utility">
          <?php print render($page['header_utility']); ?>
        </div>
      <?php endif; ?>

      <div class="site-details">
        <?php if ($logo): ?>
          <div class="logo">
            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
              <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>"/>
            </a>
          </div>
        <?php endif; ?>

        <?php if ($site_name): ?>
          <h1><?php print $site_name; ?></h1>
        <?php endif; ?>
        <?php if ($site_slogan): ?>
          <h2><?php print $site_slogan; ?></h2>
        <?php endif; ?>

      </div>

      <?php if ($page['header']): ?>
        <div class="header-region">
          <?php print render($page['header']); ?>
        </div>
      <?php endif; ?>

    </div>
  </div>
</header>

<div class="page">

  <div class="main-wrapper">

  <article>


   <h1>Not Found</h1>

    <p>Sorry, but the page you were trying to view does not exist.</p>
    <p>It looks like this was the result of either:</p>
    <ul>
      <li>a mistyped address</li>
      <li>an out-of-date link</li>
    </ul>

    You can try finding the content through an <a href="/search/">internal search</a> of this site, or return to the <a href="/">home page</a>.

    <script>
      var GOOG_FIXURL_LANG = (navigator.language || '').slice(0,2),GOOG_FIXURL_SITE = location.host;
    </script>
    <script src="http://linkhelp.clients.google.com/tbproxy/lh/wm/fixurl.js"></script>

  </article>

  </div>
</div>

<footer role="contentinfo">
  <div class="footer-wrapper">
    <div class="footer-inside">
      <?php print render($page['footer']); ?>
    </div>
  </div>
</footer>


