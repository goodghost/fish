/**
 * @file
 * User terms and conditions acceptance.
 */

(function($) {
// Attach Drupal behaviour.
Drupal.behaviors.frUserTermsAndConditions = {
  attach: function(context) {
    var $edit_submit = $('.form-submit'),
        $login_form = $('#user-login'),
        $body = $('body'),
        terms_and_conditions = Drupal.settings.fr_user.terms_and_conditions;

    if(terms_and_conditions) {
      //create popup and pseudo login button
      $login_form.append('<div class="popup-actions"><h3>' + Drupal.t("Terms and conditions") + '</h3><div class="terms-and-conditions">' + terms_and_conditions + '</div><div class="cancel">' + Drupal.t("Cancel") + '</div></div>' + '<div class="login">' + Drupal.t("Log in") + '</div>');
      $body.prepend('<div class="layer"></div>');

      var $popup = $('.popup-actions'),
          $login = $('.login'),
          $layer = $('.layer'),
          $cancel = $('.cancel');

      //change 'Log in' text to 'OK' and move it to .popup-actions
      $edit_submit.attr('value', Drupal.t('OK')).appendTo('.popup-actions');

      //show popup and hide pseudo login button on login click
      $login.click(function() {
        $popup.css('display', 'block');
        $layer.css('display', 'block');
        $(this).css('display', 'none');
      });

      //hide popup and show pseudo login on cancel click
      $cancel.click(function() {
        $popup.css('display', 'none');
        $layer.css('display', 'none');
        $login.css('display', 'block');
      });

      //disable enter key to submit a form and display popup
      $(window).keydown(function(event){
        if(event.keyCode == 13) {
          event.preventDefault();
          $popup.css('display', 'block');
          $layer.css('display', 'block');
          $login.css('display', 'none');
          return false;
        }
      });
    }
  }
}})(jQuery);