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
        //if(getpid())
        child_pid=fork();  //子进程返回0，父进程返回子进程id
        if(child_pid==0)  //如果是子进程
        {
            proc_number=i;
            //printf("%d\n",i);
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
    
    kill(0,SIGTERM);  //杀死父进程，即杀死所有进程
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

/*
1.我开始认为最终运行结果会创建child_proc_number(最多10)个进程
然后用户输入相对应的进程id,就可以杀死进程，输入q杀死所有进程退出程序。
2.实际结果跟我认为的差不多，但是用户只需要输入要杀死的第几个进程号就行。
特点就是进程会不断的显示信息，大概2秒重复一下，应该是父进程创建子进程，子进程跟父进程继续创建，然后都卡在了函数中的sleep中
3.不相同，因为proc_number是循环中的i值，而i在不同进程中是不一样的
4.使用了（用户杀死进程的个数加1）次，最后一次作用是杀死父进程，其余的作用都是杀死相对应的子进程。
执行后现象便是该进程结束，最后一次执行后现象为程序结束退出。
5.调用结束进程的函数，如exit()等。调用函数方法比较好，从外部杀死可能会中断正在执行的程序。
6.好的。

*/