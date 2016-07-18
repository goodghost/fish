/**
 * @file
 * Add button to close Drupal status message box.
 */

(function ($) {

Drupal.behaviors.closeMessages = {
  attach: function(context) {
    $('.messages', context).append('<a href="javascript:()" class="close-messages" onclick="jQuery(this).parent().remove();">' + Drupal.t('Close') + '</a>');
  }
};

})(jQuery);
