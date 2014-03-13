<?php
/**
 * @file
 * Stage output template.
 */
?>
<?php if(!empty($p_1_2_hazard_table)): ?>
  <?php print $p_1_2_hazard_table ?>
<?php endif; ?>

<?php if(!empty($p_1_2_threshold)) : ?>
  <p><?php print $p_1_2_threshold ?></p>
<?php endif; ?>
