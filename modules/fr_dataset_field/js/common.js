/**
 * @file
 * Add google chart functionality.
 */

(function ($) {

Drupal.fr = Drupal.fr || {};

Drupal.fr.dataset = {

  // Set size of font depended on window width.
  relativeFontSize: function(size) {
    var width = $(window).width(),
        defaultSize = 14,
        windowSize = [
          { uxga : [1600, 2586, 2] },
          { wxga : [1200, 1599, 1.5] },
          {  xga : [992, 1199, 1] }
        ];

    for (var j = 0; j < windowSize.length; j++) {
      for (var key in windowSize[j]) {
        if (windowSize[j].hasOwnProperty(key)) {
          if (width >= windowSize[j][key][0] && width <= windowSize[j][key][1]) {
            if (size) {
              size = windowSize[j][key][2]*size;
            } else {
              size = windowSize[j][key][2]*defaultSize;
            }
          }
        }
      }
    }
    return size;
  },

  renderCharts: function() {
    $.each(Drupal.settings.fr_dataset_field.datasetVisualisation, function(index, chartSettings) {
      var chartData = $('#' + chartSettings.container_id).data('chart');
      var chartWrapper;

      if (chartData.length === 0) {
        return;
      }
      try {
        chartWrapper = new Drupal.GoogleChart(chartData, chartSettings);
        chartWrapper.render();
      }
      catch (err) {
        console.error(err);
        document.getElementById(chartSettings.container_id).innerHTML = '<strong>' + Drupal.t('Error') + ':</strong> ' + err.message;
      }
    });
  },

  replaceAll: function(str, replacementsMap) {
    var string = str, key;
    for (key in replacementsMap) string = string.replace(new RegExp('\\{' + key + '\\}', 'gm'), replacementsMap[key]);
    return string;
  },

  isExternalLink: function(url) {
    var match = url.match(/^([^:\/?#]+:)?(?:\/\/([^\/?#]*))?([^?#]+)?(\?[^#]*)?(#.*)?/);
    if (typeof match[1] === 'string' && match[1].length > 0 && match[1].toLowerCase() !== location.protocol) {
      return true;
    }

    if (typeof match[2] === 'string' && match[2].length > 0 && match[2].replace(new RegExp(':(' + {'http:':80, 'https:':443}[location.protocol] + ')?$'), '') !== location.host) {
      return true;
    }

    return false;
  }

};


// Drupal behaviors for dataset field.
Drupal.behaviors.fr_dataset_field = {
  attach: function(context) {
    // Render charts after library is loaded.
    if (typeof google !== 'undefined') {
      google.load('visualization', '1.0', {
        packages: ['corechart', 'table', 'gauge'],
        callback: Drupal.fr.dataset.renderCharts
      });
    }
    else {
      return;
    }

    // Auto refresh report data.
    $('.button-autoclick').once().each(function() {
      var $button = $(this);
      var interval = $button.data('interval');

      if (interval) {
        setInterval(function() {
          $button.not('.progress-disabled').trigger('mousedown');
        }, interval);
      }
    });

    // Redraw charts on window resize.
    var debounce;
    $(window).once('resize-charts').resize(function() {
      clearTimeout(debounce);
      debounce = setTimeout(function() {
        Drupal.fr.dataset.renderCharts();
      }, 200);
    });

    // Prevent JS alerts.
    window.alert = function(text) {
      // Check if the console exists (required e.g. for older IE versions).
      if (typeof console !== 'undefined') {
        // Log error to console instead.
        console.error("Module 'prevent_js_alerts' prevented the following alert: " + text);
      }
      return true;
    };

  }
}

})(jQuery);
