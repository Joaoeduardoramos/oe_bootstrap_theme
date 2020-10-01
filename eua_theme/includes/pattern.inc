<?php

/**
 * @file
 * Theme and preprocess functions for patterns.
 */

/**
 * Implements hook_preprocess_HOOK() for badge_preview patterns.
 */
function eua_theme_preprocess_pattern_badge__preview(array &$variables) {
  if (strpos($variables['variant'], 'link__') === 0) {
    $variables['url'] = '#';
  }
}

/**
 * Implements hook_preprocess_HOOK() for page templates.
 */
function eua_theme_preprocess_page(&$variables) {
  // @TODO It would be better to have a setting, like bootstrap_barrio do with
  // bootstrap_barrio_fluid_container ('container-fluid' : 'container')
  $variables['container'] = 'container';
}

/**
 * Implements hook_preprocess_HOOK() for card patterns.
 */
function eua_theme_preprocess_pattern_card(array &$variables) {
  if (array_key_exists('image', $variables) && is_array($variables['image'])) {
    foreach ($variables['image'] as &$item) {
      _eua_theme_add_card_image_class($item, $variables['variant']);
    }
  }
  if (array_key_exists('links', $variables) && is_array($variables['links'])) {
    foreach ($variables['links'] as &$item) {
      _eua_theme_add_card_link_class($item);
    }
  }
}

/**
 * Add expected class in card's image.
 */
function _eua_theme_add_card_image_class(&$item, $variant) {
  $class = 'card-img-top';
  if ($variant === 'overlay') {
    $class = 'card-img';
  }
  if (is_array($item) && array_key_exists('#theme', $item)) {
    if ($item['#theme'] === 'image') {
      $item['#attributes']['class'][] = $class;
    }
    if ($item['#theme'] === 'image_formatter') {
      $item['#item_attributes']['class'][] = $class;
    }
  }
  if (is_array($item)) {
    foreach ($item as &$next) {
      _eua_theme_add_card_image_class($next, $variant);
    }
  }
}

/**
 * Add expected class in card's link.
 */
function _eua_theme_add_card_link_class(&$item) {
  $class = 'card-link';
  if (is_array($item) && array_key_exists('#type', $item)) {
    if ($item['#type'] === 'link') {
      $item['#attributes']['class'][] = $class;
    }
    if ($item['#type'] === 'html_tag' && $item['#tag'] === 'a') {
      $item['#attributes']['class'][] = $class;
    }
  }
  if (is_array($item)) {
    foreach ($item as &$next) {
      _eua_theme_add_card_link_class($next);
    }
  }
}

/**
 * Implements hook_preprocess_HOOK() for carousel patterns.
 */
function eua_theme_preprocess_pattern_carousel(array &$variables) {
  // Move first image of each slide in a specific array key.
  if (array_key_exists('slides', $variables) && is_array($variables['slides'])) {
    foreach ($variables['slides'] as &$slide) {
      $slide['image'] = _eua_theme_extract_carousel_image($slide);
    }
  }

  // Nicer preview with fixed width and local backgrounds.
  // if ($variables['context']->getType() == 'preview') {
  //  $variables['attributes']['style'] = "width: 800px";
  // }

}

/**
 * Extract image from carousel slide.
 */
function _eua_theme_extract_carousel_image(&$item) {
  if (is_array($item) && array_key_exists('#theme', $item)) {
    if ($item['#theme'] === 'image' || $item['#theme'] === 'image_formatter') {
      $image = $item;
      $item = [];
      return $image;
    }
  }
  if (isset($item) && is_array($item)) {
    foreach ($item as &$next) {
      $dig = _eua_theme_extract_carousel_image($next);
      if ($dig) {
        return $dig;
      }
    }
  }
  return FALSE;
}