#include <stdio.h>
#include <stdlib.h>

extern "C"
{
#include <uv.h>
}

void libuv_test1()
{
    printf("libuv_test1 ......\n");
    uv_loop_t *loop = (uv_loop_t *)malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);
    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_close(loop);
    free(loop);
}

void libuv_test2()
{
    printf("libuv_test2 ......\n");
    // 创建loop
    uv_loop_t *loop = (uv_loop_t *)malloc(sizeof(uv_loop_t));
    // 用uv_default_loop获取libuv提供的默认loop
    loop = uv_default_loop();
    uv_loop_init(loop);
    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_close(loop);
    free(loop);
}
/**
 *   用uv_default_loop获取libuv提供的默认loop
 *
 */

int64_t counter = 0;

void wait_for_a_while(uv_idle_t *handle)
{
    counter++;

    if (counter >= 10e6)
        uv_idle_stop(handle);
}
void libuv_test3()
{
    uv_idle_t idler;

    uv_idle_init(uv_default_loop(), &idler);
    uv_idle_start(&idler, wait_for_a_while);

    printf("Idling...\n");
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    uv_loop_close(uv_default_loop());
}

int main1(int argc, char const *argv[])
{
    printf("libuv\n");
    libuv_test1();
    return 0;
}
