<?php
/**
 * @file
 * Stage output template.
 */
?>
<section class="page">
  <h1>Process flow and confirmation</h1>

  <?php if (!empty($g_1)): ?>
    <p class="intro"><?php print $g_1; ?></p>
  <?php endif; ?>

  <?php if(!empty($flow_diagram_file)) : ?>
    <?php print render($flow_diagram_file); ?>
  <?php endif; ?>

  <?php if (!empty($g_3)): ?>
    <h3>A copy of our flow diagram can be obtained from the following location:</h3>
    <?php print $g_3; ?>
  <?php endif; ?>
