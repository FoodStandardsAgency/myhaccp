<?php
/**
 * @file
 * Stage output template.
 */
?>

<section class="page prep-e">
  <h1>Product description and intended use</h1>

  <?php if ($e_1): ?>
    <h4>Ingredients</h4>
    <span class="description">Suppliers listed in brackets.</span>
    <p><?php print $e_1; ?></p>
  <?php endif; ?>

  <?php if ($e_2): ?>
    <h4><?php print $e_2_title; ?></h4>
    <p><?php print $e_2; ?></p>
  <?php endif; ?>

  <?php if ($e_3): ?>
    <h4><?php print $e_3_title; ?></h4>
    <p><?php print $e_3; ?></p>
  <?php endif; ?>

  <?php if ($e_4): ?>
    <h4><?php print $e_4_title; ?></h4>
    <p><?php print $e_4; ?></p>
  <?php endif; ?>

  <?php if ($e_5): ?>
    <h4><?php print $e_5_title; ?></h4>
    <p><?php print $e_5; ?></p>
  <?php endif; ?>

  <?php if ($e_6): ?>
    <h4><?php print $e_6_title; ?></h4>
    <p><?php print $e_6; ?></p>
  <?php endif; ?>

  <?php if ($e_7): ?>
    <h4><?php print $e_7_title; ?></h4>
    <p><?php print $e_7; ?></p>
  <?php endif; ?>
