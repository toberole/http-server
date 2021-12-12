﻿#include <stdio.h>
#include <stdlib.h>

extern "C"
{
#include <uv.h>
}
/*
在网络I/O中会使用到uv_tcp_t和uv_udp_t。
server
服务器端的建立流程如下：
    1.uv_tcp_init建立tcp句柄。
    2.uv_tcp_bind绑定。
    3.uv_listen建立监听，当有新的连接到来时，激活调用回调函数。
    4.uv_accept接收链接。
    5.使用stream操作来和客户端通信。
*/
void on_new_connection(uv_stream_t *server, int status)
{
    // if (status < 0) {
    //     fprintf(stderr, "New connection error %s\n", uv_strerror(status));
    //     // error!
    //     return;
    // }

    // uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    // uv_tcp_init(loop, client);
    // if (uv_accept(server, (uv_stream_t*) client) == 0) {
    //     uv_read_start((uv_stream_t*) client, alloc_buffer, echo_read);
    // }
    // else {
    //     uv_close((uv_handle_t*) client, NULL);
    // }
}
int main(int argc, char const *argv[])
{
    printf("libuv_net\n");

    // loop = uv_default_loop();

    // uv_tcp_t server;
    // uv_tcp_init(loop, &server);

    // uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr);

    // uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);
    // int r = uv_listen((uv_stream_t *)&server, DEFAULT_BACKLOG, on_new_connection);
    // if (r)
    // {
    //     fprintf(stderr, "Listen error %s\n", uv_strerror(r));
    //     return 1;
    // }
    // return uv_run(loop, UV_RUN_DEFAULT);
    return 0;
}
