(function ($) {

Drupal.behaviors.fr_navbar = {
  attach: function (context, settings) {
    $('.navbar-tray-vertical', context).bind('mousewheel DOMMouseScroll', function(e) {
      $(this).scrollTop($(this).scrollTop() + e.originalEvent.deltaY);
      e.preventDefault();
    });
  }
}

}(jQuery));

