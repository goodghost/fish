<?php

/**
 * Class holding blog posts fetched from service as objects.
 */
class BlogPost {
  public $id;
  public $title;
  public $author;
  public $date;
  public $excerpt;
  public $thumbnail;
  public $link;

  /**
   * Constructor for blog post.
   */
  public function __construct($id, $title, $excerpt, $link, DateTime $date, $author, $thumbnail = NULL) {
    $this->setId($id);
    $this->setTitle($title);
    $this->setExcerpt($excerpt);
    $this->setLink($link);
    $this->setDate($date);
    $this->setAuthor($author);
    $this->setThumbnail($thumbnail);
    $this->setThumbnail($thumbnail);
  }

  /**
   * @param mixed $id
   */
  public function setId($id)
  {
    $this->id = $id;
  }

  /**
   * @return mixed
   */
  public function getId()
  {
    return $this->id;
  }



  /**
   * @param mixed $excerpt
   */
  public function setExcerpt($excerpt)
  {
    $this->excerpt = $excerpt;
  }

  /**
   * @return mixed
   */
  public function getExcerpt()
  {
    return $this->excerpt;
  }

  /**
   * @param mixed $link
   */
  public function setLink($link)
  {
    $this->link = $link;
  }

  /**
   * @return mixed
   */
  public function getLink()
  {
    return $this->link;
  }

  /**
   * @param mixed $thumbnail
   */
  public function setThumbnail($thumbnail)
  {
    $this->thumbnail = $thumbnail;
  }

  /**
   * @return mixed
   */
  public function getThumbnail()
  {
    return $this->thumbnail;
  }

  /**
   * @param mixed $title
   */
  public function setTitle($title)
  {
    $this->title = $title;
  }

  /**
   * @return mixed
   */
  public function getTitle()
  {
    return $this->title;
  }

  /**
   * @param mixed $author
   */
  public function setAuthor($author)
  {
    $this->author = $author;
  }

  /**
   * @return mixed
   */
  public function getAuthor()
  {
    return $this->author;
  }

  /**
   * @param mixed $date
   */
  public function setDate($date)
  {
    $this->date = $date;
  }

  /**
   * @return mixed
   */
  public function getDate()
  {
    return $this->date;
  }



}
