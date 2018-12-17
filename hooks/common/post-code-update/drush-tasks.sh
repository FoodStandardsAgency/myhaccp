#!/bin/sh
#
# Cloud Hook
#
# Run drush tasks all in the target environment. This script works as
# any Cloud hook.


# Map the script inputs to convenient names.
site=$1
target_env=$2
drush_alias=$site'.'$target_env

# Update database schema.
drush @$drush_alias updb -y

if [ $target_env = "prod" ]; then
    # Clear all caches if the target environment is production.
    drush @$drush_alias cc all
else
    # Enable non-prod modules; clears caches as part of the process.
    drush @$drush_alias en -y stage_file_proxy shield
fi