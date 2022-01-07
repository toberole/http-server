#include "threadpool.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
void taskFunc(void *args)
{
    int *p = (int *)args;
    printf("num: %d\n",*p);
}
int main_demo1(int argc, char const *argv[])
{

    // 创建线程池
    ThreadPool *pool = threadPoolCreate(3, 10, 100);
    for (int i = 0; i < 100; ++i)
    {
        int *num = (int *)malloc(sizeof(int));
        *num = i + 100;
        threadPoolAdd(pool, taskFunc, num);
    }

    sleep(30);

    threadPoolDestroy(pool);
    return 0;
}
