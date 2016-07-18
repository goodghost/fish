<?php

/**
 * @file fr-case.tpl.php
 * Default template implementation for cases.
 *
 * Available variables:
 * - $case: A raw case loaded directly form endpoint.
 * - $case_info: A renderable table of case information.
 * - $scenes: List of scenes associated with case.
 *
 * @see template_preprocess_case()
 */

?>

<div class="case-information">
  <h3><?php print t('Case information'); ?></h3>
  <?php print render($case_info); ?>
</div>

<div class="case-scenes">
  <h3><?php print t('Scenes'); ?></h3>
  <div class="inner">
    <?php foreach ($scenes as $scene): ?>
      <a class="case-scene" href="<?php print $scene['scene_url']; ?>">
        <div class="case-scene--name"><?php print $scene['name']; ?></div>
        <img class="case-scene--thumbnail" src="<?php print $scene['thumbnail_url']; ?>" alt="<?php print $scene['name']; ?>" />
      </a>
    <?php endforeach; ?>
  </div>
</div>
