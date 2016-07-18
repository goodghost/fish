<?php

/**
 * @file
 * Definition of views_handler_filter_node_type.
 */

/**
 * Filter by node type.
 *
 * @ingroup views_filter_handlers
 */
class views_handler_filter_operations extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Available operations');
      $this->value_options = fr_form_available_operations_options();
    }
  }
}