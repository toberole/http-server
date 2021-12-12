#include <stdio.h>
#include <stdlib.h>

extern "C"
{
#include <uv.h>
}
/*
文件描述符可以采用如下方式获得：
int uv_fs_open(uv_loop_t* loop, uv_fs_t* req, const char* path, int flags, int mode, uv_fs_cb cb)
    参数flags与mode和标准的 Unix flags 相同。
    libuv 会小心地处理 Windows 环境下的相关标志位(flags)的转换, 所以编写跨平台程序时你不用担心不同平台上文件打开的标志位不同。
关闭文件描述符可以使用：
    int uv_fs_close(uv_loop_t* loop, uv_fs_t* req, uv_file file, uv_fs_cb cb)
文件系统的回调函数有如下的形式：
    void callback(uv_fs_t* req);
*/
void on_open(uv_fs_t *req)
{
    // The request passed to the callback is the same as the one the call setup
    // function was passed.
}
int main1(int argc, char const *argv[])
{
    printf("filesystem\n");
    return 0;
}
