<?php
// $Id$

function _comment_resource_retrieve($cid) {
  global $user;
  $comment = _comment_load($cid);
  $admin = user_access('administer comments');

  if (!$admin && $comment->uid && $comment) {
    unset($comment->hostname);
    unset($comment->mail);
  }

  return $comment;
}

function _comment_resource_create($comment) {
  global $user;
  $comment = (array)$comment;
  unset($comment['status']);

  $admin = user_access('administer comments');

  if (!$admin || !isset($comment['uid'])) {
    $comment['uid'] = $user->uid;
  }
  if (!$admin || !isset($comment['name'])) {
    $comment['name'] = $user->name;
  }
  if (!$admin || !isset($comment['mail'])) {
    $comment['mail'] = $user->mail;
  }

  if (!isset($comment['format'])) {
    $comment['format'] = filter_resolve_format(FILTER_FORMAT_DEFAULT);
  }

  _comment_form_submit($comment);

  if ($cid = comment_save((array)$comment)) {
    return (object)array(
      'cid' => $cid,
      'uri' => services_resource_uri(array('comment', $cid)),
    );
  }
  return FALSE;
}

function _comment_resource_delete($cid) {
  module_load_include('admin.inc', 'comment');

  $comment = _comment_load($cid);
  _comment_delete_thread($comment);
  _comment_update_node_statistics($comment->nid);

  // Clear the cache so an anonymous users sees that the comment was deleted.
  cache_clear_all();
  return TRUE;
}

function _comment_resource_index() {
  return comment_get_recent(20);
}

function _comment_resource_node_index($nid, $page=0, $fields=array(), $parameters=array()) {
  $admin = user_access('administer comments');
  $builder = new CommentQueryBuilder($admin);

  if (is_string($fields)) {
    $fields = preg_split('/,\s?/', $fields);
  }

  $parameters['nid'] = $nid;
  // Add restrictions based on permissions
  if (!$admin || !isset($parameters['status'])) {
    $parameters['status'] = COMMENT_PUBLISHED;
  }

  list($sql, $params) = $builder->query($fields, $parameters);
  $res = db_query_range($sql, $params, $page*20, 20);

  $comments = array();
  while ($comment = db_fetch_object($res)) {
    $comment->uri = services_resource_uri(array('comment', $comment->cid));
    $comments[] = $comment;
  }
  return $comments;
}
