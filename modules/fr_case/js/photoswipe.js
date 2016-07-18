/**
 * @file
 * Add PhotoSwipe integration.
 */

(function($) {

var player;

// Attach Drupal behaviour.
Drupal.behaviors.frCasePhotoSwipe = {
  attach: function(context) {
    // Video player
    $(function() {
      // Create player object
      player = new MediaElementPlayer('#video', {
        type: ['video/mp4'],
        plugins: ['flash', 'silverlight'],
        defaultVideoWidth: 800,
        defaultVideoHeight: 400,
        success: Drupal.PhotoSwipe.prototype.videoSuccess(video)
      });
      // Since video tag must be visible on page load hide it in js
      // It's hidden by altering margin because IE8 flash player crashes while using display none
      $('.video-container').css({ 'marginLeft' : '-9999px' });
    });

    // One of thumbnails was clicked.
    $('.case-scene-dockets a.case-scene-thumbnail').once('photoswipe').on('click', function(e) {
      e.preventDefault();

      var index = $('.case-scene-dockets a.case-scene-thumbnail').index(this);
      new Drupal.PhotoSwipe(index);
    });

    // 'Scene slideshow' button was clicked.
    $('#edit-slideshow').once('photoswipe-slideshow').on('click', function(e) {
      e.preventDefault();

      new Drupal.PhotoSwipe(0).startSlideshow();
    });
  }
};

// PhotoSwipe manipulation object.
Drupal.PhotoSwipe = function(index) {
  var self = this;

  self.slideDuration = 4000;
  self.slideshowIsStarted = false;
  self.currentIndex = index;
  self.exifInfoVisible = false;

  var pswpElement = document.querySelectorAll('.pswp')[0],
      $el_stop = $('.pswp__button--stop'),
      $el_center = $('.pswp__caption__center'),
      $el_toggle = $('#slideshow-toggle'),
      $el_right = $('.pswp__button--arrow--right'),
      $el_left = $('.pswp__button--arrow--left'),
      $el_info = $('.pswp__button--exif, .pswp__button--notes'),
      $el_docket = $('.case-scene-docket'),
      $el_first = $('.pswp__button--arrow--first'),
      $el_last = $('.pswp__button--arrow--last'),
      dockets = Drupal.settings.fr_case.dockets,
      default_restricted_image = Drupal.settings.fr_case.default_restricted_image,
      images = [],
      items = [],
      keys = [],
      visible_dockets = [],
      dockets_keys = [],
      $windowWidth = $(window).width(),
      $windowHeight = $(window).height();

  // Length of dockets object.
  for (var docketKey in dockets) {
    if (dockets.hasOwnProperty(docketKey)) {
      dockets_keys.push(docketKey);
    }
  }
  dockets_keys = dockets_keys.length;

  // If there are all dockets visible.
  if ($el_docket.length == dockets_keys) {
    // Assign keys of docket object to 'keys' array.
    for (var key in dockets) keys.push(key);
    for (var i = 0; i < dockets_keys; i++) {
      for (var j = 0; j < dockets[keys[i]].length; j++) {
        if (dockets[keys[i]][j].access) {
          images.push(dockets[keys[i]][j]);
        } else {
          dockets[keys[i]][j].screensize_url = default_restricted_image;
          images.push(dockets[keys[i]][j]);
        }
      }
    }
  }
  // If there are only part of dockets visible (ajax filtered).
  else {
    $el_docket.each(function() {
      visible_dockets.push($(this).data('id'));
    });
    for (var i = 0; i < visible_dockets.length; i++) {
      for (var j = 0; j < dockets[visible_dockets[i]].length; j++) {
        if (dockets[visible_dockets[i]][j].access) {
          images.push(dockets[visible_dockets[i]][j]);
        } else {
          dockets[keys[i]][j].screensize_url = default_restricted_image;
          images.push(dockets[keys[i]][j]);
        }
      }
    }
  }

  // Prepare array of gallery images.
  for (var k = 0; k < images.length; k++) {
    items.push({
      src: (images[k].type == 'video' ? images[k].thumbnail_url : images[k].screensize_url),
      video_src: images[k].screensize_url,
      title: images[k].order,
      type: images[k].type,
      w: $windowWidth,
      h: $windowHeight,
      id: images[k].id,
      exif_notes: Drupal.theme('ajaxLoader'),
      image_info: images[k].image_info,
      image_number: Drupal.t('Image @image', {'@image': parseInt(k + 1)}),
      image_reference: images[k].ref
    });
  }

  // Options.
  var options = {
    index: index,
    history: false,
    focus: false,
    showAnimationDuration: 0,
    hideAnimationDuration: 0,
    closeOnVerticalDrag: false,
    loop: true,
    zoomEl: false,
    fullscreenEl: false,
    timeToIdle: 0,
    timeToIdleOutside: 0,
    arrowEl: true,
    closeOnScroll: false,
    indexIndicatorSep: ' ' + Drupal.t('of') + ' ',
    addCaptionHTMLFn: self.captionHtml
  };

  // Init gallery.
  self.gallery = new PhotoSwipe(pswpElement, PhotoSwipeUI_Default, items, options);

  // Handle event when user change slide.
  self.gallery.listen('afterChange', function() {
    var prevIndex = self.currentIndex;
    var newIndex = self.gallery.getCurrentIndex();
    var itemType = self.gallery.currItem.type;
    var videoSrc = self.gallery.currItem.video_src;

    self.loaded();
    self.videoPlayer(itemType, videoSrc);

    // Gallery was just opened.
    if (newIndex == prevIndex) {
      return;
    }
    // User switched to next slide.
    if ((newIndex > prevIndex && newIndex !== 0 && prevIndex !== 0) || (newIndex === 0 && prevIndex !== 1) ||  (prevIndex === 0 && newIndex === 1)) {
      self.next();
    }
    // User switched to prev slide.
    else {
      self.prev();
    }
    self.currentIndex = self.gallery.getCurrentIndex();
  });

  // Open the gallery.
  self.gallery.init();

  // Activate videoPlayer if the first chosen item was video item
  var itemType = self.gallery.currItem.type;
  var videoSrc = self.gallery.currItem.video_src;
  if (itemType == 'video') {
    self.videoPlayer(itemType, videoSrc);
  }

  // Event handler for space key.
  function spaceKeyHandler(e) {
    if (e.keyCode === 32) {
      e.preventDefault();
      self.toggleSlideshow();
    }
  }

  // Toggle slideshow with space key.
  $(document).keydown(spaceKeyHandler);

  // Play or pause slideshow.
  $el_toggle.click(function() {
    self.toggleSlideshow();
  });

  // Callback executed when gallery is closed.
  self.gallery.listen('close', function() {
    self.stopSlideshow();
    $el_center.removeClass('info');
    $el_first.off('click');
    $el_last.off('click');
    self.videoPlayer();
    $(document).unbind('keydown', spaceKeyHandler);
  });

  // Show exif / notes information on exif / notes buttons click.
  $el_info.click(function() {
    self.stopSlideshow();
    $el_center.addClass('info');
    self.exifInfoVisible = true;
    self.loadExif();
  });

  //go to first photo
  $el_first.click(function() {
    self.gallery.goTo(0);
  });

  //go to last photo
  $el_last.click(function() {
    self.gallery.goTo((items.length-1));
  });

  // Hide exif / notes information on close button.
  $('.close').live('click', function() {
    self.resetSlideshow();
    self.exifInfoVisible = false;
    $el_center.removeClass('info');
  });

  return self;
};

// Prepare and run video item.
Drupal.PhotoSwipe.prototype.videoPlayer = function(type, src) {
  var self = this;
  // Default arguments
  type = typeof type !== 'undefined' ? type : '';
  src = typeof src !== 'undefined' ? src : '';

  var $video_container = $('.video-container');
  var $exif = $('.pswp__button--exif div');

  // Prepare video to run
  if (type == 'video') {
    if (this.slideshowIsStarted) {
      self.gallery.listen('afterChange', function() {
        self.stopSlideshow();
        player.slideshowStopped = true;
      });
    }
    $exif.html(Drupal.t('Video information'));
    $('.pswp__img').css('marginLeft', '-9999px');
    $video_container.css({ 'marginLeft' : 'auto' });
    player.pause();
    player.setSrc(src);
    player.load();
    player.play();
    return false;
  } else {
  // Hide video and pause it
    $exif.html(Drupal.t('Exif information'));
    $video_container.css({ 'marginLeft' : '-9999px' });
    player.pause();
    player.setSrc(''); //set src to '' to prevent from downloading video file
    $('.pswp__img').css('marginLeft', 'auto');
  }
};

// Set vertical position of video
Drupal.PhotoSwipe.prototype.videoPosition = function(videoHeight) {
  videoHeight = typeof videoHeight !== 'undefined' ? videoHeight : '';
  if (videoHeight != '') {
    var topDistance = ($(window).height() - videoHeight)/2;
    $('.video-container').css({'top' : topDistance, 'bottom' : 'auto'});
  }
};

// Video success
Drupal.PhotoSwipe.prototype.videoSuccess = function (video) {
  if (video.addEventListener) {
    video.addEventListener('loadeddata', function () {
      //position video verically after video is loaded
      var $mep_height = $('#mep_0').height();
      Drupal.PhotoSwipe.prototype.videoPosition($mep_height);
    });
  } else {
    // For IE8 - this value is passed directly to the function because Flash player doesn't support loadeddata method
    // so it can't return real height of the element.
    Drupal.PhotoSwipe.prototype.videoPosition(400);
  }
};

// Callback triggered when image is loaded.
Drupal.PhotoSwipe.prototype.loaded = function() {
  if (this.exifInfoVisible) {
    this.loadExif();
  }
};

// Load exif info.
Drupal.PhotoSwipe.prototype.loadExif = function() {
  var currentItem = this.gallery.currItem;

  $.ajax({
    url: Drupal.url('scene-image-data/' + currentItem.id),
    complete: function (response, status) {
      if (response.status == 'error' || response.status == 'parsererror') {
        console.error(response);
      }
      else {
        var objResponse = JSON.parse(response.responseText);
        if (!objResponse.exif) {
          objResponse.exif = Drupal.t('N/A');
        }
        if (!objResponse.notes) {
          objResponse.notes = Drupal.t('N/A');
        }
        $('.exif-content').html(objResponse.exif);
        $('.notes-content').html(objResponse.notes);
      }
    },
    dataType: 'json',
    type: 'GET'
  });
};

// Callback for "Previous" button.
Drupal.PhotoSwipe.prototype.prev = function() {
  this.resetSlideshow();
};

// Callback for "Next" button.
Drupal.PhotoSwipe.prototype.next = function() {
  this.resetSlideshow();
};

// Callback for gallery images caption.
Drupal.PhotoSwipe.prototype.captionHtml = function(item, captionEl, isFake) {
  var html,
      panel_title;
  if (item.type == 'video') {
    panel_title = Drupal.t('Video information');
  } else {
    panel_title = Drupal.t('Exif');
  }
  html = '<div class="image-info"><div class="item first">' + item.image_info + item.image_number + '</div><div class="item last">' + item.image_reference + '</div></div>';
  html +=  '<div class="exif_notes"><div class="exif">' + '<h4>' + panel_title + '</h4><div class="exif-content">' + item.exif_notes + '</div></div>';
  html += '<div class="notes"><div class="close">' + Drupal.t('Close') + '</div>' + '<h4>' + Drupal.t('Notes') + '</h4><div class="notes-content">' + item.exif_notes + '</div></div></div>';
  captionEl.children[0].innerHTML = html;
  return true;
};

// Start slideshow.
Drupal.PhotoSwipe.prototype.startSlideshow = function() {
  var self = this;
  self.slideshowIsStarted = true;
  self.slideshowInterval = setInterval(function() {
    self.gallery.next();
  }, self.slideDuration);

  $('.pswp__button--stop')
    .removeClass('start')
    .html(Drupal.t('Stop slideshow') + '<span></span>');
};

// Stop slideshow.
Drupal.PhotoSwipe.prototype.stopSlideshow = function() {
  this.slideshowIsStarted = false;
  clearInterval(this.slideshowInterval);
  $('.pswp__button--stop')
    .addClass('start')
    .html(Drupal.t('Start slideshow') + '<span></span>');
};

// Reset slideshow timer.
Drupal.PhotoSwipe.prototype.resetSlideshow = function() {
  var self = this;
  if (self.slideshowIsStarted) {
    self.stopSlideshow();
    self.startSlideshow();
  }
};

// Toggle slideshow.
Drupal.PhotoSwipe.prototype.toggleSlideshow = function() {
  if (this.slideshowIsStarted) {
    this.stopSlideshow();
  }
  else {
    this.startSlideshow();
  }
};

})(jQuery);
