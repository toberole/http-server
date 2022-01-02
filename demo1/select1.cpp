#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

void start_server_1(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("usage: ip address + port numbers\n");
        return -1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    printf("ip: %s\n", ip);
    printf("port: %d\n", port);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        printf("Fail to create listen socket!\n");
        return -1;
    }

    ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    if (ret == -1)
    {
        printf("Fail to bind socket!\n");
        return -1;
    }

    ret = listen(listenfd, 5); //监听队列最大排队数设置为5
    if (ret == -1)
    {
        printf("Fail to listen socket!\n");
        return -1;
    }

    struct sockaddr_in client_address; //记录进行连接的客户端的地址
    socklen_t client_addrlength = sizeof(client_address);
    int connfd = accept(listenfd, (struct sockaddr *)&client_address, &client_addrlength);
    if (connfd < 0)
    {
        printf("Fail to accept!\n");
        close(listenfd);
    }

    char buff[1024] = {0}; //数据接收缓冲区
    fd_set read_fds;       //读文件操作符
    fd_set exception_fds;  //异常文件操作符
    FD_ZERO(&read_fds);
    FD_ZERO(&exception_fds);

    while (1)
    {
        memset(buff, 0, sizeof(buff));
        /*每次调用select之前都要重新在read_fds和exception_fds中设置文件描述符connfd，因为事件发生以后，文件描述符集合将被内核修改*/
        FD_SET(connfd, &read_fds);
        FD_SET(connfd, &exception_fds);

        ret = select(connfd + 1, &read_fds, NULL, &exception_fds, NULL);
        if (ret < 0)
        {
            printf("Fail to select!\n");
            return -1;
        }

        if (FD_ISSET(connfd, &read_fds))
        {
            ret = recv(connfd, buff, sizeof(buff) - 1, 0);
            if (ret <= 0)
            {
                break;
            }

            printf("get %d bytes of normal data: %s \n", ret, buff);
        }
        else if (FD_ISSET(connfd, &exception_fds)) //异常事件
        {
            ret = recv(connfd, buff, sizeof(buff) - 1, MSG_OOB);
            if (ret <= 0)
            {
                break;
            }

            printf("get %d bytes of exception data: %s \n", ret, buff);
        }
    }

    close(connfd);
    close(listenfd);
}
void start_server_2(int argc, char *argv[])
{
    int server_sockfd;
    int client_sockfd;
    int server_len;
    int client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int result;
    fd_set readfds;
    fd_set testfds;
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0); //建立服务器端socket
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(8888);
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    listen(server_sockfd, 5); //监听队列最多容纳5个
    FD_ZERO(&readfds);
    FD_SET(server_sockfd, &readfds); //将服务器端socket加入到集合中
    while (1)
    {
        char ch;
        int fd;
        int nread;
        testfds = readfds; //将需要监视的描述符集copy到select查询队列中，select会对其修改，所以一定要分开使用变量
        printf("server waiting\n");

        /*无限期阻塞，并测试文件描述符变动 */
        result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0); // FD_SETSIZE：系统默认的最大文件描述符
        if (result < 1)
        {
            perror("server5");
            exit(1);
        }

        /*扫描所有的文件描述符*/
        for (fd = 0; fd < FD_SETSIZE; fd++)
        {
            /*找到相关文件描述符*/
            if (FD_ISSET(fd, &testfds))
            {
                /*判断是否为服务器套接字，是则表示为客户请求连接。*/
                if (fd == server_sockfd)
                {
                    client_len = sizeof(client_address);
                    client_sockfd = accept(server_sockfd,
                                           (struct sockaddr *)&client_address, &client_len);
                    FD_SET(client_sockfd, &readfds); //将客户端socket加入到集合中
                    printf("adding client on fd %d\n", client_sockfd);
                }
                else /*客户端socket中有数据请求时*/
                {
                    ioctl(fd, FIONREAD, &nread); //取得数据量交给nread

                    /*客户数据请求完毕，关闭套接字，从集合中清除相应描述符 */
                    if (nread == 0)
                    {
                        close(fd);
                        FD_CLR(fd, &readfds); //去掉关闭的fd
                        printf("removing client on fd %d\n", fd);
                    }
                    else /*处理客户数据请求*/
                    {
                        read(fd, &ch, 1);
                        sleep(5);
                        printf("serving client on fd %d\n", fd);
                        ch++;
                        write(fd, &ch, 1);
                    }
                }
            }
        }
    }
}

void client1()
{
    int client_sockfd;
    int len;
    struct sockaddr_in address; //服务器端网络地址结构体
    int result;
    char ch = 'A';
    client_sockfd = socket(AF_INET, SOCK_STREAM, 0); //建立客户端socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(8888);
    len = sizeof(address);
    result = connect(client_sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("oops: client2");
        exit(1);
    }
    //第一次读写
    write(client_sockfd, &ch, 1);
    read(client_sockfd, &ch, 1);
    printf("the first time: char from server = %c\n", ch);
    sleep(5);

    //第二次读写
    write(client_sockfd, &ch, 1);
    read(client_sockfd, &ch, 1);
    printf("the second time: char from server = %c\n", ch);

    close(client_sockfd);
}

int main(int argc, char *argv[])
{

    return 0;
}
