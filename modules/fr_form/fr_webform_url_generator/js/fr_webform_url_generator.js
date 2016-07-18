(function ($) { 
  Drupal.fr_webform_url_generator = {};

  Drupal.fr_webform_url_generator.attachRows = function(context, $modal) {
    var $row = $('.view-webform-picker tr');
    $row.off('click');
    $row.on('click', function() {
      // Get NID
      nid = $(this).attr('class').replace('webform-node-', '');
              
      // Add 'selected class to row cells
      $('.view-webform-picker td').removeClass('selected');
      $('td', this).addClass('selected');

      // Get node data (operations and category or object)
      Drupal.fr_webform_url_generator.generateNodeOptions(nid, Drupal.fr_webform_url_generator.input_id);
    });
  }

  Drupal.fr_webform_url_generator.input_id = undefined;

  Drupal.fr_webform_url_generator.generateNodeOptions = function(nid, input_id) {
    $.ajax({
      type     : "GET",
      url      : "/fr_webform_node_data/" + nid,
      success : function(content) {
        $('tr.generated').slideUp(400, function() {
          $(this).remove();
        });

        content = JSON.parse(content);
        var form = '';

        form += '<div class="form-link-wrapper-' + nid + '">';
        // Available operations select form element
        form += '<label>' + Drupal.t('Select operation: ') + '</label>';
        form += '<select class="available-operations">';
        for (var operation_key in content.operations) {
          if (content.operations.hasOwnProperty(operation_key)) {
            form += '<option value="' + operation_key + '">' + content.operations[operation_key] + '</option>';
          }
        }
        form += '</select>';

        // Objects select form element
        if (content.category == '1') {
          form += '<label>' + Drupal.t('Select object: ') + '</label>';
          form += '<select class="objects">';
          form += '<option value="' + content.objects + '">' + content.objects + '</option>';
          form += '</select>';
        } else {
          form += '<label>' + Drupal.t('Select category: ') + '</label>';
          form += '<select class="objects">';
          for (var object_key in content.objects) {
            if (content.objects.hasOwnProperty(object_key)) {
              form += '<option value="' + content.objects[object_key] + '">' + content.objects[object_key] + '</option>';
            }
          }
          form += '</select>';
        }

        // Submit button
        form += '<button type="button" class="button-link-' + nid + '">' + Drupal.t('Insert link') + '</button>';
        $('<tr class="generated"><td colspan="4">' + form + '</td></tr>').insertAfter('.webform-node-' + nid);
        $('tr.generated').hide().show('slow');
        form += '</div>';

        $('.button-link-'+nid).click(function() {
          var link = '';
          var operations_value = $('.form-link-wrapper-' + nid + ' .available-operations').val();
          var object_value = $('.form-link-wrapper-' + nid + ' .objects').val();

          if (operations_value == '0') {
            link = 'submission/' + nid + '/{' + content.primary_key + '}/' + object_value + '/edit';
          } else if (operations_value == '1') {
            link = 'submission/' + nid + '/{' + content.primary_key + '}/' + object_value;
          } else if (operations_value == '2') {
            link = 'node/' + nid + '/object/' + object_value;
          }

          $('#' + input_id).val(link);
          $('#modal-generator').dialog('close');
        });

      },
      error: function(err) {
        console.log(err);
      }
    });
  }

  Drupal.behaviors.fr_webform_url_generator = {
    attach: function (context, settings) {
      $('#form-picker').attr('id', 'modal-generator');
      Drupal.fr_webform_url_generator.attachRows(context, $('#modal-generator'));
    
      // Attach jQuery UI dialog
      $('#modal-generator:not(.ajax-processed)').addClass('ajax-processed').dialog({
        resizable: true,
        height: ($(window).height() - 200),
        width: ($(window).width() - 100),
        modal: true,
        title: Drupal.t('Form picker'),
        autoOpen: false
      });

      var $input_url_generator = $('input.form-type-url-generator:not(.ajax-processed)').addClass('ajax-processed'),
          generated_button = '<a class="url-generator">'+Drupal.t('Pick a form')+'</a>';
      
      // Generate button for each input which has class .form-type-url-generator
      $(generated_button).insertAfter($input_url_generator);

      var $open_generator = $('.url-generator:not(.ajax-processed)').addClass('ajax-processed');
      $open_generator.click(function() {
        Drupal.fr_webform_url_generator.input_id = $(this).prev().attr('id');
        $('#modal-generator').dialog('open');
        Drupal.fr_webform_url_generator.attachRows(context, $('#modal-generator'));
      });
    }
  }
})(jQuery);