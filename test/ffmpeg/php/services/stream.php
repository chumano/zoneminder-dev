<?php
require "./models/video.php";

class StreamServices
{
    private $file;
    private $listVideos;
    private $cppPath;

    public function __construct()
    {
        $this->cppPath = '/src/FFmpeg-Test/';
        $this->file = $this->cppPath . 'assets/';
        //init list of videos
        //Don't mind this, just hard code video starttime and endtime
        //Real thing should get this info from database
        $this->listVideos = array();
        $initStartTime = "2020-08-21 10:42:45";
        $initEndTime = "2020-08-21 10:43:42";
        for ($i = 15; $i < 19; $i++) {
            $video = new Video($i, $initStartTime, $initEndTime);
            array_push($this->listVideos, $video);
            $tempStartDatetime = explode(" ", $initStartTime);
            $tempStartTime = explode(":", $tempStartDatetime[1]);
            $tempStartTime[1] = (int)$tempStartTime[1] + 1;
            $tempStartDatetime[1] = implode(":", $tempStartTime);
            $initStartTime = implode(" ", $tempStartDatetime);
            $tempEndDatetime = explode(" ", $initEndTime);
            $tempEndTime = explode(":", $tempEndDatetime[1]);
            $tempEndTime[1] = (int)$tempEndTime[1] + 1;
            $tempEndDatetime[1] = implode(":", $tempEndTime);
            $initEndTime = implode(" ", $tempEndDatetime);
        }
    }

    public function getVideoWithId($videoId)
    {
        $this->file = $this->file . $videoId . "/" . $videoId . "-video.mp4";
        // var_dump($this->file);
        // echo nl2br("URI: $uri[1]\n");
        // echo nl2br("File: $this->file\n");
        $this->getStream();
    }

    public function getVideoWithQuery($query)
    {
        // var_dump($query);
        //this function only get the first video that match query condition
        // $result = $this->listVideos;
        // if (isset($query["starttime"])) {
        //     $startDate = new DateTime($query["starttime"]);
        //     $result = array_filter($result, function ($video) use ($startDate) {
        //         $videoStartTime = new DateTime($video->getStartTime());
        //         return $videoStartTime >= $startDate;
        //     });
        // }
        // if (isset($query["endtime"])) {
        //     $endDate =  new DateTime($query["endtime"]);
        //     $result = array_filter($result, function ($video) use ($endDate) {
        //         $videoEndTime = new DateTime($video->getEndTime());
        //         return $videoEndTime <= $endDate;
        //     });
        // }
        // if (count($result) > 0) {
        //     // var_dump(array_values($result)[0]->getId());
        //     $this->getVideoWithId(array_values($result)[0]->getId());
        // } else {
        //     return 404;
        // }
        $output = $this->cppPath . "output/output.mp4";
        $starttime = $query["starttime"];
        $endtime = $query["endtime"];
        // var_dump($this->cppPath . "main '$starttime' '$endtime' $output");
        exec($this->cppPath . "main '$starttime' '$endtime' $output", $result, $status);
        $this->file = $output;
        // sleep(2);
        // var_dump($this->file);
        // var_dump($output);
        // var_dump($result);
        // var_dump($status);
        $this->getStream();
    }

    public function getStream()
    {
        $fp = @fopen($this->file, 'rb');
        // var_dump($fp);
        // var_dump($this->file);
        if ($fp) {
            $size   = filesize($this->file); // File size
            $length = $size;           // Content length
            $start  = 0;               // Start byte
            $end    = $size - 1;       // End byte
            header('Content-type: video/mp4');
            //header("Accept-Ranges: 0-$length");
            header("Accept-Ranges: bytes");
            if (isset($_SERVER['HTTP_RANGE'])) {
                $c_start = $start;
                $c_end   = $end;
                list(, $range) = explode('=', $_SERVER['HTTP_RANGE'], 2);
                if (strpos($range, ',') !== false) {
                    header('HTTP/1.1 416 Requested Range Not Satisfiable');
                    header("Content-Range: bytes $start-$end/$size");
                    exit;
                }
                if ($range == '-') {
                    $c_start = $size - substr($range, 1);
                } else {
                    $range  = explode('-', $range);
                    $c_start = $range[0];
                    $c_end   = (isset($range[1]) && is_numeric($range[1])) ? $range[1] : $size;
                }
                $c_end = ($c_end > $end) ? $end : $c_end;
                if ($c_start > $c_end || $c_start > $size - 1 || $c_end >= $size) {
                    header('HTTP/1.1 416 Requested Range Not Satisfiable');
                    header("Content-Range: bytes $start-$end/$size");
                    exit;
                }
                $start  = $c_start;
                $end    = $c_end;
                $length = $end - $start + 1;
                fseek($fp, $start);
                header('HTTP/1.1 206 Partial Content');
            }
            header("Content-Range: bytes $start-$end/$size");
            header("Content-Length: " . $length);
            $buffer = 1024 * 8;
            while (!feof($fp) && ($p = ftell($fp)) <= $end) {
                if ($p + $buffer > $end) {
                    $buffer = $end - $p + 1;
                }
                set_time_limit(0);
                echo fread($fp, $buffer);
                flush();
            }
            fclose($fp);
            exit();
        } else {
            return 404;
        }
    }
}
