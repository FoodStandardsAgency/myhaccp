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
  $handler->display->display_options['filters']['field_contact_consent_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/user-profiles';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'User Profiles';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['user_profiles'] = $view;

  return $export;
}
