#pragma once

class HttpServer
{
private:
    int port = 0;
    int server_fd = 0;
    int isStop = 0;

public:
    HttpServer(int port);
    void start();
    void stop();
    ~HttpServer();
};