#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
/*
服务端
    创建socket ---> bind ---> listen ---> accept
    int socket(int domain, int type, int protocol)
        domain就是指PF_INET、PF_INET6以及PF_LOCAL等，表示什么样的套接字。
        type可用的值是：
            SOCK_STREAM: 表示的是字节流，对应TCP；
            SOCK_DGRAM： 表示的是数据报，对应UDP；
            SOCK_RAW: 表示的是原始套接字。
        protocol原本是用来指定通信协议的，但现在基本废弃。因为协议已经通过前面两个参数指定完成。
        protocol目前一般写成0即可。

    bind(int fd, sockaddr * addr, socklen_t len)调用bind函数把套接字和套接字地址绑定

    int listen (int socketfd, int backlog)
        socketfd为套接字描述符
        backlog，在Linux中表示已完成(ESTABLISHED)且未accept的队列大小，
        这个参数的大小决定了可以接收的并发数目。这个参数越大，并发数目理论上也会越大。
        但是参数过大也会占用过多的系统资源

    int accept(int listensockfd, struct sockaddr *cliaddr, socklen_t *addrlen)
        listensockfd是套接字，可以叫它为listen套接字，因为这就是前面通过bind，listen一系列操作而得到的套接字。函数的返回值有两个部分，
        第一个部分cliadd是通过指针方式获取的客户端的地址，addrlen告诉我们地址的大小
 */
/*
客户端
    创建socket ---> connect
    int connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
        sockfd是连接套接字，通过前面讲述的socket函数创建。
        servaddr和addrlen分别代表指向套接字地址结构的指针和该结构的大小。套接字地址结构必须含有服务器的IP地址和端口号。
    如果是TCP套接字，那么调用connect函数将激发TCP的三次握手过程，而且仅在连接建立成功或出错时才返回。其中出错返回可能有以下几种情况：
        1、三次握手无法建立，客户端发出的SYN包没有任何响应，于是返回TIMEOUT错误。这种情况比较常见的原因是对应的服务端IP写错。
        2、客户端收到了RST（复位）回答，这时候客户端会立即返回CONNECTION REFUSED错误。这种情况比较常见于客户端发送连接请求时的请求端口写错，
        因为RST是TCP在发生错误时发送的一种TCP分节。产生RST的三个条件是：目的地为某端口的SYN到达，然而该端口上没有正在监听的服务器（如前所述）；TCP想取消一个已有连接；TCP接收到一个根本不存在的连接上的分节。
        3、客户发出的SYN包在网络上引起了"destination unreachable"，即目的不可达的错误。这种情况比较常见的原因是客户端和服务器端路由不通。
*/
int make_server_socket(uint16_t port)
{
    int sock;
    struct sockaddr_in name;
    /* 创建字节流类型的IPV4 socket. */
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    /* 绑定到port和ip. */
    name.sin_family = AF_INET;                /* IPV4 */
    name.sin_port = htons(port);              /* 指定端口 */
    name.sin_addr.s_addr = htonl(INADDR_ANY); /* 通配地址,绑定到本机IP地址 */
    /* 把IPV4地址转换成通用地址格式，同时传递长度 */
    if (bind(sock, (struct sockaddr *)&name, sizeof(name)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    return sock;
}

void startServer()
{
    do
    {

    } while (0);
}
int main(int argc, char const *argv[])
{
    printf("Hello World!\n");
    return 0;
}

/*
发送数据
  发送数据时常用的有三个函数，分别是write、send和sendmsg。
    ssize_t write (int socketfd, const void *buffer, size_t size)
    ssize_t send (int socketfd, const void *buffer, size_t size, int flags)
    ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags)
    write 函数是常见的文件写函数，如果把socketfd换成文件描述符，就是普通的文件写入。
    如果想指定选项，发送带外数据，就需要使用第二个带flag的函数。所谓带外数据，是一种基于TCP协议的紧急数据，用于客户端-服务器在特定场景下的紧急处理。
    如果想指定多重缓冲区传输数据，就需要使用第三个函数，以结构体msghdr的方式发送数据。

    对于普通文件描述符而言，一个文件描述符代表了打开的一个文件句柄，通过调用write函数，操作系统内核帮我们不断地往文件系统中写入字节流。注意，写入的字节流大小通常和输入参数size的值是相同的，否则表示出错。
    对于套接字描述符而言，它代表了一个双向连接，在套接字描述符上调用write写入的字节数有可能比请求的数量少，这在普通文件描述符情况下是不正常的。
    产生这个现象的原因在于操作系统内核为读取和发送数据做了很多我们表面上看不到的工作

发送缓冲区
    当TCP三次握手成功，TCP连接成功建立后，操作系统内核会为每一个连接创建配套的基础设施，比如发送缓冲区。
    发送缓冲区的大小可以通过套接字选项来改变，当我们的应用程序调用write函数时，实际所做的事情是把数据从应用程序中拷贝到操作系统内核的发送缓冲区中，并不一定是把数据通过套接字写出去。

读取数据
ssize_t read (int socketfd, void *buffer, size_t size)
read函数要求操作系统内核从套接字描述字socketfd读取最多多少个字节（size），并将结果存储到buffer中。
返回值告诉我们实际读取的字节数目，也有一些特殊情况，如果返回值为0，表示EOF（end-of-file），
这在网络中表示对端发送了FIN包，要处理断连的情况；如果返回值为-1，表示出错。
如果是非阻塞I/O，情况会略有不同

发送成功仅仅表示的是数据被拷贝到了发送缓冲区中，并不意味着连接对端已经收到所有的数据。
至于什么时候发送到对端的接收缓冲区，或者更进一步说，什么时候被对方应用程序缓冲所接收，
对上层应用而言完全都是透明的【由底层操作系统网络协议栈处理】。
 */

/* 从socketfd描述字中读取"size"个字节. */
size_t readn(int fd, void *buffer, size_t size)
{
    char *buffer_pointer = (char *)buffer;
    int length = size;

    while (length > 0)
    {
        int result = read(fd, buffer_pointer, length);

        if (result < 0)
        {
            if (errno == EINTR)
            {
                continue; /* 考虑非阻塞的情况，这里需要再次调用read */
            }
            else
            {
                return (-1);
            }
        }
        else if (result == 0)
        {
            break; /* EOF(End of File)表示套接字关闭 */
        }

        length -= result;
        buffer_pointer += result;
    }
    return (size - length); /* 返回的是实际读取的字节数*/
}