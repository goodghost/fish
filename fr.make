; Drupal make file
core = 7.x
api = 2

; Default settings
defaults[projects][subdir] = contrib

; Drupal core
projects[drupal][version] = 7.34
projects[drupal][subdir] = ""

; Contrib modules
projects[auto_nodetitle] = 1.0

projects[admin_views] = 1.3

projects[addressfield] = 1.0

projects[field_permissions] = 1.0-beta2

projects[ctools] = 1.6

projects[content_lock] = 2.0
; Add suppport for entity translation.
projects[content_lock][patch][2348499] = https://www.drupal.org/files/issues/content_lock-entity-translation-support-2348499-3.patch

projects[coffee] = 2.x
; Remove dependency on menu module
projects[coffee][patch][coffee] = https://www.drupal.org/files/issues/remove_dependency_on-2413123-1.patch

projects[date] = 2.8

projects[draggableviews][download][type] = git
projects[draggableviews][download][url] = http://git.drupal.org/project/draggableviews.git
projects[draggableviews][download][revision] = 4f5ac4ca6eaef98d9ccf28b715eeaa2548306ccd
projects[draggableviews][download][branch] = 7.x-2.x
; Intorduces Taxonomy Term ordering using weight property as opposed to custom field
projects[draggableviews][patch][1716912] = http://drupal.org/files/1716912.draggableviews.taxo-term-weight-handler.patch

projects[devel] = 1.5

projects[diff] = 3.2

projects[elements] = 1.4

projects[entity] = 1.5
projects[entity][patch][entity_field_property_callback-1312374-23] = https://www.drupal.org/files/issues/entity_field_property_callback-1312374-23.patch

projects[entity_translation] = 1.0-beta3

projects[email] = 1.3

projects[title][download][type] = git
projects[title][download][url] = http://git.drupal.org/project/title.git
projects[title][download][revision] = 32e80163c1c74a777582f81108fa2139f5ad9002
projects[title][download][branch] = 7.x-1.x

projects[entityreference] = 1.1

projects[entityreference_view_widget] = 2.0-rc6

projects[features] = 2.3

projects[field_collection] = 1.0-beta8
projects[field_collection][patch][2384323] = https://www.drupal.org/files/issues/2384323-16-dont-try-to-delete-missing-items.patch

projects[field_group] = 1.4

projects[file_entity] = 2.0-beta1

projects[geofield] = 2.3

projects[geophp] = 1.7

projects[http_client] = 2.4

projects[jquery_update] = 3.0-alpha2

projects[libraries] = 2.2

projects[link] = 1.3

projects[media] = 2.0-alpha4

projects[mediaelement] = 1.2

projects[memcache] = 1.2

projects[migrate] = 2.6-rc1

projects[migrate_extras] = 2.5

projects[navbar] = 1.5

projects[og] = 2.7

; Includes patch for https://www.drupal.org/node/1621014
projects[panels][download][type] = git
projects[panels][download][url] = http://git.drupal.org/project/panels.git
projects[panels][download][revision] = ed2063d46b61502707cf09c976a93cf1ef938412
projects[panels][download][branch] = 7.x-3.x

projects[panelizer] = 3.1

projects[roleassign] = 1.0

projects[services] = 3.11

projects[search_krumo] = 1.5

projects[strongarm] = 2.0

projects[telephone] = 1.0-alpha1

projects[token] = 1.5

projects[views] = 3.8

projects[views_bulk_operations] = 3.2

projects[webform] = 4.1

projects[webform_layout] = 2.2

projects[wysiwyg][download][type] = git
projects[wysiwyg][download][url] = http://git.drupal.org/project/wysiwyg.git
projects[wysiwyg][download][revision] = 5f2268b7e4fec58746e2cd19f1824dafcff877e3
projects[wysiwyg][download][branch] = 7.x-2.x


; Themes
projects[shiny][version] = 1.6
projects[shiny][type] = theme


; Libraries

libraries[ckeditor][download][type] = file
libraries[ckeditor][download][url] = http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.3.4/ckeditor_4.3.4_full.zip

libraries[jquery_lazyload][download][type] = file
libraries[jquery_lazyload][download][url] = https://github.com/tuupola/jquery_lazyload/archive/1.9.3.tar.gz

libraries[photoswipe][download][type] = file
libraries[photoswipe][download][url] = https://github.com/dimsemenov/PhotoSwipe/archive/v4.0.7.tar.gz

libraries[mediaelement][download][type] = file
libraries[mediaelement][download][url] = https://github.com/johndyer/mediaelement/archive/2.16.4.zip

libraries[jquery_timepicker_addon][download][type] = file
libraries[jquery_timepicker_addon][download][url] = https://github.com/trentrichardson/jQuery-Timepicker-Addon/archive/v1.5.5.zip

; Libraries required by navbar module

libraries[backbone][download][type] = file
libraries[backbone][download][url] = https://github.com/jashkenas/backbone/archive/1.1.0.zip

libraries[modernizr][download][type] = file
libraries[modernizr][download][url] = https://github.com/Modernizr/Modernizr/archive/v2.7.2.zip

libraries[underscore][download][type] = file
libraries[underscore][download][url] = https://github.com/jashkenas/underscore/archive/1.5.2.zip
