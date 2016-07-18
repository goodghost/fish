/**
 * @file
 * Bar chart functionality.
 */

(function ($) {

// Function for generating bar chart.
Drupal.GoogleChart.prototype.renderBarChart = function() {
  var self = this,
      relativeSize = Drupal.fr.dataset.relativeFontSize(self.displaySettings.font_size);

  self.prepareData();

  //set font style
  var fontStyle = [];
  switch (self.displaySettings.font_style) {
    case '1': fontStyle.push(true, false); break;
    case '2': fontStyle.push(false, true); break;
    case '3': fontStyle.push(true, true); break;
    default: fontStyle.push(false, false);
  }

  //set colors of columns
  var columnColors = [];
  for (var key in self.displaySettings.bars_color) {
    if (self.displaySettings.bars_color.hasOwnProperty(key)) {
      if (key != self.displaySettings.x_field) {
        columnColors.push(self.displaySettings.bars_color[key]);
      }
    }
  }

  var options = {
    bar : { groupWidth: 61.8 * parseFloat(self.displaySettings.column_thickness) + "%", },
    fontSize : relativeSize,
    chartArea : { 
      width: self.displaySettings.chart_area.width ? self.displaySettings.chart_area.width + "%" : "95%",
      height: self.displaySettings.chart_area.height ? self.displaySettings.chart_area.height + "%" : "60%",
      top: self.displaySettings.chart_area.top ? self.displaySettings.chart_area.top + "%" : "5%",
      left: self.displaySettings.chart_area.left ? self.displaySettings.chart_area.left + "%" : "auto"
    },
    backgroundColor : self.displaySettings.background ? self.displaySettings.background : 'transparent',
    vAxis : { 
      textStyle : {
        color: self.displaySettings.textcolor ? self.displaySettings.textcolor : '#ffffff',
        bold : fontStyle[0], 
        italic : fontStyle[1]
      },
      title : self.displaySettings.title_vaxis,
      titleTextStyle : {
        color: self.displaySettings.textcolor ? self.displaySettings.textcolor : '#ffffff',
        bold : fontStyle[0], 
        italic : fontStyle[1]
      },
      viewWindow: {
        min: (self.displaySettings.min_axis_horizontal) ? self.displaySettings.min_axis_horizontal : 'pretty',
        max: (self.displaySettings.max_axis_horizontal) ? self.displaySettings.max_axis_horizontal : 'pretty'
      }
    },
    hAxis : { 
      textStyle : { 
        color: self.displaySettings.textcolor ? self.displaySettings.textcolor : '#ffffff',
        bold : fontStyle[0], 
        italic : fontStyle[1]
      },
      title : self.displaySettings.title_haxis,
      titleTextStyle : {
        color: self.displaySettings.textcolor ? self.displaySettings.textcolor : '#ffffff',
        bold : fontStyle[0], 
        italic : fontStyle[1]
      },
      viewWindow: {
        min: (self.displaySettings.min_axis_vertical) ? self.displaySettings.min_axis_vertical : 'pretty',
        max: (self.displaySettings.max_axis_vertical) ? self.displaySettings.max_axis_vertical : 'pretty'
      },
    },
    legend: { 
      position : (self.displaySettings.legend_position) ? self.displaySettings.legend_position : 'bottom',
      alignment  : 'center',
      textStyle: {
        color: self.displaySettings.textcolor ? self.displaySettings.textcolor : '#ffffff',
        bold : fontStyle[0], 
        italic : fontStyle[1]
      },
    },
    colors: columnColors,
  };
  var chart = new google.visualization.BarChart(document.getElementById(self.containerId));
  chart.draw(self.dataTable, options);
};

}(jQuery));
