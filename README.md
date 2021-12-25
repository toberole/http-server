http server 基本框架搭建完成
后面整合 libuv

服务器端程序，都应该设置 SO_REUSEADDR 套接字选项，以便服务端程序可以在极短时间内复用同一个端口启动。

处理网络字节序
uint16_t htons (uint16_t hostshort)
uint16_t ntohs (uint16_t netshort)
uint32_t htonl (uint32_t hostlong)
uint32_t ntohl (uint32_t netlong)