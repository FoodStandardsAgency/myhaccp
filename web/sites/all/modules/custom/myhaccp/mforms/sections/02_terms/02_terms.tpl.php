<?php
/**
 * @file
 * Stage output template.
 *
 * Note: continues from previous c_1 so no title needed and no opening section tag.
 */
?>
<?php if (!empty($c_intro)) : ?>
  <?php print $c_intro ?>
<?php endif; ?>
<h3><?php print $c_4_title ?></h3>
<?php print $c_4; ?>

<h3><?php print $a_1_title ?></h3>
<?php print $a_1; ?>
<h3><?php print $a_2_title ?></h3>
<p><?php print $a_2; ?></p>

<?php if ($c_5): ?>
<?php print $c_5; ?>
<?php endif; ?>
