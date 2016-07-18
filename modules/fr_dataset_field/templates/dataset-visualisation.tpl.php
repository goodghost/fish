<?php

/**
 * @file dataset.tpl.php
 * Default template implementation to visualise datasets.
 *
 * Available variables:
 * - $item: An array of item properties.
 *
 * @see template_preprocess_dataset()
 *
 * @ingroup themeable
 */
?>

<div class="dataset-visualisation-wrapper dataset-visualisation-type-<?php print $display_type; ?> <?php print $classes; ?>">
  <div <?php print $attributes; ?> data-chart="<?php print $data; ?>" class="dataset-visualisation-object" id="<?php print $container_id; ?>">
    <?php if ($is_empty): ?>
      <?php print t('No results for given query.'); ?>
    <?php else: ?>
      <div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>
      <?php print t('Please wait...'); ?>
    <?php endif; ?>
  </div>
</div>
