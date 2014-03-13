<?php
/**
 * @file
 * Stage output template.
 */
?>
<?php if (!empty($g_1)): ?>
  <p class="intro"><?php print $g_1; ?></p>
<?php endif; ?>

<?php if(!empty($flow_diagram_file)) : ?>
  <?php //print render($flow_diagram_file); ?>
<?php endif; ?>

<?php if(!empty($flow_diagram_data)) : ?>
  <div class="flow-diagram-container">
    <img src="data:image/gif;base64,<?php print $flow_diagram_data; ?>" />
  </div>
<?php endif; ?>

<?php if (!empty($g_3)): ?>
  <h3>A copy of our flow diagram can be obtained from the following location:</h3>
  <?php print $g_3; ?>
<?php endif; ?>

<h2>On-site confirmation of flow diagram</h2>

<?php if (!empty($h_1)) : ?>
  <p><?php print $h_1; ?></p>
<?php endif; ?>

<?php if (!empty($h_2)) : ?>
  <p><?php print $h_2; ?></p>
<?php endif; ?>

<?php if (!empty($h_3)) : ?>
  <p><?php print $h_3; ?></p>
<?php endif; ?>

<?php if (!empty($h_4)) : ?>
  <p><?php print $h_4; ?></p>
<?php endif; ?>

<?php if (!empty($h_5)) : ?>
  <p><?php print $h_5; ?></p>
<?php endif; ?>

<?php if (!empty($h_6)) : ?>
  <p><?php print $h_6; ?></p>
<?php endif; ?>

<?php if (!empty($h_7)) : ?>
  <?php print $h_7; ?>
<?php endif; ?>
