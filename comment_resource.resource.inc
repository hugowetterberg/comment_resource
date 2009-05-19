<?php
// $Id$

function _comment_resource_service_resource() {
  return array(
    'comment' => array(
      '#file' => array('file' => 'inc', 'module' => 'comment_resource'),
      '#retrieve' => array(
        '#callback' => '_comment_resource_retrieve',
        '#args' => array(
          array(
            '#name' => 'cid',
            '#optional' => FALSE,
            '#source' => array('path' => 0),
            '#type' => 'int',
            '#description' => 'The nid of the node to get',
          ),
        ),
        '#models' => array(
          'ResourceFeedModel' => array(
            'class' => 'CommentResourceFeedModel',
            'arguments' => array('source'=>'single'),
          ),
        ),
        '#access callback' => '_comment_resource_access',
        '#access arguments' => array('view'),
        '#access arguments append' => TRUE,
      ),
      '#create' => array(
        '#callback' => '_comment_resource_create',
        '#args' => array(
          array(
            '#name' => 'node',
            '#optional' => FALSE,
            '#source' => 'data',
            '#description' => 'The comment object to create',
            '#type' => 'struct',
          ),
        ),
        '#models' => array(
          'ResourceFeedModel' => array(
            'class' => 'CommentResourceFeedModel',
            'arguments' => array('source'=>'single'),
          ),
        ),
        '#access callback' => '_comment_resource_access',
        '#access arguments' => array('create'),
        '#access arguments append' => TRUE,
      ),
      '#delete' => array(
        '#callback' => '_comment_resource_delete',
        '#args' => array(
          array(
            '#name' => 'nid',
            '#optional' => FALSE,
            '#source' => array('path' => 0),
          ),
        ),
        '#access callback' => '_comment_resource_access',
        '#access arguments' => array('delete'),
        '#access arguments append' => TRUE,
      ),
      '#index' => array(
        '#callback' => '_comment_resource_index',
        '#args' => array(
        ),
        '#models' => array(
          'ResourceFeedModel' => array(
            'class' => 'CommentResourceFeedModel',
          ),
          'ResourceTimeFeedModel' => array(
            'class' => 'CommentResourceFeedModel',
          ),
        ),
        '#access arguments' => array('access content'),
        '#access arguments append' => TRUE,
      ),
    ),
  );
}

function _comment_resource_node_comments() {
  return array(
    '#file' => array('file' => 'inc', 'module' => 'comment_resource'),
    '#callback' => '_comment_resource_node_index',
    '#args' => array(
      array(
        '#name' => 'page',
        '#optional' => TRUE,
        '#type' => 'int',
        '#description' => 'The zero-based index of the page to get, defaults to 0.',
        '#default value' => 0,
        '#source' => array('param' => 'page'),
      ),
      array(
        '#name' => 'fields',
        '#optional' => TRUE,
        '#type' => 'array',
        '#description' => 'The fields to get.',
        '#default value' => 0,
        '#source' => array('param' => 'fields'),
      ),
      array(
        '#name' => 'params',
        '#optional' => TRUE,
        '#type' => 'struct',
        '#description' => 'Parameters for the query builder.',
        '#default value' => 0,
        '#source' => 'param',
      ),
    ),
    '#access callback' => '_comment_resource_node_comments_access',
    '#access arguments' => array(),
    '#access arguments append' => TRUE,
    '#models' => array(
      'ResourceFeedModel' => array(
        'class' => 'EventOccasionsFeedModel',
      ),
      'ResourceTimeFeedModel' => array(
        'class' => 'EventOccasionsFeedModel',
      ),
    ),
  );
}
