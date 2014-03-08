<?php
/**
 * @file
 * Stage output template.
 */
?>
<section class="page haccp-plan">
  <h1>HACCP plan</h1>
  <?php if(!empty($p_5_table)): ?>
    <?php print $p_5_table; ?>
  <?php endif; ?>
</section>
