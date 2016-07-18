(function ($) { 
  Drupal.behaviors.fr_form = {
    attach: function (context, settings) {
      var $description = $('.webform-fish-api .description'),
          $form_action = $('.webform-fish-api .form-actions', context),
          $form = $('.webform-fish-api'),
          unchangedForm = $form.serialize(),
          inputDataConfirm = $('input.confirmation'),
          buttonsResetCancel = $('.button-reset, .button-cancel'),
          value = null,
          $form_elements = $('.webform-fish-api-add-new-item input.form-text, .webform-fish-api-add-new-item select'),
          i = 0,
          newSubmission = Drupal.settings.fr_form.fr_form_title_new_submission,
          editSubmission = Drupal.settings.fr_form.fr_form_title_edit_submission,
          $pageTitle = $('.page-title');

      // Fill the form with values from data-value attribute and change title of the page
      $pageTitle.text(newSubmission);
      $($form_elements).each(function() {
        attr = $(this).attr('data-value');
        if (typeof attr !== typeof undefined && attr !== false) {
          $(this).val(attr);
          if (i == '0') {
            $pageTitle.text(editSubmission);
            i++;
          }
        }
      });
      i = 0;

      // Description tooltips for webform fields 
      $description.each(function() {
        $(this).before('<div class="fa fa-question-circle question-mark"><span>' + $(this).html() + '</span></div');
      });
      $('.question-mark').hover(function() {
        $('span', this).fadeIn(500);
      }, function(){
        $('span', this).fadeOut(300);
      });

      // Reset the Form and Cancel buttons
      $form_action.append('<div class="button-reset">' + Drupal.t('Reset') + '</div>', '<div class="button-cancel">' + Drupal.t('Cancel') + '</div>');
      $('#webform-components-form').find('.button-reset, .button-cancel').hide();
      
      // Get value of data-confirmation attribute
      inputDataConfirm.click(function() {
        value = $(this).attr('data-confirmation');
      });
      
      // Disable default action if data-confirmation value is 1
      $('.webform-fish-api.view-page').submit(function(event) {
        if (value == '1') {
          event.preventDefault();
          value = 0;
        }
      });

      jQuery.fn.reset = function() {
        $(this).each ( function() {
          this.reset();
        });
      }

      $('.button-reset', context).add(inputDataConfirm).once().bind('click', function (event) {
        $('<div id="dialog-confirm">' + Drupal.t('Are you sure?') + '</div>').appendTo('body');
        $('#dialog-confirm').dialog({
          resizable: false,
          height: 160,
          modal: true,
          dialogClass: 'no-close',
          buttons: {
            OK: function() {
              if ($(event.target).hasClass('button-reset')) {
                $('.webform-fish-api').reset();
                $('.webform-fish-api .ajax-processed').val('');             
              } else if ($(event.target).attr('data-confirmation', '1')) {
                 // Unbind previously blocked submit 
                $('.webform-fish-api.view-page').unbind('submit');
                 // Trigger submit button
                $('#'+event.target.id).trigger('click');
              }
              $(this).dialog('destroy');
            },
            Cancel: function() {
              $(this).dialog('close');
            }
          }
        });
      });  

      $('.button-cancel').click( function (event) {
        //Check if form has been altered 
        if ($('.webform-fish-api').serialize() != unchangedForm) {
          $('<div id="dialog-confirm">' + Drupal.t('Are you sure?') + '</div>').appendTo('body');
          $('#dialog-confirm').dialog({
            resizable: false,
            height: 160,
            modal: true,
            dialogClass: 'no-close',
            buttons: {
              OK: function() {
                parent.history.back();
              },
              Cancel: function() {
                $(this).dialog('close');
              }
            }
          });  
        } else {
          parent.history.back();
        }
      });     
    }
  };
})(jQuery);