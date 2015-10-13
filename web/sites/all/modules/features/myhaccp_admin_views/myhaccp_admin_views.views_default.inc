<?php
/**
 * @file
 * myhaccp_admin_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function myhaccp_admin_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'registrations';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Registrations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'User Registrations';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    5 => '5',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'main' => 'main',
  );
  /* Field: COUNT(User: Active) */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'users';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['group_type'] = 'count';
  $handler->display->display_options['fields']['status']['label'] = 'Total user registrations in period';
  $handler->display->display_options['fields']['status']['element_type'] = 'strong';
  $handler->display->display_options['fields']['status']['element_wrapper_type'] = 'h2';
  /* Field: COUNT(User: Name) */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['group_type'] = 'count';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Date: Date (users) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'users';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = 'between';
  $handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['label'] = 'Registration date';
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'users.created' => 'users.created',
  );
  /* Filter criterion: Profile: Business type (field_business_type) */
  $handler->display->display_options['filters']['field_business_type_value']['id'] = 'field_business_type_value';
  $handler->display->display_options['filters']['field_business_type_value']['table'] = 'field_data_field_business_type';
  $handler->display->display_options['filters']['field_business_type_value']['field'] = 'field_business_type_value';
  $handler->display->display_options['filters']['field_business_type_value']['relationship'] = 'profile';
  $handler->display->display_options['filters']['field_business_type_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_business_type_value']['expose']['operator_id'] = 'field_business_type_value_op';
  $handler->display->display_options['filters']['field_business_type_value']['expose']['label'] = 'Business type';
  $handler->display->display_options['filters']['field_business_type_value']['expose']['operator'] = 'field_business_type_value_op';
  $handler->display->display_options['filters']['field_business_type_value']['expose']['identifier'] = 'field_business_type_value';
  $handler->display->display_options['filters']['field_business_type_value']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_business_type_value']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_business_type_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/registrations';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Registrations';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['registrations'] = array(
    t('Master'),
    t('User Registrations'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Profile'),
    t('Total user registrations in period'),
    t('Name'),
    t('Registration date'),
    t('Business type'),
    t('Page'),
  );
  $export['registrations'] = $view;

  $view = new view();
  $view->name = 'user_profiles';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'profile';
  $view->human_name = 'User Profiles';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'User Profiles';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    5 => '5',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'pid' => 'pid',
    'field_business_type' => 'field_business_type',
    'field_postcode' => 'field_postcode',
    'field_size' => 'field_size',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'pid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_business_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_postcode' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_size' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Profile: User uid */
  $handler->display->display_options['relationships']['user']['id'] = 'user';
  $handler->display->display_options['relationships']['user']['table'] = 'profile';
  $handler->display->display_options['relationships']['user']['field'] = 'user';
  /* Field: Global: View result counter */
  $handler->display->display_options['fields']['counter']['id'] = 'counter';
  $handler->display->display_options['fields']['counter']['table'] = 'views';
  $handler->display->display_options['fields']['counter']['field'] = 'counter';
  $handler->display->display_options['fields']['counter']['label'] = 'Count';
  $handler->display->display_options['fields']['counter']['counter_start'] = '1';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'user';
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'user';
  /* Field: Profile: Business type */
  $handler->display->display_options['fields']['field_business_type']['id'] = 'field_business_type';
  $handler->display->display_options['fields']['field_business_type']['table'] = 'field_data_field_business_type';
  $handler->display->display_options['fields']['field_business_type']['field'] = 'field_business_type';
  /* Field: Profile: Business type (other) */
  $handler->display->display_options['fields']['field_business_other']['id'] = 'field_business_other';
  $handler->display->display_options['fields']['field_business_other']['table'] = 'field_data_field_business_other';
  $handler->display->display_options['fields']['field_business_other']['field'] = 'field_business_other';
  $handler->display->display_options['fields']['field_business_other']['label'] = 'Business type if other';
  /* Field: Profile: Size of business */
  $handler->display->display_options['fields']['field_size']['id'] = 'field_size';
  $handler->display->display_options['fields']['field_size']['table'] = 'field_data_field_size';
  $handler->display->display_options['fields']['field_size']['field'] = 'field_size';
  /* Field: Profile: Postcode area */
  $handler->display->display_options['fields']['field_postcode']['id'] = 'field_postcode';
  $handler->display->display_options['fields']['field_postcode']['table'] = 'field_data_field_postcode';
  $handler->display->display_options['fields']['field_postcode']['field'] = 'field_postcode';
  /* Field: Profile: I agree to the FSA contacting me for any research or surveys related to the use of this site. */
  $handler->display->display_options['fields']['field_contact_consent']['id'] = 'field_contact_consent';
  $handler->display->display_options['fields']['field_contact_consent']['table'] = 'field_data_field_contact_consent';
  $handler->display->display_options['fields']['field_contact_consent']['field'] = 'field_contact_consent';
  $handler->display->display_options['fields']['field_contact_consent']['label'] = 'Contact consent';
  $handler->display->display_options['fields']['field_contact_consent']['type'] = 'list_key';
  /* Filter criterion: Profile: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'profile';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'main' => 'main',
  );
  /* Filter criterion: Profile: I agree to the FSA contacting me for any research or surveys related to the use of this site. (field_contact_consent) */
  $handler->display->display_options['filters']['field_contact_consent_value']['id'] = 'field_contact_consent_value';
  $handler->display->display_options['filters']['field_contact_consent_value']['table'] = 'field_data_field_contact_consent';
  $handler->display->display_options['filters']['field_contact_consent_value']['field'] = 'field_contact_consent_value';
  $handler->display->display_options['filters']['field_contact_consent_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_contact_consent_value']['expose']['operator_id'] = 'field_contact_consent_value_op';
  $handler->display->display_options['filters']['field_contact_consent_value']['expose']['label'] = 'I agree to the FSA contacting me for any research or surveys related to the use of this site. (field_contact_consent)';
  $handler->display->display_options['filters']['field_contact_consent_value']['expose']['operator'] = 'field_contact_consent_value_op';
  $handler->display->display_options['filters']['field_contact_consent_value']['expose']['identifier'] = 'field_contact_consent_value';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10, 50, 100, 500';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['content'] = 'Note that the CSV export below will only export users who have consented to be contacted.';
  $handler->display->display_options['footer']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Profile: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'profile';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'main' => 'main',
  );
  /* Filter criterion: Profile: I agree to the FSA contacting me for any research or surveys related to the use of this site. (field_contact_consent) */
  $handler->display->display_options['filters']['field_contact_consent_value']['id'] = 'field_contact_consent_value';
  $handler->display->display_options['filters']['field_contact_consent_value']['table'] = 'field_data_field_contact_consent';
  $handler->display->display_options['filters']['field_contact_consent_value']['field'] = 'field_contact_consent_value';
  $handler->display->display_options['filters']['field_contact_consent_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_contact_consent_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_contact_consent_value']['expose']['operator_id'] = 'field_contact_consent_value_op';
  $handler->display->display_options['filters']['field_contact_consent_value']['expose']['label'] = 'User consents to contact';
  $handler->display->display_options['filters']['field_contact_consent_value']['expose']['operator'] = 'field_contact_consent_value_op';
  $handler->display->display_options['filters']['field_contact_consent_value']['expose']['identifier'] = 'field_contact_consent_value';
  $handler->display->display_options['filters']['field_contact_consent_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['path'] = 'admin/reports/user-profiles';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'User Profiles';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = 'myhaccp-user-profiles-%timestamp-full.csv';
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['style_options']['quote'] = 1;
  $handler->display->display_options['style_options']['trim'] = 0;
  $handler->display->display_options['style_options']['replace_newlines'] = 0;
  $handler->display->display_options['style_options']['header'] = 1;
  $handler->display->display_options['style_options']['keep_html'] = 0;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Profile: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'profile';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'main' => 'main',
  );
  /* Filter criterion: Profile: I agree to the FSA contacting me for any research or surveys related to the use of this site. (field_contact_consent) */
  $handler->display->display_options['filters']['field_contact_consent_value']['id'] = 'field_contact_consent_value';
  $handler->display->display_options['filters']['field_contact_consent_value']['table'] = 'field_data_field_contact_consent';
  $handler->display->display_options['filters']['field_contact_consent_value']['field'] = 'field_contact_consent_value';
  $handler->display->display_options['filters']['field_contact_consent_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_contact_consent_value']['expose']['operator_id'] = 'field_contact_consent_value_op';
  $handler->display->display_options['filters']['field_contact_consent_value']['expose']['label'] = 'I agree to the FSA contacting me for any research or surveys related to the use of this site. (field_contact_consent)';
  $handler->display->display_options['filters']['field_contact_consent_value']['expose']['operator'] = 'field_contact_consent_value_op';
  $handler->display->display_options['filters']['field_contact_consent_value']['expose']['identifier'] = 'field_contact_consent_value';
  $handler->display->display_options['path'] = 'admin/user_profiles/csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['use_batch'] = 'batch';
  $handler->display->display_options['segment_size'] = '100';
  $translatables['user_profiles'] = array(
    t('Master'),
    t('User Profiles'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('User'),
    t('Count'),
    t('Name'),
    t('E-mail'),
    t('Business type'),
    t('Business type if other'),
    t('Size of business'),
    t('Postcode area'),
    t('Contact consent'),
    t('I agree to the FSA contacting me for any research or surveys related to the use of this site. (field_contact_consent)'),
    t('Page'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Displaying @start - @end of @total'),
    t('Note that the CSV export below will only export users who have consented to be contacted.'),
    t('User consents to contact'),
    t('Data export'),
  );
  $export['user_profiles'] = $view;

  $view = new view();
  $view->name = 'users_by_access_time';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'profile';
  $view->human_name = 'Users by access time';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Users by access time';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    5 => '5',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'counter' => 'counter',
    'name' => 'name',
    'mail' => 'mail',
    'created' => 'created',
    'access' => 'access',
    'field_business_type' => 'field_business_type',
    'field_business_other' => 'field_business_other',
    'field_size' => 'field_size',
    'field_postcode' => 'field_postcode',
    'field_contact_consent' => 'field_contact_consent',
    'login' => 'login',
  );
  $handler->display->display_options['style_options']['default'] = 'access';
  $handler->display->display_options['style_options']['info'] = array(
    'counter' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mail' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'access' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_business_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_business_other' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_size' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_postcode' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_contact_consent' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'login' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Profile: User uid */
  $handler->display->display_options['relationships']['user']['id'] = 'user';
  $handler->display->display_options['relationships']['user']['table'] = 'profile';
  $handler->display->display_options['relationships']['user']['field'] = 'user';
  /* Field: Global: View result counter */
  $handler->display->display_options['fields']['counter']['id'] = 'counter';
  $handler->display->display_options['fields']['counter']['table'] = 'views';
  $handler->display->display_options['fields']['counter']['field'] = 'counter';
  $handler->display->display_options['fields']['counter']['label'] = 'Count';
  $handler->display->display_options['fields']['counter']['counter_start'] = '1';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'user';
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'user';
  /* Field: User: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['relationship'] = 'user';
  /* Field: Profile: Business type */
  $handler->display->display_options['fields']['field_business_type']['id'] = 'field_business_type';
  $handler->display->display_options['fields']['field_business_type']['table'] = 'field_data_field_business_type';
  $handler->display->display_options['fields']['field_business_type']['field'] = 'field_business_type';
  /* Field: Profile: Business type (other) */
  $handler->display->display_options['fields']['field_business_other']['id'] = 'field_business_other';
  $handler->display->display_options['fields']['field_business_other']['table'] = 'field_data_field_business_other';
  $handler->display->display_options['fields']['field_business_other']['field'] = 'field_business_other';
  $handler->display->display_options['fields']['field_business_other']['label'] = 'Business type if other';
  /* Field: Profile: Size of business */
  $handler->display->display_options['fields']['field_size']['id'] = 'field_size';
  $handler->display->display_options['fields']['field_size']['table'] = 'field_data_field_size';
  $handler->display->display_options['fields']['field_size']['field'] = 'field_size';
  /* Field: Profile: Postcode area */
  $handler->display->display_options['fields']['field_postcode']['id'] = 'field_postcode';
  $handler->display->display_options['fields']['field_postcode']['table'] = 'field_data_field_postcode';
  $handler->display->display_options['fields']['field_postcode']['field'] = 'field_postcode';
  /* Field: Profile: I agree to the FSA contacting me for any research or surveys related to the use of this site. */
  $handler->display->display_options['fields']['field_contact_consent']['id'] = 'field_contact_consent';
  $handler->display->display_options['fields']['field_contact_consent']['table'] = 'field_data_field_contact_consent';
  $handler->display->display_options['fields']['field_contact_consent']['field'] = 'field_contact_consent';
  $handler->display->display_options['fields']['field_contact_consent']['label'] = 'Contact consent';
  $handler->display->display_options['fields']['field_contact_consent']['type'] = 'list_key';
  /* Field: User: Last login */
  $handler->display->display_options['fields']['login']['id'] = 'login';
  $handler->display->display_options['fields']['login']['table'] = 'users';
  $handler->display->display_options['fields']['login']['field'] = 'login';
  $handler->display->display_options['fields']['login']['relationship'] = 'user';
  $handler->display->display_options['fields']['login']['date_format'] = 'html5_tools_iso8601';
  $handler->display->display_options['fields']['login']['second_date_format'] = 'html5_tools_iso8601';
  /* Field: User: Last access */
  $handler->display->display_options['fields']['access']['id'] = 'access';
  $handler->display->display_options['fields']['access']['table'] = 'users';
  $handler->display->display_options['fields']['access']['field'] = 'access';
  $handler->display->display_options['fields']['access']['relationship'] = 'user';
  $handler->display->display_options['fields']['access']['date_format'] = 'html5_tools_iso8601';
  $handler->display->display_options['fields']['access']['second_date_format'] = 'html5_tools_iso8601';
  /* Sort criterion: User: Last access */
  $handler->display->display_options['sorts']['access']['id'] = 'access';
  $handler->display->display_options['sorts']['access']['table'] = 'users';
  $handler->display->display_options['sorts']['access']['field'] = 'access';
  $handler->display->display_options['sorts']['access']['relationship'] = 'user';
  /* Filter criterion: Profile: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'profile';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'main' => 'main',
  );
  /* Filter criterion: Date: Date (users) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'users';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['relationship'] = 'user';
  $handler->display->display_options['filters']['date_filter']['operator'] = '<';
  $handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['label'] = 'Last Access';
  $handler->display->display_options['filters']['date_filter']['expose']['description'] = 'The table will show users who last accessed the site before the date entered';
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['date_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'users.access' => 'users.access',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10, 50, 100, 500';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['path'] = 'admin/reports/user-access';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'User by access time';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = 'myhaccp-user-profiles-%timestamp-full.csv';
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['style_options']['quote'] = 1;
  $handler->display->display_options['style_options']['trim'] = 0;
  $handler->display->display_options['style_options']['replace_newlines'] = 0;
  $handler->display->display_options['style_options']['header'] = 1;
  $handler->display->display_options['style_options']['keep_html'] = 0;
  $handler->display->display_options['path'] = 'admin/user_access/csv';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $handler->display->display_options['use_batch'] = 'batch';
  $handler->display->display_options['segment_size'] = '100';
  $translatables['users_by_access_time'] = array(
    t('Master'),
    t('Users by access time'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('User'),
    t('Count'),
    t('Name'),
    t('E-mail'),
    t('Created date'),
    t('Business type'),
    t('Business type if other'),
    t('Size of business'),
    t('Postcode area'),
    t('Contact consent'),
    t('Last login'),
    t('Last access'),
    t('Last Access'),
    t('The table will show users who last accessed the site before the date entered'),
    t('Page'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Displaying @start - @end of @total'),
    t('Data export'),
  );
  $export['users_by_access_time'] = $view;

  return $export;
}
