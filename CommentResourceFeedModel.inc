<?php
// $Id$

class CommentResourceFeedModel implements ResourceTimeFeedModel {
  protected $comments = NULL;

  public function __construct($data) {
    $this->comments = $data;
  }

  public function current() {
    $comment = current($this->comments);
    if ($comment!==FALSE) {
      return new CommentResourceFeedModelItem($comment);
    }
    return FALSE;
  }

  public function key() {
    return key($this->comments);
  }

  public function next() {
    next($this->comments);
  }

  public function rewind() {
    reset($this->comments);
  }

  public function valid() {
    // It's safe to use current as there never should be a boolean
    // in the node array.
    return current($this->comments)!==FALSE;
  }
}

class CommentResourceFeedModelItem implements ResourceTimeFeedModelItem {
  protected $comment = NULL;

  public function __construct($data) {
    $this->comment = $data;
  }

  /**
   * Returns the comment subject
   *
   * @return string
   *  The title of the node
   */
  public function getName() {
    return $this->comment->subject;
  }

  /**
   * Returns the full comment
   */
  public function getDescription() {
    return $this->comment->comment;
  }

  /**
   * Returns the absolute url to the node
   *
   * @return string
   *  The node url
   */
  public function getUrl() {
    return url('node/' . $this->comment->nid, array(
      'absolute' => TRUE,
      'fragment' => 'comment-' . $this->comment->cid,
    ));
  }

  /**
   * Gets the comment timestamp
   *
   * @return int
   */
  public function getCreated() {
    return $this->comment->timestamp;
  }

  /**
   * Gets the comment timestamp
   *
   * @return int
   */
  public function getStarts() {
    return $this->comment->timestamp;
  }

  /**
   * Gets the comment timestamp
   *
   * @return int
   */
  public function getEnds() {
    return $this->comment->timestamp;
  }

  /**
   * Gets a associative array containing extra properties for the item.
   *
   * @return array
   *  The extra properties of the item as an array
   */
  public function getProperties() {
    return array();
  }
}
