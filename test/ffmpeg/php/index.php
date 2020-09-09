<?php
require "./routes/stream.php";

$uri = parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH);
$uri = explode('/', $uri);
// $method = $_SERVER['REQUEST_METHOD'];
//Allow CORS
header("Access-Control-Allow-Orgin: *");
header("Access-Control-Allow-Methods: *");

$route = $uri[3];
switch ($route) {
    case 'streams':
        $router = new StreamRouter();
        break;
    default:
}

// $videoId;
// if (isset($uri[3])) {
//     $videoId = $uri[3];
// } else {
//     $videoId = 15;
// }
// $streaming = new Stream();
// $streaming->getStream($videoId);
