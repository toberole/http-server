/*
服务端：
    socket ---> bind ---> [recvfrom <----> sendto]

客户端：
    socket --- > [sendto <----> recvfrom]

ssize_t recvfrom(int sockfd, void *buff, size_t nbytes, int flags, 
　　　　　　　　　　struct sockaddr *from, socklen_t *addrlen); 
sockfd是本地创建的套接字描述符，buff指向本地的缓存，nbytes表示最大接收数据字节。
flags是和I/O相关的参数,如果用不到，设置为0。
from和addrlen，实际上是返回对端发送方的地址和端口等信息

ssize_t sendto(int sockfd, const void *buff, size_t nbytes, int flags,
                const struct sockaddr *to, socklen_t addrlen); 

 
 */

