/**
 * @file
 * Add lazy load functionality.
 */

(function ($) {

  Drupal.behaviors.frCaseLazyLoad = {
    attach: function(context) {
      $('img.lazy').lazyload();
    }
  }

})(jQuery);
