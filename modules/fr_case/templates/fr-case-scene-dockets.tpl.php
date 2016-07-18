<?php

/**
 * @file fr-case-scene-dockets.tpl.php
 * Default template implementation for case scenes.
 *
 * Available variables:
 * - $case: A raw case loaded directly form endpoint.
 * - $scene: A raw scene loaded directly form endpoint.
 * - $dockets: Array of scene dockets width images.
 * - $total_images: Images counter.
 */

?>
<div id="case-scene-dockets-wrapper" class="case-scene-dockets">
  <div class="case-scene-dockets-counter"><?php print t('Total images: @total-images', array('@total-images' => $total_images)); ?></div>
  <?php if ($dockets): ?>
    <?php foreach ($dockets as $docket_label => $docket): ?>
      <div class="case-scene-docket case-scene-docket-name<?php print drupal_html_class($docket_label); ?>" data-id="<?php print $docket_label; ?>">
        <?php if ($docket_label): ?>
          <div class="scene-docket-infobox">
            <h4 class="docket-label"><?php print $docket_label; ?></h4>
            <?php if (!empty($docket[0]['user_id'])): ?>
              <div class="case-scene-docket-created-by"><?php print t('created by %user', array('%user' => $docket[0]['user_id'])); ?></div>
            <?php endif; ?>
            <?php if ($is_remote): ?>
              <a href="<?php print $print_links[$docket_label]; ?>" class="order-print"><?php print t('Order print'); ?></a>
            <?php endif; ?>
          </div>
        <?php endif; ?>
        <div class="docket-images">
          <?php foreach ($docket as $image_index => $docket_image): ?>
            <div class="docket-image<?php print $is_admin ? ' accessible' : '' ?>">
              <a
                class="case-scene-thumbnail<?php print $docket_image['type'] == 'video' ? ' case-scene-thumbnail-video' : ''; ?> case-scene-thumbnail--<?php print $docket_image['sensitive'] ? 'sensitive' : 'not-sensitive'; ?> case-scene-thumbnail--<?php print $docket_image['restricted'] ? 'restricted' : 'not-restricted'; ?>"
                data-user="<?php print $docket_image['user_id']; ?>"
                data-ref="<?php print $docket_image['ref']; ?> <?php print $docket_image['sensitive'] ? '<span>'.t('Sensitive image view with caution').'</span>' : ''; ?> <?php print $docket_image['restricted'] ? '<span>'.t('Restricted Image').'</span>' : ''; ?>"
                href="<?php $docket_image['type'] == 'image' ? print $docket_image['screensize_url'] : print $docket_image['thumbnail_url']; ?>"
                >
                <?php if ($docket_image['sensitive']): ?>
                  <span class="sensitive"></span>
                <?php endif; ?>
                <?php if ($docket_image['restricted']): ?>
                  <div class="image-restricted"></div>
                <?php endif; ?>

                <?php if ($docket_image['access']): ?>
                  <img
                    class="lazy"
                    data-original="<?php print $docket_image['thumbnail_url']; ?>"
                    alt="<?php print $docket_image['ref']; ?>"
                    />
                <?php endif; ?>
              </a>
              <div class="image-details">
                <label><?php print $image_index + 1; ?></label>
                <?php
                // Code below are just for purposes of presentation that restricted,
                // locked, image type elements are implemented in CSS and ready to use.
                ?>
                <?php if ($is_admin): ?>
                  <div class="restrict"></div>
                  <div class="lock"></div>
                <?php endif; ?>
                <?php if (in_array($docket_image['category_class'], array('fingerprint', 'footwear'))): ?>
                  <div class="type <?php print $docket_image['category_class']; ?>" title="<?php print $docket_image['category_class']; ?>"></div>
                <?php endif; ?>
              </div>
            </div>
            
          <?php endforeach; ?>
        </div>
      </div>
    <?php endforeach; ?>
  <?php else: ?>
    <div class="case-scene-dockets-empty">
      <?php print t('No results for given query.'); ?>
    </div>
  <?php endif; ?>
</div>

<!-- Root element of PhotoSwipe. Must have class pswp. -->
<div class="pswp" tabindex="-1" role="dialog" aria-hidden="true">
  <!-- Background of PhotoSwipe. 
  It's a separate element as animating opacity is faster than rgba(). -->
  <div class="pswp__bg"></div>
  <!-- Slides wrapper with overflow:hidden. -->
  <div class="pswp__scroll-wrap">

  <!-- Container that holds slides. 
  PhotoSwipe keeps only 3 of them in the DOM to save memory.
  Don't modify these 3 pswp__item elements, data is added later on. -->
    <div class="pswp__container">
      <div class="pswp__item"></div>
      <div class="pswp__item"></div>
      <div class="pswp__item"></div>
    </div>

    <!-- Default (PhotoSwipeUI_Default) interface on top of sliding area. Can be changed. -->
    <div class="pswp__ui pswp__ui--hidden">
      <div class="pswp__top-bar">
        <!--  Controls are self-explanatory. Order can be changed. -->
          <div class="pswp__counter"></div>
          <div class="pswp__button pswp__button--exif">
            <span></span><div><?php print t('Exif information'); ?></div>
          </div>

          <div class="pswp__button pswp__button--notes" title="<?php print t('Notes'); ?>"><span></span><?php print t('Notes'); ?></div>

          <div class="pswp__button pswp__button--close" title="<?php print t('Close (Esc)'); ?>"><span></span><?php print t('Close'); ?></div>

          <div class="pswp__button pswp__button--arrow--last" title="<?php print t('Last'); ?>"></div>
          <div class="pswp__button pswp__button--arrow--right" title="<?php print t('Next'); ?>"></div>
          <div class="pswp__button pswp__button--arrow--left" title="<?php print t('Previous'); ?>"></div>
          <div class="pswp__button pswp__button--arrow--first" title="<?php print t('First'); ?>"></div>

          <div class="pswp__button navigation-name"><?php print t('Navigation'); ?></div>
          <div class="pswp__button pswp__button--stop start" id="slideshow-toggle" title="<?php print t('Toggle slideshow (space)'); ?>"><?php print t('Start slideshow'); ?><span></span></div>
          <div class="pswp__button pswp__button--share" title="<?php print t('Share'); ?>"></div>
          <div class="pswp__button pswp__button--fs" title="<?php print t('Toggle fullscreen'); ?>"><?php print t('Fullscreen'); ?><span></span></div>
          <div class="pswp__button pswp__button--zoom" title="<?php print t('Zoom in/out'); ?>"></div>
          <div class="pswp__preloader">
            <div class="pswp__preloader__icn">
              <div class="pswp__preloader__cut">
                <div class="pswp__preloader__donut"></div>
              </div>
              </div>
            </div>
        </div>
        <div class="pswp__share-modal pswp__share-modal--hidden pswp__single-tap">
          <div class="pswp__share-tooltip"></div> 
        </div>
        <div class="pswp__caption">
          <div class="pswp__caption__center"></div>
        </div>
    </div>
  </div>
  <div class="video-container">
    <div class="inner">
      <?php print $video; ?>
    </div>
  </div>
</div>
