/**
 * @file
 * Pie chart functionality.
 */

(function ($) {

// Function for generating pie chart.
Drupal.GoogleChart.prototype.renderPieChart = function() {
  var self = this;
  var chart;
  var relativeSize = Drupal.fr.dataset.relativeFontSize(self.displaySettings.font_size);

  // Set colors of columns.
  var i = 0,
    columnColors = [],
    fontStyle = [];

  self.prepareDataPieChart();

  // Set font style.
  switch (self.displaySettings.font_style) {
    case '1': fontStyle.push(true, false); break;
    case '2': fontStyle.push(false, true); break;
    case '3': fontStyle.push(true, true); break;
    default: fontStyle.push(false, false);
  }

  for (var key in self.displaySettings.slices_colors) {
    if (self.displaySettings.slices_colors.hasOwnProperty(key)) {
      if (i != 0) {
        columnColors.push(self.displaySettings.slices_colors[key]);
      }
    }
    i++;
  }

  if (self.chartData[0].length > 2) {
    // Remove ajax throbber.
    $container.html('');

    for (var j = 0; j < self.chartData.length; j++) {
      var optionsMulti = {
        fontSize: relativeSize,
        chartArea : {
          width: self.displaySettings.chart_area.width ? self.displaySettings.chart_area.width + '%' : '95%',
          height: self.displaySettings.chart_area.height ? self.displaySettings.chart_area.height + '%' : '60%',
          top: self.displaySettings.chart_area.top ? self.displaySettings.chart_area.top + '%' : '5%',
          left: self.displaySettings.chart_area.left ? self.displaySettings.chart_area.left + '%' : 'auto'
        },
        title: self.chartData[j][0].value,
        titleTextStyle : { color : self.displaySettings.textcolor ? self.displaySettings.textcolor : '#ffffff'},
        backgroundColor: self.displaySettings.background ? self.displaySettings.background : 'transparent',
        is3D: self.displaySettings.is_third_dim == 1,
        legend: {
          textStyle: {
            color: self.displaySettings.textcolor ? self.displaySettings.textcolor : '#ffffff',
            bold: fontStyle[0],
            italic: fontStyle[1]
          },
          position: self.displaySettings.legend_position ? self.displaySettings.legend_position: 'bottom',
          alignment: 'center'
        },
        colors: columnColors
      };
      $container.parent().addClass('dataset-visualisation-multichart');
      $container.append('<div class="dataset-visualisation-subchart" id="' + self.containerId + j + '"></div>');
      chart = new google.visualization.PieChart(document.getElementById(self.containerId + j));
      chart.draw(self.dataTable, optionsMulti);
    }
  }
  else if (self.chartData[0].length == 2) {
    // Chart options.
    var options = {
      fontSize: relativeSize,
      chartArea : { 
        width: self.displaySettings.chart_area.width ? self.displaySettings.chart_area.width + '%' : '95%',
        height: self.displaySettings.chart_area.height ? self.displaySettings.chart_area.height + '%' : '60%',
        top: self.displaySettings.chart_area.top ? self.displaySettings.chart_area.top + '%' : '5%',
        left: self.displaySettings.chart_area.left ? self.displaySettings.chart_area.left + '%' : 'auto'
      },
      backgroundColor: self.displaySettings.background ? self.displaySettings.background : 'transparent',
      is3D: self.displaySettings.is_third_dim == 1,
      legend: {
        textStyle: {
          color: self.displaySettings.textcolor ? self.displaySettings.textcolor : '#ffffff',
          bold: fontStyle[0],
          italic: fontStyle[1]
        },
        position: self.displaySettings.legend_position ? self.displaySettings.legend_position: 'bottom',
        alignment: 'center'
      }
    };

    chart = new google.visualization.PieChart(document.getElementById(self.containerId));
    chart.draw(self.dataTable, options);
  }
};

// Prepare data for pie chart.
Drupal.GoogleChart.prototype.prepareDataPieChart = function() {
  var self = this;
  this.dataTable = new google.visualization.DataTable();

  // Add data for chart for more then two columns.
  if (self.chartData[0].length > 2) {
    for (var i = 0; i < self.chartData.length; i++) {
      self.dataTable.addColumn('string');
      self.dataTable.addColumn('number');
      for (var innerIndex = 0; innerIndex < self.chartData[0].length; innerIndex++) {
        if (Drupal.GoogleChart.dataTypes[self.chartData[i][innerIndex].type] == 'number') {
          self.dataTable.addRow([self.chartData[i][innerIndex].name, self.chartData[i][innerIndex].value]);
        }
      }
    }
  }
  // Add data for chart for two or less columns.
  else if (self.chartData[0].length == 2) {
    self.dataTable.addColumn('string');
    self.dataTable.addColumn('number');

    for (var j = 0, l = self.chartData.length; j < l; j++) {
      self.chartData[j].sort(function (a, b) {
        if (Drupal.GoogleChart.dataTypes[b.type] == 'string') return 1;
        if (Drupal.GoogleChart.dataTypes[a.type] == 'string') return -1;
        return 0;
      });
    }
    for (var k = 0; k < self.chartData.length; k++) {
      self.dataTable.addRow([self.chartData[k][0].value, self.chartData[k][1].value]);
    }
  }
};

}(jQuery));
