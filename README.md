http server 基本框架搭建完成
后面整合 libuv

服务器端程序，都应该设置 SO_REUSEADDR 套接字选项，以便服务端程序可以在极短时间内复用同一个端口启动。
