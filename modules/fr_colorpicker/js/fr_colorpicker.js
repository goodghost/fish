/**
 * @file
 * Javascript for Farbtastic widget.
 */

(function ($) {

  /**
   * Provides a farbtastic colorpicker for the form element.
   */
  Drupal.behaviors.frColorpicker = {
    attach: function (context) {
      // Display the current value as background if the field has one.
      $('.form-colorpicker', context)
          .each(function() {
            var color = $(this).val();
            if (color) {
              $(this).css({
                'background-color': color,
                'color': contrast(color)
              });
            }
          })
          .focus(function() {
            var $editField = $(this);
            var $picker = $('#' + $editField.data('picker'), context);

            // Hide all color pickers except this one.
            $('.colorpicker-picker').hide();
            $picker.show();

            $picker.position({
              of: $editField,
              my: 'left top',
              at: 'left bottom'
            });

            var updateBackground = function() {
              // Catch errors caused by invalid hex codes.
              var unpacked = farb.unpack(this.value);
              if (!unpacked) {
                return;
              }
              // If a valid color, set background/foreground colors.
              $(this).css({
                backgroundColor: this.value,
                'color': farb.RGBToHSL(unpacked)[2] > 0.5 ? '#000' : '#fff'
              });
            };

            var updatePicker = function() {
              farb.setColor(this.value);
            };

            // Adjust the background color on keyup and onload.
            $editField
              .unbind('keyup.colorpicker')
              .bind('keyup.colorpicker', updateBackground)
              .bind('keyup.colorpicker', updatePicker);

            // Attach Farbtastic.
            var farb = $.farbtastic($picker);
            farb.setColor($editField.val());
            farb.linkTo(function(color) {
              $editField.val(color);
              updateBackground.apply($editField[0]);
            });
          })
          .focusout(function() {
            $('.colorpicker-picker').hide();
          });
    }
  };

  // Change text color based on background color.
  // See: http://www.w3.org/TR/AERT#color-contrast
  function contrast(hexcolor) {
    hexcolor = hexcolor.substring(1);
    var r = parseInt(hexcolor.substr(0, 2), 16);
    var g = parseInt(hexcolor.substr(2, 2), 16);
    var b = parseInt(hexcolor.substr(4, 2), 16);
    var yiq = ((r * 299) + (g * 587) + (b * 114)) / 1000;
    return (yiq > 125) ? 'black' : 'white';
  }

})(jQuery);
