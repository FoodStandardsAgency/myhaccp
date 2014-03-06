<?php
/**
 * @file
 * Stage output template.
 */
?>
<div class="page-break"></div>
<section class="page">
  <h1>Severity scores</h1>

  <?php if(!empty($p_1_2_hazard_table)): ?>
    <?php print $p_1_2_hazard_table ?>
  <?php endif; ?>

  <?php if(!empty($p_1_2_threshold)) : ?>
    <p><?php print $p_1_2_threshold ?></p>
  <?php endif; ?>

</section>

