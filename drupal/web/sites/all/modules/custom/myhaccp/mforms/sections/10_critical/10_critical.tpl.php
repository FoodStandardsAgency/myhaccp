<?php
/**
 * @file
 * Stage output template.
 */
?>

<?php if ($ccps): ?>
<p class="intro"><?php print t('The following critical limits have been established for the CCPs.'); ?></p>
<?php endif; ?>
<?php if(!empty($p_3_table)): ?>
  <?php print $p_3_table; ?>
<?php endif; ?>
