
(function ($) {


// Google Chart manipulation object.
Drupal.GoogleChart = function(chartData, chartSettings) {
  this.chartData = chartData;
  this.chartSettings = chartSettings;
  this.datasetId = this.chartSettings.item.dataset;
  this.containerId = this.chartSettings.container_id;
  this.displaySettings = this.chartSettings.item.display_settings;
};

// Static variable to store current chart.
Drupal.GoogleChart.currentChart = {};

// Google chart data types mapping.
// Available types: string, number, boolean, date, datetime, and timeofday.
Drupal.GoogleChart.dataTypes = {
  'int': 'number',
  'double': 'number',
  'float': 'number',
  'string': 'string',
  'varchar': 'string',
  'bool': 'boolean',
  'tinyint': 'number',
  'date': 'string',
  'datetime': 'string',
  'timestamp': 'number'
};

// Static sort function to sort columns in dataset.
Drupal.GoogleChart.sortColumns = function(a, b) {
  var displaySettings = Drupal.GoogleChart.currentChart.displaySettings;
  if (b.name == displaySettings.x_field) {
    return 1;
  }
  if (a.name == displaySettings.x_field) {
    return -1;
  }
  return 0;
};

// Add columns to data table.
Drupal.GoogleChart.prototype.addColumns = function() {
  var fields = this.chartSettings.item.fields;
  var fieldLabel, fieldName;

  for (var i = 0; i < this.chartData[0].length; i++) {
    fieldName = this.chartData[0][i].name;
    if (typeof fields[fieldName] !== 'undefined' && fields[fieldName].label) {
      fieldLabel = fields[fieldName].label;
    }
    else {
      fieldLabel = fieldName;
    }
    this.dataTable.addColumn(Drupal.GoogleChart.dataTypes[this.chartData[0][i].type], fieldLabel);
  }
};

// Add rows to data table.
Drupal.GoogleChart.prototype.addRows = function() {
  if (this.chartData.length < 1) {
    return;
  }
  var tempArr = [];
  for (var j = 0; j < this.chartData.length; j++) {
    for (var innerIndex = 0; innerIndex < this.chartData[0].length; innerIndex++) {
      tempArr.push(this.chartData[j][innerIndex].value);
    }
    this.dataTable.addRows([tempArr]);
    tempArr = [];
  }
};

// Prepare data for chart.
Drupal.GoogleChart.prototype.prepareData = function() {
  this.dataTable = new google.visualization.DataTable();

  // Sort data to have an x = true set as first element.
  if (typeof this.displaySettings.x_field !== 'undefined') {
    Drupal.GoogleChart.currentChart = this;
    for (var i = 0, l = this.chartData.length; i < l; i++) {
      this.chartData[i].sort(Drupal.GoogleChart.sortColumns);
    }
  }

  this.addColumns();
  this.addRows();
};

// Render chart.
Drupal.GoogleChart.prototype.render = function() {
  switch (this.chartSettings.item.display_type) {
    case 'table':
      this.renderTable();
      break;

    case 'bar_chart':
      this.renderBarChart();
      break;

    case 'line_chart':
      this.renderLineChart();
      break;

    case 'pie_chart':
      this.renderPieChart();
      break;

    case 'gauge':
      this.renderGauge();
      break;

    default:
      this.renderTable();
  }
};

})(jQuery);
