(function ($) { 
  Drupal.behaviors.fr_form_timepicker = {
    attach: function (context, settings) {
      // Time picker
       $('.webform-component-datetime-field input').datetimepicker({
         timeFormat : 'HH:mm',
         dateFormat : 'dd/mm/yy',
         showSecond : false
      });
    }
  };
})(jQuery);