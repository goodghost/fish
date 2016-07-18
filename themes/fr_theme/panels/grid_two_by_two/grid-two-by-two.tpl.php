<?php
/**
 * @file
 * Template for a 2x2 column panel layout.
 *
 * This template provides a two by two column panel display layout.
 *
 * Variables:
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top-left']: Content in the top left column.
 *   - $content['top-right']: Content in the top right column.
 *   - $content['bottom-left']: Content in the bottom left column.
 *   - $content['bottom-right']: Content in the bottom right column.
 */
?>
<div class="panel-dashboard panel-display panel-two-by-two clearfix" id="panel-dashboard">
  <div class="first-row clearfix">
    <div class="panel-panel panel-top-left col-lg-6 col-sm-12">
      <div class="inside"><?php print $content['top-left']; ?></div>
    </div>

    <div class="panel-panel panel-top-right col-lg-6 col-sm-12">
      <div class="inside"><?php print $content['top-right']; ?></div>
    </div>
  </div>

  <div class="second-row clearfix">
    <div class="panel-panel panel-bottom-left col-lg-6 col-sm-12">
      <div class="inside"><?php print $content['bottom-left']; ?></div>
    </div>

    <div class="panel-panel panel-bottom-right col-lg-6 col-sm-12">
      <div class="inside"><?php print $content['bottom-right']; ?></div>
    </div>
  </div>
</div>
