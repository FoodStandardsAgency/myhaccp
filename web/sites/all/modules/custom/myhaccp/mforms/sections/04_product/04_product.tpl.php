<?php
/**
 * @file
 * Stage output template.
 */
?>

<?php if(!empty($e_1)): ?>
  <h4>Ingredients</h4>
  <span class="description">Suppliers listed in brackets.</span>
  <p><?php print $e_1; ?></p>
<?php endif; ?>

<?php if(!empty($e_2)): ?>
  <h4><?php print $e_2_title; ?></h4>
  <p><?php print $e_2; ?></p>
<?php endif; ?>

<?php if(!empty($e_3)): ?>
  <h4><?php print $e_3_title; ?></h4>
  <p><?php print $e_3; ?></p>
<?php endif; ?>

<?php if(!empty($e_4)): ?>
  <h4><?php print $e_4_title; ?></h4>
  <p><?php print $e_4; ?></p>
<?php endif; ?>

<?php if(!empty($e_5)): ?>
  <h4><?php print $e_5_title; ?></h4>
  <p><?php print $e_5; ?></p>
<?php endif; ?>

<?php if(!empty($e_6)): ?>
  <h4><?php print $e_6_title; ?></h4>
  <p><?php print $e_6; ?></p>
<?php endif; ?>

<?php if(!empty($e_7)): ?>
  <h4><?php print $e_7_title; ?></h4>
  <p><?php print $e_7; ?></p>
<?php endif; ?>

  <h2>Intended Use</h2>

<?php if (!empty($f_1)) : ?>
  <p><strong>Name of the product:</strong> <?php print $f_1; ?></p>
<?php endif; ?>

<?php if (!empty($f_2)): ?>
  <p><?php print $f_2; ?></p>
<?php endif; ?>

<?php if (!empty($f_3)): ?>
  <p><?php print $f_3; ?></p>
<?php endif; ?>

<?php if (!empty($f_4)): ?>
  <p><?php print $f_4; ?></p>
<?php endif; ?>

<?php if (!empty($f_5)): ?>
  <p><?php print $f_5; ?></p>
<?php endif; ?>

<?php if (!empty($f_6)): ?>
  <p><?php print $f_6; ?></p>
<?php endif; ?>

<?php if (!empty($f_7)): ?>
  <p><?php print $f_7; ?></p>
<?php endif; ?>

<?php if (!empty($f_8)): ?>
  <h4><?php print $f_8_title; ?></h4>
  <p><?php print $f_8; ?></p>
<?php endif; ?>
