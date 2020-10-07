/*
 |--------------------------------------------------------------------------
 | Mix Asset Management
 |--------------------------------------------------------------------------
 |
 | Mix provides a clean, fluent API for defining some Webpack build steps
 | for your application. See https://github.com/JeffreyWay/laravel-mix.
 |
 */
const path = require("path");
const mix = require('laravel-mix');

/* Specify base_theme relative path */
const baseTheme = "../eua_theme/";
const baseThemePath = path.resolve(__dirname, baseTheme);

/* Live reloads URL pushing */
const proxy = 'http://drupal.local';

/*
 |--------------------------------------------------------------------------
 | Configuration
 |--------------------------------------------------------------------------
 */
mix.webpackConfig({
  resolve: {
    alias: {
      "eua_scss": `${baseThemePath}/resources/sass`,
      "@eua_js": `${baseThemePath}/resources/js`,
    },
  },
});

if (!mix.inProduction()) {
  // Enable source maps.
  // See https://www.drupal.org/project/radix/issues/3021020#comment-13116504
  mix
    .webpackConfig({
      devtool: 'source-map'
    })
    .sourceMaps();
}

/*
 |--------------------------------------------------------------------------
 | Configuration
 |--------------------------------------------------------------------------
 */
mix
  .setPublicPath('assets')
  .disableNotifications()
  .options({
    processCssUrls: false,
    postCss: [require("autoprefixer")],
  })
  .webpackConfig({
    module: {
      rules: [
        {
          test: /\.scss$/,
          loader: 'import-glob-loader',
        }
      ]
    }
  });

/*
 |--------------------------------------------------------------------------
 | Browsersync
 |--------------------------------------------------------------------------
 */
mix.browserSync({
  proxy: proxy,
  files: [
    'assets/js/**/*.js',
    'assets/css/**/*.css',
  ],
  stream: true,
});

/*
 |--------------------------------------------------------------------------
 | SASS
 |--------------------------------------------------------------------------
 */
mix.sass('resources/sass/EUA_SUBTHEME_MACHINE_NAME.style.scss', 'css');

// Bootstrap Ie11 support scss files:
// https://coliff.github.io/bootstrap-ie11/
mix.sass('./node_modules/bootstrap-ie11/scss/bootstrap-ie11.scss', 'css');

/*
 |--------------------------------------------------------------------------
 | JS
 |--------------------------------------------------------------------------
 */

// Load bootstrap globally
mix.autoload({
  'bootstrap': ['bootstrap'],
});

mix.js('resources/js/EUA_SUBTHEME_MACHINE_NAME.script.js', 'js');