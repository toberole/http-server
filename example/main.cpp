#include <cstdio>
#include "HttpServer.h"

#include "HttpServlet.h"

class MyHttpServlet : public com::zw::HttpServlet {
    void doGet(com::zw::HttpServletRequest *request, com::zw::HttpServletResponse *response) {
        printf("doGet ......\n");
        doPost(request, response);
    }

    void doPost(com::zw::HttpServletRequest *request, com::zw::HttpServletResponse *response) {
        printf("doPost ......\n");
        response->setHeader("Content-Type", "text/html;charset=utf-8");
        response->setBody("hello world!");
        response->end();
    }
};

int main(int argc, char const *argv[]) {
    HttpServer *server = new HttpServer(8080);
    com::zw::HttpServlet *servlet = new MyHttpServlet();
    server->setRoute("/test/aaaa", servlet);
    server->start();
    printf("Hello World!\n");

    return 0;
}
