<?php

/**
 * @file
 * Definition of fr_user_views_handler_filter_user_remote.
 */

/**
 * Filter by remote property in data column.
 *
 * @ingroup views_filter_handlers
 */
class fr_user_views_handler_filter_user_remote extends views_handler_filter_boolean_operator {

  function query() {
    $table = $this->ensure_my_table();
    $this->query->add_field($table, 'data', 'fr_user_data');
  }

  function post_execute(&$values) {
    $value = $this->options['value'];

    foreach ($values as $index => $row) {
      $data = $row->fr_user_data;
      $is_remote = FALSE;
      if (!empty($data)) {
        $data = unserialize($data);
        $is_remote = !empty($data['remote']);
      }
      if ($is_remote != $value) {
        unset($values[$index]);
      }
    }
  }

}
