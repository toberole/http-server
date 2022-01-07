#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{

    printf("fd_set size: %d\n",sizeof(fd_set));
    // 标准终端输入
    int fd = STDIN_FILENO;
    fd_set readfds;
    fd_set writefds;
    fd_set errorfds;
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_ZERO(&errorfds);

    FD_SET(fd, &readfds);
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    // int select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout)
    int n = select(fd + 1, &readfds, NULL, NULL, &timeout);
    if (n == 0)
    {
        printf("timeout ......\n");
    }
    else if (n < 0)
    {
        printf("fail ......\n");
    }
    else
    {
        printf("succ ......\n");
    }

    return 0;
}
