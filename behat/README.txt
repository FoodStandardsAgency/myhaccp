Run composer install
Create a behat.yml file with something like the following:

default:
  paths:
    features: 'features'
  extensions:
    Behat\MinkExtension\Extension:
      goutte: ~
      selenium2: ~
      zombie: ~
      base_url: http://l.myhaccp
      files_path: ./test_files
    Drupal\DrupalExtension\Extension:
      api_driver: "drupal"
      blackbox: ~
      drush:
        root: ../web
      drupal:
        drupal_root: ../web

The above paths assume you'll be running this inside your vagrant box.
If this isn't the case then adjust the paths to suit.
