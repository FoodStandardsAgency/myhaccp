<?php
/**
 * @file
 * Contains drush integration for cleanup.
 *
 * Alot of this is based on zen's drush integration, so send them the beer!
 * @see http://drupalcode.org/project/zen.git/blob/refs/heads/7.x-5.x:/zen-internals/zen.drush.inc
 */

/**
 * Implements hook_drush_command().
 */
function cleanup_drush_command() {
  $items = array();
  $items['cleanup'] = array(
    'description' => 'Create a cleanup sub-theme.',
    'arguments' => array(
      'name' => dt('The name of your sub-theme.'),
      'machine-name' => dt('[optional] A machine-readable name for your sub-theme.'),
    ),
    'options' => array(
      'name' => dt('The name of your sub-theme.'),
      'machine-name' => dt('A machine-readable name for your sub-theme.'),
      'description' => dt('A description for your sub-theme.'),
      'site-name' => dt('The sitename directory where you wish the sub-theme to be installed. Defaults to the sitename where cleanup itself is located.'),
    ),
    'examples' => array(
      'drush cleanup "Daughter of the cleanup"' => dt('Create a sub-theme called `Daughter of the cleanup` with the automatically generated machine name `daughter_of_the_cleanup`.'),
      'drush cleanup "Daughter of the cleanup" childship' => dt('Create a sub-theme called `Daughter of the cleanup` with the machine name `childship`.'),
      'drush cleanup "Daughter of the cleanup" childship --site-name=all' => dt('Create a sub-theme called `Daughter of the cleanup` in the sites/all/themes/childship.'),
    ),
  );
  return $items;
}

/**
 * Create a copy of NEWTHEME renamed to specified machine name together with
 * all other references to NEWTHEME.
 */
function drush_cleanup($name = NULL, $machine_name = NULL) {
  if (!isset($name)) {
    $name = drush_get_option('name');
  }

  // Figure out the machine name of the subtheme, either use the one passed by
  // the user or generate one from the name of the theme.
  if (!isset($machine_name)) {
    $machine_name = drush_get_option('machine-name');
  }
  if (!$machine_name) {
    $machine_name = $name;
  }
  $machine_name = drupal_clean_css_identifier(strtolower($machine_name), array(' ' => '_', '_' => '_', '/' => '', '[' => '', ']' => ''));

  $cleanup_path = drush_locate_root() . '/' . drupal_get_path('theme', 'cleanup');
  $newtheme_path = dirname($cleanup_path) . '/NEWTHEME';

  // Figure out the path to the subtheme, if a user didn't specify a sitename
  // directory use the same as cleanup itself.
  if ($site_name = drush_get_option('site-name')) {
    $subtheme_path = drush_locate_root() . '/sites/' . $site_name . '/themes/' . $machine_name;
    $subtheme_dir = dirname($subtheme_path);
    // Make sure the themes folder exist within the sitename directory.
    if (!is_dir($subtheme_dir)) {
      return drush_set_error('DRUSH_cleanup_COPY_DIR', dt('Destination directory !path does not exist. You have to create it.', array(
        '!path' => $subtheme_dir,
      )));
    }
  }
  // The user didn't provide a sitename so we extract it from where cleanup
  // itself is installed.
  else {
    $path = explode('/', $cleanup_path);
    $path = array_slice($path, 0, -2);
    $subtheme_path = implode('/', $path) . '/' . $machine_name;
  }

  // Create a renamed copy of cleanups example subtheme.
  if (!drush_copy_dir($newtheme_path, $subtheme_path)) {
    return drush_set_error('DRUSH_cleanup_COPY_DIR', dt('Subtheme generation failed, exiting.'));
  }

  $subtheme_info_file = $subtheme_path . '/' . $machine_name . '.info';
  // Activate the info file and rename it to the new machine name.
  drush_op('rename', $subtheme_path . '/NEWTHEME.info.example', $subtheme_info_file);
  // Rename all references to NEWTHEME and change the theme description if the
  // user provided an alternative.
  $alterations = array(
    'NEWTHEME' => $name
  );
  if ($description = drush_get_option('description')) {
    $alterations += array("= Hi im $name based on cleanup - you should really rename me :)" => "= $description");
  }
  drush_op('cleanup_file_str_replace', $subtheme_info_file, array_keys($alterations), $alterations);
  drush_op('cleanup_file_str_replace', $subtheme_path . '/template.php', 'NEWTHEME', $machine_name);

  drush_print(dt('cleanup subtheme "!name" created in: !path', array(
    '!name' => $name,
    '!path' => $subtheme_path,
  )));
  drush_print(dt('Visit your themes settings page and configure it to your liking: !path', array(
    '!path' => url('admin/appearance/settings/' . $machine_name, array('absolute' => TRUE)),
  )));
}

/**
 * Do string replacement within a specified file.
 */
function cleanup_file_str_replace($file_path, $find, $replace) {
  $file_contents = file_get_contents($file_path);
  $file_contents = str_replace($find, $replace, $file_contents);
  file_put_contents($file_path, $file_contents);
}
