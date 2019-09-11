#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int main(void)
{
    int i;s
    for(i=0;i<2;i++)
    {
        fork();
        printf("-\n");
        //printf("-");
    }
    wait(NULL);
    wait(NULL);
    return 0;
}

/*程序应该输出6个-，可是没有\n的话结果是8个-。
6个-的原因是因为fork不断进行，从当前程序接着继续，所以是6个。
8个-的原因是fork()调用时，整个父进程空间会原模原样复制到子进程中，包括指令、变量值、程序调用栈、环境变量和缓冲区等等。
所以在其中的两个fork里，之前缓冲区中都有一个‘-’，所以加起来是8个。*/

