<?php
/**
 * @file
 * Stage output template.
 */
?>

<section class="page">
  <h1>The HACCP team</h1>

  <?php if(!empty($d_1_team)) : ?>
    <?php print $d_1_team ?>
  <?php endif; ?>

  <?php if(!empty($d_1_team_skills)) : ?>
    <?php print $d_1_team_skills ?>
  <?php endif;  ?>

</section>
