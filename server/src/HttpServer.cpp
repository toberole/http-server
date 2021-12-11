#include "HttpServer.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <netdb.h>
#include <cerrno>
#include <thread>

#include "http_parser.h"
#include "HttpServletRequest.h"
#include "HttpMsgHandler.h"
#include <sstream>

namespace {
    std::map<std::string, com::zw::HttpServlet *> g_route;
}

HttpServer::HttpServer(int port) : port(port) {
}

void HttpServer::setRoute(std::string path, com::zw::HttpServlet *httpServlet) {
    g_route.insert(std::make_pair(path, httpServlet));
}

void HttpServer::start() {
    int res = -1;
    do {
        server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (server_fd == -1) {
            printf("create socker ret: %d,error: %s\n", server_fd, strerror(errno));
            break;
        }

        sockaddr_in server_addr;
        bzero(&server_addr, sizeof(sockaddr_in));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        res = bind(server_fd, (struct sockaddr *) (&server_addr), sizeof(struct sockaddr));
        if (res != 0) {
            printf("bind res: %d,error: %s\n", res, strerror(errno));
            break;
        }

        res = listen(server_fd, 1024);
        if (res == -1) {
            printf("listen res: %d,error: %s\n", res, strerror(errno));
            break;
        }

        int client_fd;
        while (isStop != 1) {
            sockaddr_storage storage;
            socklen_t sock_len = sizeof(storage);
            client_fd = accept(server_fd, (sockaddr *) &storage, &sock_len);
            if (client_fd == -1) {
                printf("accept res: %d,error: %s\n", client_fd, strerror(errno));
                continue;
            } else {
                printf("...... welcome client start ......\n");

                if (storage.ss_family == AF_INET) {
                    sockaddr_in *addr = (sockaddr_in *) &storage;
                    char ip[INET_ADDRSTRLEN];
                    inet_ntop(AF_INET, &addr->sin_addr, ip, sock_len);
                    printf("client [%s:%d] \n", ip, ntohs(addr->sin_port));
                } else if (storage.ss_family == AF_INET6) {
                    sockaddr_in6 *addr = (sockaddr_in6 *) &storage;
                    char ip[INET6_ADDRSTRLEN];
                    inet_ntop(AF_INET6, &addr->sin6_addr, ip, sock_len);
                    printf("client [%s:%d] \n", ip, ntohs(addr->sin6_port));
                }

                printf("...... welcome client end ......\n");
            }

            std::thread client_thead = std::thread(
                    [client_fd]() {
                        uint8_t buff[1024] = {0};
                        int ret = 0;

                        auto *parser = (http_parser *) malloc(sizeof(http_parser));
                        auto *httpServletRequest = (com::zw::HttpServletRequest *) new com::zw::HttpServletRequest();

                        httpServletRequest->clientFD = client_fd;

                        httpServletRequest->on_message_complete_cb = [](http_parser *parser) {
                            printf("on_message_complete_cb\n");
                            auto *request = (com::zw::HttpServletRequest *) (parser->data);
                            com::zw::HttpServlet *servlet = g_route[request->requestPath];
                            if (servlet) {
                                auto *response = new com::zw::HttpServletResponse(request->clientFD);
                                if (request->method == 1) {
                                    printf("on_message_complete_cb doGet ......\n");
                                    servlet->doGet(request, response);
                                } else {
                                    printf("on_message_complete_cb doPost ......\n");
                                    servlet->doPost(request, response);
                                }
                                free(response);
                                response = nullptr;
                            } else {
                                std::stringstream ss;
                                ss << "HTTP/1.1 404\r\n";
                                ss << "Content-Type: text/html;charset=utf-8\r\n";
                                std::string body = "服务器找不到请求的资源 ......";
                                ss << "Content-Length: " + body.size();
                                ss << "\r\n";
                                ss << body;
                                send(request->clientFD, (void *) (ss.str().c_str()), ss.str().size(), 0);
                                close(request->clientFD);
                            }

                            printf("on_message_complete_cb end ......\n");
                        };
                        parser->data = httpServletRequest;

                        parser_init(parser, HTTP_REQUEST);

                        http_parser_settings *httpSettings = (http_parser_settings *) malloc(
                                sizeof(http_parser_settings));
                        httpSettings->on_message_begin = onMessageBegin;
                        httpSettings->on_headers_complete = onHeaderComplete;
                        httpSettings->on_message_complete = onMessageComplete;
                        httpSettings->on_url = onURL;
                        httpSettings->on_status = onStatus;
                        httpSettings->on_header_field = onHeaderField;
                        httpSettings->on_header_value = onHeaderValue;
                        httpSettings->on_body = onBody;

                        while ((ret = recv(client_fd, (void *) buff, 1024, 0)) > 0) {
                            int parse_ret = parse(parser, httpSettings, reinterpret_cast<const char *>(buff), ret);
                            printf("buf: %s,parse_ret: %d\n", buff, parse_ret);
                            memset((void *) buff, 0, 1024);
                        }

                        if (ret <= 0) {
                            printf("recv ret: %d,error: %s\n", ret, strerror(errno));
                            close(client_fd);
                        }

                        delete(httpServletRequest);
                        httpServletRequest = nullptr;

                        free(parser);
                        parser = nullptr;

                        free(httpSettings);
                        httpSettings = nullptr;
                    });

            client_thead.detach();
        }
    } while (0);

    printf("start end\n");
}

void HttpServer::stop() {
    isStop = 1;
}

HttpServer::~HttpServer() {
}

/**
     * int socket(int family, int type, int protocol); //返回socket描述字
     * family：协议族。常用的协议族有，AF_INET(IPV4)、AF_INET6(IPV6)、AF_LOCAL（或称AF_UNIX，Unix域socket）、AF_ROUTE等。
     * type：指定socket类型。常用的socket类型有，SOCK_STREAM、SOCK_DGRAM、SOCK_RAW、SOCK_PACKET、SOCK_SEQPACKET等。
     * protocol：指定协议。常用的协议有，IPPROTO_TCP、IPPTOTO_UDP、IPPROTO_SCTP、IPPROTO_TIPC等，它们分别对应TCP传输协议、UDP传输协议、STCP传输协议、TIPC传输协议。
     */

/**
     * int bind(int sock_fd, const struct sockaddr *addr, socklen_t addr_len);
     * sock_fd：socket描述字。
     * addr：struct sockaddr类型的数据结构，由于struct sockaddr数据结构类型不方便设置，所以通常会通过对truct sockaddr_in进行地质结构设置，然后进行强制类型转换成struct sockaddr类型的数据。
     * addr_len：对应的地址的长度。
     */

/**
     * int listen(int sock_fd, int conn_num);
     * conn_num：相应socket可以排队的最大连接个数。
     */

/**
 * int connect(int sock_fd, struct sockaddr *addr,int addr_len);
 * addr：连接目标服务器的协议族。
 * addr_len：对应的地址的长度。
 */

/**
 * int accept(int sock_fd, struct sockaddr *addr, socklen_t *addr_len); //返回连接描述字
 * sock_fd：socket描述字。
 * client_addr：结果参数，用来接受一个返回值，这返回值指定客户端的地址，不需要可设置NULL。
 * addr_len：client_addr的长度
 */