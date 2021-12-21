#include <stdio.h>
#include <stdlib.h>
 
extern "C"
{
    #include <uv.h>
}

void libuv_test1()
{
    uv_loop_t *loop = (uv_loop_t *)malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);
    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_close(loop);
    free(loop);
}

int main(int argc, char const *argv[])
{
    printf("Hello libuv\n");
    libuv_test1();
    return 0;
}
