/**
 * @file
 * Add slide dashboard entity in wallboard view.
 */
(function ($) {
Drupal.behaviors.wallboardSlide = {
  attach: function(context) {
    var duration = parseInt(Drupal.settings.wallboardSlide.slideSettings.duration, 10)*1000,
        transitionSpeed = parseFloat(Drupal.settings.wallboardSlide.slideSettings.transitionSpeed)*1000,
        effect = Drupal.settings.wallboardSlide.slideSettings.effect,
        i = 0,
        j = 0,
        focus = true,
        interval,
        ie,
        timeoutFrequency = 20,
        $item = $('.node-wallboard .field-name-field-dashboards.field-type-entityreference > .field-items > .field-item'),
        $items = $('.node-wallboard .field-name-field-dashboards.field-type-entityreference > .field-items'),
        $body = $('body'),
        $windowWidth = $(window).width(),
        $bodyInnerWidth = $('body').width(),
        step = ($windowWidth * timeoutFrequency) / (duration - transitionSpeed * 2),
        $regionTop = $('.region-page-top'),
        $trayNavbarActive = $('.navbar-tray.navbar-active'),
        $branding = $('#branding'),
        length = $item.length;

    // Hide region top for better visual effect
    $regionTop.css({ 'display' : 'none' });
    $branding.css('margin-top', '-85px');

    //Create button for navbar open
    $body.append('<div class="navbar-open">' + Drupal.t('Open navbar') + '</div>');

    // Create timer element for time passing visualization
    $body.append('<div class="timer"></div>');

    var $timer = $('.timer'),
        $navbarOpen = $('.navbar-open');

    $timer.css('width', 0);

    // Open navbar
    $navbarOpen.click(function() {
      $regionTop.css('display', 'block');
      $trayNavbarActive.css('padding-top', '64px');
      $branding.css('margin-top', '0');
      $this.html(Drupal.t('Close navbar'));
    });

    // Show progress of timer width
    var setWidth = function() {
      if (focus) {
        $timer.css({ 'width' : step*j + 'px' });
        j++;
        if (step*j < $windowWidth) {
          setTimeout(setWidth, timeoutFrequency);
        } else {
          $timer.css({ 'width' : 0 });
          j = 0;
        }
      }
    };

    var changeSlide = function() {
      setTimeout(setWidth, timeoutFrequency);
      switch(effect) {
        // Fade transition
        case '0': 
          
          $item.eq(i).animate({ 'opacity' : '0' }, transitionSpeed, function() {
            i++;
            if (i === length) {
              i = 0;
            }
            $item.eq(i).animate({ 'opacity' : '1' }, transitionSpeed, function() {});
          });
        break;

        // Slide horizontal
        case '1':
          
          $body.css('overflow-x', 'hidden');

          $item.eq(i).animate({ 'left' : '-' + $windowWidth + 'px' }, transitionSpeed, function() {
            $item.eq(i).css('opacity', '0');
            i++;
            if (i === length) {
              i = 0;
            }
            $item.eq(i).css({ 'opacity' : '1', 'left' : $windowWidth + 'px' });
            $item.eq(i).animate({ 'left' : '0' }, transitionSpeed);
          });
        break;

        // Slide vertical
        case '2':
          
          $items.css('overflow', 'hidden');
          $body.css('overflow-y', 'hidden');
          $item.eq(i).animate({ 'top' : '-' + $item.height() + 'px' }, transitionSpeed, function() {
            $item.eq(i).css('opacity', '0');
            i++;
            if (i === length) {
              i = 0;
            }
            $item.eq(i).css({ 'opacity' : '100', 'top' : $item.height() + 'px' });
            $item.eq(i).animate({ 'top' : '15px' }, transitionSpeed);
          });           
        break;
      }
    };

    $(window).load(function() {
      $item.not(':first').css('opacity', '0');
      setTimeout(setWidth, timeoutFrequency);
      interval = setInterval(changeSlide, duration); 
      ie = Drupal.detectIE();

      // Check if is not IE
      if (!ie) {
        // Start interval and progress bar animatiom when window gets focus
        $(window).bind('focus', function() {
          focus = true;
          // Reset iterators
          j = 0;
          i = 0;

          //Show only first item
          $item.not(':first').css('opacity', '0');
          $item.eq(i).css('opacity', '0');

          // Start interval
          setTimeout(setWidth, timeoutFrequency);
          interval = setInterval(changeSlide, duration);
        });

        // Stop interval and progress bar animatiom when window lost focus
        $(window).bind('blur', function() {
          focus = false;
          clearInterval(interval);
        });
      }
    });
  }
};
})(jQuery);

// Detect if it's Internet Explorer browser
Drupal.detectIE = function() {
  var match = navigator.userAgent.match(/(?:MSIE |Trident\/.*; rv:)(\d+)/);
  return match ? parseInt(match[1]) : undefined;
}