(function($) {
  Drupal.behaviors.frCaseTooltip = {
    attach: function(context) {
      $('a.case-scene-thumbnail').hover(
        function() {
          var ref = $(this).data('ref');
          $(this).after('<div class="tooltip">' + ref + '</div>');
        }, 
        function() {
          $('.tooltip').remove();
        }
      )
    }
  }
})(jQuery);