<?php

/**
 * @file
 * Theme and preprocess functions for elements.
 */

use Drupal\Core\Render\Element;
use Drupal\eua_theme\Theme\EuaThemePreRender;

/**
 * Implements hook_element_info_alter().
 */
function eua_theme_element_info_alter(&$info) {
  if (isset($info['datetime'])) {
    $info['datetime']['#process'][] = '_eua_theme_process_element_grid_row';
  }

  if (isset($info['datelist'])) {
    $info['datelist']['#process'][] = '_eua_theme_process_element_grid_row';
  }

  // Add a pre-render function that handles checkbox variants.
  if (isset($info['checkbox'])) {
    $info['checkbox']['#pre_render'][] = [EuaThemePreRender::class, 'checkbox'];
  }

  // Add a pre-render function that handles checkboxes variants.
  if (isset($info['checkboxes'])) {
    $info['checkboxes']['#pre_render'][] = [EuaThemePreRender::class, 'checkboxes'];
  }
}

/**
 * Process callback for applying a grid on elements.
 *
 * @see eua_theme_element_info_alter
 */
function _eua_theme_process_element_grid_row(&$element) {
  $element['#attributes']['class'][] = 'row';
  foreach (Element::children($element) as $key) {
    $element[$key]['#col_class'] = 'col-auto';
  }
  return $element;
}