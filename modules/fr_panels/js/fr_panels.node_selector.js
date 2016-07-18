(function($){
  Drupal.behaviors.NodePaneSelection = {
    attach: function(context) {
      // hide submit button
      $('#ctools-node-content-type-selection-form').find('#edit-next').hide();
      // fill the ctools form with the selected node ID

      $('a.node-pane-selector').click(function() {
        var $nodeSelector = $(this);
        $nodeSelector.addClass('disabled');
        var selected_nid = $nodeSelector.attr('data-nid');
        $('[name="selected_nid"]').val(selected_nid) ;
        $('#ctools-node-content-type-selection-form').submit();
        return false;
      });
    }
  };
})(jQuery);
