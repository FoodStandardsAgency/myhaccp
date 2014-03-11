<?php
/**
 * @file
 * Stage output template.
 */
?>

<section>
  <h1>Critical limits for the CCPs</h1>
  <p class="intro">The following critical limits have been established for the CCPs.</p>
  <?php if(!empty($p_3_table)): ?>
    <?php print $p_3_table; ?>
  <?php endif; ?>

</section>
