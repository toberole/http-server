#pragma once

#include <map>
#include "HttpServlet.h"

class HttpServer {
private:
    int port = 0;
    int server_fd = 0;
    int isStop = 0;

public:
    HttpServer(int port);

    void start();

    void setRoute(std::string path, com::zw::HttpServlet *httpServlet);

    void stop();

    ~HttpServer();
};