/**
 * @file
 * Gague functionality.
 */

(function ($) {

// Function for generating gauge chart.
Drupal.GoogleChart.prototype.renderGauge = function() {
  var self = this;
  var containerId = self.chartSettings.container_id;
  var displaySettings = self.chartSettings.item.display_settings;
  var fields = self.chartSettings.item.fields;
  var fieldLabel, fieldName;

  // Maybe this could be generated automatically based on values of data?
  var options = displaySettings,
    data, title, chart,
    chartContainer = document.getElementById(containerId),
    $chartContainer = $(chartContainer);

  if (typeof options.width === 'undefined' || !options.width) {
    options.width = 400;
  }
  if (typeof options.width === 'undefined' || !options.height) {
    options.height = 220;
  }

  if (self.chartData[0].length > 2) {
    // Remove ajax throbber.
    $chartContainer.html('');

    for (var index = 0; index < self.chartData.length; index++) {
      data = new google.visualization.DataTable();
      data.addColumn('string');
      data.addColumn('number');

      for (var innerIndex = 0; innerIndex < self.chartData[0].length; innerIndex++) {
        if (Drupal.GoogleChart.dataTypes[self.chartData[index][innerIndex].type] == 'number') {
          fieldName = self.chartData[index][innerIndex].name;

          if (typeof fields[fieldName] !== 'undefined' && fields[fieldName].label) {
            fieldLabel = fields[fieldName].label;
          }
          else {
            fieldLabel = fieldName;
          }
          data.addRow([fieldLabel, self.chartData[index][innerIndex].value]);
        }
        else {
          title = self.chartData[index][innerIndex].value;
        }
      }

      // Create containers for nested gauges.
      $chartContainer.append('<div id="' + containerId + index + '"></div>');

      // Draw chart
      chart = new google.visualization.Gauge(document.getElementById(containerId + index));
      chart.draw(data, options);

      // Add title for chart, Gauge don't support "title" option.
      $('#' + containerId + index).prepend('<h5 class="chart-title">' + title + '</h5>');
    }
  }
  else {
    self.prepareData();
    chart = new google.visualization.Gauge(chartContainer);
    chart.draw(self.dataTable, options);
  }
};

}(jQuery));
