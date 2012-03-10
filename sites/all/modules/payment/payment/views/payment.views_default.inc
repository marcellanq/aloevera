<?php

/**
 * @file Default views.
 */

/**
 * Implements hook_views_default_views().
 */
function payment_views_default_views() {
  $views = array();

  $view_payments = payment_view_payments();
  $views[$view_payments->name] = $view_payments;
  $view_payment_methods = payment_view_payment_methods();
  $views[$view_payment_methods->name] = $view_payment_methods;

  return $views;
}

/**
 * Return the payment overview view.
 *
 * @return view
 */
function payment_view_payments() {
  $view = new view;
  $view->name = 'payments';
  $view->description = 'List all payments made using Payment module.';
  $view->tag = 'payment';
  $view->base_table = 'payment';
  $view->human_name = 'Payments';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Payments';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'payment.view.own';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'updated' => 'updated',
    'currency_code' => 'currency_code',
    'amount' => 'amount',
    'title_specific' => 'title_specific',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'updated' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'currency_code' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'amount' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title_specific' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 1;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no payments yet.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Relationship: Payment: Payment method ID */
  $handler->display->display_options['relationships']['pmid']['id'] = 'pmid';
  $handler->display->display_options['relationships']['pmid']['table'] = 'payment';
  $handler->display->display_options['relationships']['pmid']['field'] = 'pmid';
  $handler->display->display_options['relationships']['pmid']['required'] = 0;
  /* Field: Payment: Last updated date and time */
  $handler->display->display_options['fields']['updated']['id'] = 'updated';
  $handler->display->display_options['fields']['updated']['table'] = 'payment';
  $handler->display->display_options['fields']['updated']['field'] = 'updated';
  $handler->display->display_options['fields']['updated']['label'] = 'Last updated';
  $handler->display->display_options['fields']['updated']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['external'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['updated']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['updated']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['html'] = 0;
  $handler->display->display_options['fields']['updated']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['updated']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['updated']['hide_empty'] = 0;
  $handler->display->display_options['fields']['updated']['empty_zero'] = 0;
  $handler->display->display_options['fields']['updated']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['updated']['date_format'] = 'long';
  /* Field: Payment: Currency code */
  $handler->display->display_options['fields']['currency_code']['id'] = 'currency_code';
  $handler->display->display_options['fields']['currency_code']['table'] = 'payment';
  $handler->display->display_options['fields']['currency_code']['field'] = 'currency_code';
  $handler->display->display_options['fields']['currency_code']['label'] = '';
  $handler->display->display_options['fields']['currency_code']['exclude'] = TRUE;
  $handler->display->display_options['fields']['currency_code']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['external'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['currency_code']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['currency_code']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['html'] = 0;
  $handler->display->display_options['fields']['currency_code']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['currency_code']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['currency_code']['hide_empty'] = 0;
  $handler->display->display_options['fields']['currency_code']['empty_zero'] = 0;
  $handler->display->display_options['fields']['currency_code']['hide_alter_empty'] = 0;
  /* Field: Payment: Amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'payment';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  $handler->display->display_options['fields']['amount']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['amount']['alter']['text'] = '[currency_code] [amount]';
  $handler->display->display_options['fields']['amount']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['external'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['amount']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['amount']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['html'] = 0;
  $handler->display->display_options['fields']['amount']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['amount']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['amount']['hide_empty'] = 0;
  $handler->display->display_options['fields']['amount']['empty_zero'] = 0;
  $handler->display->display_options['fields']['amount']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['amount']['format_plural'] = 0;
  /* Field: Payment method: Title (specific) */
  $handler->display->display_options['fields']['title_specific']['id'] = 'title_specific';
  $handler->display->display_options['fields']['title_specific']['table'] = 'payment_method';
  $handler->display->display_options['fields']['title_specific']['field'] = 'title_specific';
  $handler->display->display_options['fields']['title_specific']['relationship'] = 'pmid';
  $handler->display->display_options['fields']['title_specific']['label'] = 'Payment method';
  $handler->display->display_options['fields']['title_specific']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title_specific']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title_specific']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title_specific']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title_specific']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title_specific']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title_specific']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title_specific']['hide_alter_empty'] = 0;
  /* Field: Payment method: Title (generic) */
  $handler->display->display_options['fields']['title_generic']['id'] = 'title_generic';
  $handler->display->display_options['fields']['title_generic']['table'] = 'payment_method';
  $handler->display->display_options['fields']['title_generic']['field'] = 'title_generic';
  $handler->display->display_options['fields']['title_generic']['relationship'] = 'pmid';
  /* Field: Payment: Operations */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'payment';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['external'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['html'] = 0;
  $handler->display->display_options['fields']['operations']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['operations']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['operations']['hide_empty'] = 0;
  $handler->display->display_options['fields']['operations']['empty_zero'] = 0;
  $handler->display->display_options['fields']['operations']['hide_alter_empty'] = 1;
  /* Sort criterion: Payment: Last updated date and time */
  $handler->display->display_options['sorts']['updated']['id'] = 'updated';
  $handler->display->display_options['sorts']['updated']['table'] = 'payment';
  $handler->display->display_options['sorts']['updated']['field'] = 'updated';
  $handler->display->display_options['sorts']['updated']['order'] = 'DESC';

  /* Display: Administration page */
  $handler = $view->new_display('page', 'Administration page', 'page_1');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'payment.view.all';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Payment: Last updated date and time */
  $handler->display->display_options['fields']['updated']['id'] = 'updated';
  $handler->display->display_options['fields']['updated']['table'] = 'payment';
  $handler->display->display_options['fields']['updated']['field'] = 'updated';
  $handler->display->display_options['fields']['updated']['label'] = 'Last updated';
  $handler->display->display_options['fields']['updated']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['external'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['updated']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['updated']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['html'] = 0;
  $handler->display->display_options['fields']['updated']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['updated']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['updated']['hide_empty'] = 0;
  $handler->display->display_options['fields']['updated']['empty_zero'] = 0;
  $handler->display->display_options['fields']['updated']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['updated']['date_format'] = 'long';
  /* Field: Payment: Currency code */
  $handler->display->display_options['fields']['currency_code']['id'] = 'currency_code';
  $handler->display->display_options['fields']['currency_code']['table'] = 'payment';
  $handler->display->display_options['fields']['currency_code']['field'] = 'currency_code';
  $handler->display->display_options['fields']['currency_code']['label'] = '';
  $handler->display->display_options['fields']['currency_code']['exclude'] = TRUE;
  $handler->display->display_options['fields']['currency_code']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['external'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['currency_code']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['currency_code']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['html'] = 0;
  $handler->display->display_options['fields']['currency_code']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['currency_code']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['currency_code']['hide_empty'] = 0;
  $handler->display->display_options['fields']['currency_code']['empty_zero'] = 0;
  $handler->display->display_options['fields']['currency_code']['hide_alter_empty'] = 0;
  /* Field: Payment: Amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'payment';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  $handler->display->display_options['fields']['amount']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['amount']['alter']['text'] = '[currency_code] [amount]';
  $handler->display->display_options['fields']['amount']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['external'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['amount']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['amount']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['html'] = 0;
  $handler->display->display_options['fields']['amount']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['amount']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['amount']['hide_empty'] = 0;
  $handler->display->display_options['fields']['amount']['empty_zero'] = 0;
  $handler->display->display_options['fields']['amount']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['amount']['format_plural'] = 0;
  /* Field: Payment method: Title (specific) */
  $handler->display->display_options['fields']['title_specific']['id'] = 'title_specific';
  $handler->display->display_options['fields']['title_specific']['table'] = 'payment_method';
  $handler->display->display_options['fields']['title_specific']['field'] = 'title_specific';
  $handler->display->display_options['fields']['title_specific']['relationship'] = 'pmid';
  $handler->display->display_options['fields']['title_specific']['label'] = 'Payment method';
  $handler->display->display_options['fields']['title_specific']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title_specific']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title_specific']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title_specific']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title_specific']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title_specific']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title_specific']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title_specific']['hide_alter_empty'] = 0;
  /* Field: Payment: Operations */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'payment';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['external'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['html'] = 0;
  $handler->display->display_options['fields']['operations']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['operations']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['operations']['hide_empty'] = 0;
  $handler->display->display_options['fields']['operations']['empty_zero'] = 0;
  $handler->display->display_options['fields']['operations']['hide_alter_empty'] = 1;
  $handler->display->display_options['path'] = 'admin/content/payment';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Payments';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';

  /* Display: User's own payments */
  $handler = $view->new_display('page', 'User\'s own payments', 'page_2');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'payment.view.own';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Payment: Last updated date and time */
  $handler->display->display_options['fields']['updated']['id'] = 'updated';
  $handler->display->display_options['fields']['updated']['table'] = 'payment';
  $handler->display->display_options['fields']['updated']['field'] = 'updated';
  $handler->display->display_options['fields']['updated']['label'] = 'Last updated';
  $handler->display->display_options['fields']['updated']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['external'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['updated']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['updated']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['updated']['alter']['html'] = 0;
  $handler->display->display_options['fields']['updated']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['updated']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['updated']['hide_empty'] = 0;
  $handler->display->display_options['fields']['updated']['empty_zero'] = 0;
  $handler->display->display_options['fields']['updated']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['updated']['date_format'] = 'long';
  /* Field: Payment: Currency code */
  $handler->display->display_options['fields']['currency_code']['id'] = 'currency_code';
  $handler->display->display_options['fields']['currency_code']['table'] = 'payment';
  $handler->display->display_options['fields']['currency_code']['field'] = 'currency_code';
  $handler->display->display_options['fields']['currency_code']['label'] = '';
  $handler->display->display_options['fields']['currency_code']['exclude'] = TRUE;
  $handler->display->display_options['fields']['currency_code']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['external'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['currency_code']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['currency_code']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['currency_code']['alter']['html'] = 0;
  $handler->display->display_options['fields']['currency_code']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['currency_code']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['currency_code']['hide_empty'] = 0;
  $handler->display->display_options['fields']['currency_code']['empty_zero'] = 0;
  $handler->display->display_options['fields']['currency_code']['hide_alter_empty'] = 0;
  /* Field: Payment: Amount */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'payment';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  $handler->display->display_options['fields']['amount']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['amount']['alter']['text'] = '[currency_code] [amount]';
  $handler->display->display_options['fields']['amount']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['external'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['amount']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['amount']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['amount']['alter']['html'] = 0;
  $handler->display->display_options['fields']['amount']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['amount']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['amount']['hide_empty'] = 0;
  $handler->display->display_options['fields']['amount']['empty_zero'] = 0;
  $handler->display->display_options['fields']['amount']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['amount']['format_plural'] = 0;
  /* Field: Payment method: Title (generic) */
  $handler->display->display_options['fields']['title_generic']['id'] = 'title_generic';
  $handler->display->display_options['fields']['title_generic']['table'] = 'payment_method';
  $handler->display->display_options['fields']['title_generic']['field'] = 'title_generic';
  $handler->display->display_options['fields']['title_generic']['relationship'] = 'pmid';
  $handler->display->display_options['fields']['title_generic']['label'] = 'Payment method';
  $handler->display->display_options['fields']['title_generic']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title_generic']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title_generic']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title_generic']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title_generic']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title_generic']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title_generic']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title_generic']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title_generic']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title_generic']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title_generic']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title_generic']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title_generic']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title_generic']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title_generic']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title_generic']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title_generic']['hide_alter_empty'] = 1;
  /* Field: Payment: Operations */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'payment';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['external'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['html'] = 0;
  $handler->display->display_options['fields']['operations']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['operations']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['operations']['hide_empty'] = 0;
  $handler->display->display_options['fields']['operations']['empty_zero'] = 0;
  $handler->display->display_options['fields']['operations']['hide_alter_empty'] = 1;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Payment: User ID */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'payment';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['uid']['not'] = 0;
  $handler->display->display_options['path'] = 'user/%/payment';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Payments';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'user-menu';
  $translatables['payments'] = array(
    t('Master'),
    t('Payments'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('There are no payments yet.'),
    t('Payment method'),
    t('Last updated'),
    t('Amount'),
    t('[currency_code] [amount]'),
    t('.'),
    t(','),
    t('Title (generic)'),
    t('Operations'),
    t('Administration page'),
    t('User\'s own payments'),
    t('All'),
  );

  return $view;
}

/**
 * Return the payment method overview view.
 *
 * @return view
 */
function payment_view_payment_methods() {
  $view = new view;
  $view->name = 'payment_methods';
  $view->description = '';
  $view->tag = 'payment';
  $view->base_table = 'payment_method';
  $view->human_name = 'Payment methods';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Payment methods';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'payment.method.administer';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'pmid' => 'pmid',
    'title_generic' => 'title_generic',
    'controller_title' => 'controller_title',
    'nothing' => 'nothing',
    'nothing_1' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'pmid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'title_generic' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'controller_title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '<<>>',
    ),
    'nothing_1' => array(
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 1;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no payment methods yet.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Field: Payment method: Payment method ID */
  $handler->display->display_options['fields']['pmid']['id'] = 'pmid';
  $handler->display->display_options['fields']['pmid']['table'] = 'payment_method';
  $handler->display->display_options['fields']['pmid']['field'] = 'pmid';
  $handler->display->display_options['fields']['pmid']['label'] = '';
  $handler->display->display_options['fields']['pmid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['pmid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['pmid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['pmid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['pmid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['pmid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['pmid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['pmid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['pmid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['pmid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['pmid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['pmid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['pmid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['pmid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['pmid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['pmid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['pmid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['pmid']['hide_alter_empty'] = 0;
  $handler->display->display_options['fields']['pmid']['format_plural'] = 0;
  /* Field: Payment method: Title (specific) */
  $handler->display->display_options['fields']['title_specific']['id'] = 'title_specific';
  $handler->display->display_options['fields']['title_specific']['table'] = 'payment_method';
  $handler->display->display_options['fields']['title_specific']['field'] = 'title_specific';
  $handler->display->display_options['fields']['title_specific']['label'] = 'Title';
  $handler->display->display_options['fields']['title_specific']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title_specific']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title_specific']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title_specific']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title_specific']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title_specific']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title_specific']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title_specific']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title_specific']['hide_alter_empty'] = 0;
  /* Field: Payment method: Payment method type title */
  $handler->display->display_options['fields']['controller_title']['id'] = 'controller_title';
  $handler->display->display_options['fields']['controller_title']['table'] = 'payment_method';
  $handler->display->display_options['fields']['controller_title']['field'] = 'controller_title';
  $handler->display->display_options['fields']['controller_title']['label'] = 'Type';
  $handler->display->display_options['fields']['controller_title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['controller_title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['controller_title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['controller_title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['controller_title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['controller_title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['controller_title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['controller_title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['controller_title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['controller_title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['controller_title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['controller_title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['controller_title']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['controller_title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['controller_title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['controller_title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['controller_title']['hide_alter_empty'] = 0;
  /* Field: Payment method: Operations */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'payment_method';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['external'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['operations']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['operations']['alter']['html'] = 0;
  $handler->display->display_options['fields']['operations']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['operations']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['operations']['hide_empty'] = 0;
  $handler->display->display_options['fields']['operations']['empty_zero'] = 0;
  $handler->display->display_options['fields']['operations']['hide_alter_empty'] = 0;
  /* Sort criterion: Payment method: Title (specific) */
  $handler->display->display_options['sorts']['title_specific']['id'] = 'title_specific';
  $handler->display->display_options['sorts']['title_specific']['table'] = 'payment_method';
  $handler->display->display_options['sorts']['title_specific']['field'] = 'title_specific';

  /* Display: Administration page */
  $handler = $view->new_display('page', 'Administration page', 'page_1');
  $handler->display->display_options['path'] = 'admin/config/services/payment';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Payment';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Payment';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $translatables['payment_methods'] = array(
    t('Master'),
    t('Payment methods'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('There are no payment methods yet.'),
    t('.'),
    t(','),
    t('Title'),
    t('Type'),
    t('Operations'),
    t('Administration page'),
  );

  return $view;
}