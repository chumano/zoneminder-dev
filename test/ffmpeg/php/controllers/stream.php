<?php
require "./services/stream.php";

class StreamController
{
    // private $params;
    private $services;

    public function __construct()
    {
        $this->services = new StreamServices();
    }

    public function getStreamWithId($videoid)
    {
        $result = $this->services->getVideoWithId($videoid);
        if ($result == 404)
            return 404;
    }

    public function getStream($query)
    {
        $result = $this->services->getVideoWithQuery($query);
        if ($result == 404)
            return 404;
    }
}
