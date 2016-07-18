<?php

// Plugin definition
$plugin = array(
  'title' => t('Two by two - grid'),
  'category' => t('Columns: 2'),
  'icon' => 'grid_two_by_two.png',
  'theme' => 'grid-two-by-two',
  'css' => 'grid_two_by_two.css',
  'regions' => array(
    'top-left' => t('Top left side'),
    'top-right' => t('Top right side'),
    'bottom-left' => t('Bottom left side'),
    'bottom-right' => t('Bottom right side'),
  ),
);
