(function ($) {

/**
 * JS version of Drupal url().
 */
Drupal.url = function(path) {
  return Drupal.settings.basePath + Drupal.settings.pathPrefix + path;
};

// Theme function for ajax loader.
Drupal.theme.prototype.ajaxLoader = function() {
  return '<div class="ajax-progress-wrapper"><div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>' + Drupal.t('Please wait...') + '</div>';
};

}(jQuery));

