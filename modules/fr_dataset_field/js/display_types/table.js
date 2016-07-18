/**
 * @file
 * Table functionality.
 */

(function ($) {

// Generate table
Drupal.GoogleChart.prototype.renderTable = function() {
  var self = this;
  var options = {
    allowHtml: true,
    cssClassNames: {
      headerRow: 'table-header',
      tableRow: 'even',
      oddTableRow: 'odd'
    }
  };

  // Add pagination.
  if (parseInt(self.displaySettings.page_size, 10) > 0) {
    options['page'] = 'enable';
    options['pageSize'] = parseInt(self.displaySettings.page_size, 10);
    options['pagingSymbols'] = {
      prev: Drupal.t('prev'),
      next: Drupal.t('next'),
    };
  }

  var chartWrapper = document.getElementById(self.containerId);
  var table = new google.visualization.Table(chartWrapper);
  var dataField;

  // Apply overridden values (icon or link).
  for (var row = 0; row < self.chartData.length; row++) {
    for (var column = 0; column < self.chartData[row].length; column++) {
      dataField = self.chartData[row][column];

      if (typeof dataField.overridden_value !== 'undefined') {
        dataField.value = dataField.overridden_value;
        dataField.type = 'string';
      }
    }
  }

  // Add event listener while sorting columns.
  // Add/remove "sorted" CSS class to sorted column cells.
  google.visualization.events.addListener(table, 'sort', sortCSSClass);

  function sortCSSClass(e) {
    var child = parseInt(e.column)+1;
    $('td.google-visualization-table-td', '#' + chartWrapper.id).removeClass('sorted');
    $('td.google-visualization-table-td:nth-child('+ child +')', '#' + chartWrapper.id).addClass('sorted');
  }

  self.prepareData();

  table.draw(self.dataTable, options);
};

}(jQuery));
