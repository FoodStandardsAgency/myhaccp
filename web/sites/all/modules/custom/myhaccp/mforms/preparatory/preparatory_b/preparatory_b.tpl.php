<?php
/**
 * @file
 * Stage output template.
 */
?>

<section class="page">
  <h1>Management commitment</h1>
  <h3><?php print $b_1_title ?></h3>
  <?php print $b_1; ?>
  <?php if ($b_2) : ?>
    <h3><?php print $b_2_title ?></h3>
    <?php print $b_2; ?>
  <?php endif; ?>
</section>
