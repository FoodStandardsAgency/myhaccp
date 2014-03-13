<?php
/**
 * @file
 * Stage output template.
 */
?>

<p class="intro">The following critical limits have been established for the CCPs.</p>
<?php if(!empty($p_3_table)): ?>
  <?php print $p_3_table; ?>
<?php endif; ?>
