#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<ctype.h>
#include <stdlib.h>
#define MAX_CHILD_NUMBER 10 //允许建立子进程的个数最大值
#define SLEEP_INTERVAL 2  //子进程睡眠时间

int proc_number=0; //子进程的自编号，从0开始
void do_something();
int main(int argc,char* argv[])
{
    int child_proc_number=MAX_CHILD_NUMBER; //子进程个数
    int i,ch;
    pid_t child_pid;
    pid_t pid[10]={0}; //存放每个子进程的id
    if(argc>1)  //第一个参数表示子进程个数
    {
        child_proc_number=atoi(argv[1]);  //字符串转整形函数
        child_proc_number=(child_proc_number>10)?10:child_proc_number; //子进程最大个数为10
    }
    for(i=0;i<child_proc_number;i++)
    {
        child_pid=fork();
        if(child_pid==0)  //如果是子进程
        {
            proc_number=i;
            do_something();//输出信息
        }
        else  //如果是父进程
        {
            pid[i]=child_pid;  //子进程id保存到数组中
            //pid[i]=getpid();
            //这种方法是不对的，因为是获取到的是当前的父进程id，但是为什么会导致程序整个有问题，待解决
        }
        
    }
    while((ch=getchar())!='q') //用户选择杀死进程，数字为进程号，q退出
    {
        if(isdigit(ch)) //判断输入的是否是十进制数，也就是在10内
        {
            kill(pid[ch-'0'],SIGTERM); //杀死进程
        }
    }
    
    for(i=0;i<child_proc_number;i++)
    {
        kill(pid[i],SIGTERM); //杀死进程
    }

    kill(0,SIGTERM);
    return 0;
    
}

void do_something()
{
    for(;;)
    {
        printf("这是第%d个进程，并且进程id为%d\n",proc_number,getpid());
        sleep(SLEEP_INTERVAL); //主动阻塞2秒
    }
}