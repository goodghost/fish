(function ($) {

Drupal.behaviors.frDatasetWidget = {
  attach: function (context, settings) {

    // Add "form-selected" class when radio button is checked.
    var $radio = $('td.icon-mapping-icon input[type="radio"]');

    $radio.each(function() {
      var $this = $(this);
      if ($this.is(':checked')) {
        $this.addClass('form-selected');
      }
      else {
        $this.removeClass('form-selected');
      }
    });

    $radio.on('change', function() {
      var $this = $(this);
      var $siblings = $('[name="' + $this.attr('name') + '"');
      $siblings.removeClass('form-selected');
      if ($this.is(':checked')) {
        $this.addClass('form-selected');
      }
      else {
        $this.removeClass('form-selected');
      }
    });

    // Disable submit buttons when AJAX is still in progress.
    var $submitButtons = $('.form-actions input[type=submit]');

    $('.field-type-dataset').find('input, select')
      .ajaxStart(function(event) {
        $submitButtons.attr('disabled', true);
        //var $element = $(this);
        //if (!$element.isDisabled) {
        //  $element.addClass('dataset-disabled').attr('disabled', true);
        //}
      })
      .ajaxStop(function(event) {
        $submitButtons.attr('disabled', false);
        //var $element = $(this);
        //if ($element.hasClass('dataset-disabled')) {
        //  $element.removeAttr('disabled');
        //}
      });
  }
}

}(jQuery));

