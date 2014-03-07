<?php
/**
 * @file
 * Stage output template.
 */
?>
<section class="page">
  <h1>Documentation and record keeping</h1>

  <?php if(!empty($p_7_1)) : ?>
    <?php print $p_7_1; ?>
  <?php endif; ?>

  <?php if(!empty($p_7_2)) : ?>
    <h3><?php print $p_7_2_title; ?></h3>
    <?php print $p_7_2; ?>
  <?php endif; ?>

  <?php if(!empty($p_7_3)) : ?>
    <h3><?php print $p_7_3_title; ?></h3>
    <p><?php print $p_7_3; ?></p>
  <?php endif; ?>

  <?php if(!empty($p_7_4)) : ?>
    <p><?php print $p_7_4; ?></p>
  <?php endif; ?>

  <?php if(!empty($p_7_5)) : ?>
    <p><?php print $p_7_5; ?></p>
  <?php endif; ?>

</section>
