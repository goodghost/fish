/**
 * @file
 * Add dashboard resizing funcionallity.
 */
(function ($) {
Drupal.behaviors.common = {
  attach: function(context) {
    function resizeDashboard() {
      var headerHeight = $('#branding').outerHeight() + 150,
          windowHeight = $(window).height();

      dashboardHeight = windowHeight - headerHeight;
      $('.panel-two-by-two').css("height", dashboardHeight + "px");
      $('.page-node-panelizer-page-manager #panel-dashboard').css('height', 'auto');
    }
    $(window).on('resize', function() { resizeDashboard(); });
    return resizeDashboard();
}}
})(jQuery);