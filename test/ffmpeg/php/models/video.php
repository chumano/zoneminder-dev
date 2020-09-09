<?php
class Video
{
    private $id;
    private $starttime;
    private $endtime;

    public function __construct($id, $starttime, $endtime)
    {
        $this->id = $id;
        $this->starttime = $starttime;
        $this->endtime = $endtime;
    }

    public function getId()
    {
        return $this->id;
    }

    public function getStartTime()
    {
        return $this->starttime;
    }

    public function getEndTime()
    {
        return $this->endtime;
    }
}
