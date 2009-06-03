<?php
// $Id$

class CommentQueryBuilder extends QueryBuilder {
  public function __construct($admin=FALSE) {
    $this->defaultFields = array('cid', 'pid', 'uid', 'name', 'timestamp', 'subject', 'comment');
    $this->rewriteSql = FALSE;
    $this->defaultOrderField = 'timestamp';

    $table = array(
      'cid' => array(
        'type' => 'int',
        'condition' => self::CONDITION_MATCH,
        'sortable' => FALSE,
      ),
      'pid' => array(
        'type' => 'int',
        'condition' => self::CONDITION_MATCH,
        'sortable' => FALSE,
      ),
      'nid' => array(
        'type' => 'int',
        'condition' => self::CONDITION_MATCH,
        'sortable' => FALSE,
        'column' => 'nid',
      ),
      'uid' => array(
        'type' => 'int',
        'condition' => self::CONDITION_MATCH,
        'sortable' => FALSE,
        'column' => 'uid',
      ),
      'status' => array(
        'type' => 'int',
        'condition' => self::CONDITION_MATCH,
        'sortable' => FALSE,
        'column' => 'status',
      ),
      'timestamp' => array(
        'type' => 'int',
        'condition' => self::CONDITION_RANGE,
        'sortable' => TRUE,
      ),
      'mail' => array(
        'condition' => self::CONDITION_MATCH,
      ),
      'format' => array(),
      'subject' => array(),
      'comment' => array(),
      'name' => array(),
      'thread' => array(),
      'homepage' => array(),
    );

    if ($admin) {
      $table['hostname'] = array(
        'condition' => self::CONDITION_MATCH,
      );
    }

    $this->add_table('c', '{comments} AS c', NULL, $table);
  }
}
