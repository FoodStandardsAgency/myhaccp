#!/bin/sh
#
# Cloud Hook
#


# Map the script inputs to convenient names.
site=$1
target_env=$2
drush_alias=$site'.'$target_env

# Enable the following modules.
drush @$drush_alias en -y shield

