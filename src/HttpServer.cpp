﻿#include "HttpServer.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <thread>

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
HttpServer::HttpServer(int port) : port(port)
{
}

void HttpServer::start()
{
    int res = -1;
    do
    {
        server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (server_fd == -1)
        {
            printf("create socker ret: %d,error: %s\n", server_fd, strerror(errno));
            break;
        }

        sockaddr_in server_addr;
        bzero(&server_addr, sizeof(sockaddr_in));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        res = bind(server_fd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr));
        if (res != 0)
        {
            printf("bind res: %d,error: %s\n", res, strerror(errno));
            break;
        }

        res = listen(server_fd, 1024);
        if (res == -1)
        {
            printf("listen res: %d,error: %s\n", res, strerror(errno));
            break;
        }

        int client_fd;
        uint8_t buff[1024] = {0};
        while (isStop != 1)
        {
            client_fd = accept(server_fd, nullptr, nullptr);
            if (client_fd == -1)
            {
                printf("accept res: %d,error: %s\n", client_fd, strerror(errno));
                continue;
            }

            res = recv(client_fd, (void *)buff, 1024, 0);
            if (res <= 0)
            {
                printf("recv res: %d,error: %s\n", res, strerror(errno));
                close(client_fd);
                client_fd = 0;
                continue;
            }

            printf("buf: %s\n", buff);
        }

    } while (0);

    printf("start end\n");
}

void HttpServer::stop()
{
    isStop = 1;
}

HttpServer::~HttpServer()
{
}