#include <stdio.h>
#include "HttpServer.h"

int main(int argc, char const *argv[]) {
    HttpServer *server = new HttpServer(8080);
    server->start();
    printf("Hello World!\n");
    return 0;
}
