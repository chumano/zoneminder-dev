<?php
require "./controllers/stream.php";
require "./services/response.php";

class StreamRouter
{
    private $params;
    private $method;
    private $response;
    private $controller;

    public function __construct()
    {
        $this->response = new Response();
        $this->controller = new StreamController();
        $this->_processAPI();
    }

    private function _processAPI()
    {

        $this->params = explode('/', trim($_SERVER['PATH_INFO'], '/'));
        $this->method = $_SERVER['REQUEST_METHOD'];
        switch ($this->method) {
            case 'POST':
                // $this->params = $_POST;
                break;

            case 'GET':
                // Không cần nhận, bởi params đã được lấy từ url
                $parts = parse_url($_SERVER['REQUEST_URI']);
                $query = NULL;
                if (isset($parts['query']))
                    parse_str($parts['query'], $query);
                if (isset($this->params[1])) {
                    $result = $this->controller->getStreamWithId($this->params[1]);
                } else {
                    $result = $this->controller->getStream($query);
                }
                if ($result == 404) {
                    $this->response->response(404, "Can not find any video");
                } else {
                    $this->response->response(500, "Invalid Route");
                }
                // var_dump(get_class_methods($this->controller));
                break;

            case 'PUT':
                break;

            case 'DELETE':
                // Không cần nhận, bởi params đã được lấy từ url
                break;

            default:
                $this->response->response(500, "Invalid Method");
                break;
        }
    }
}
