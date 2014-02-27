<?php
/**
 * @file
 * Stage output template.
 */
?>

<section class="page">
  <h2>Management commitment</h2>
  <h3><?php print $b_1_title ?></h3>
  <?php print $b_1; ?>
  <?php if ($b_2) : ?>
    <h3><?php print $b_2_title ?></h3>
    <?php print $b_2; ?>
  <?php endif; ?>
</section>
<div class="page-break"></div>
