//POSIX下线程控制的实验程序残缺版
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<ctype.h>
#include<pthread.h>

#define MAX_THREAD 3  //线程的个数
unsigned long long main_counter,counter[MAX_THREAD];
//main_counter是主线程，counter[]各个线程不断加1

void* thread_worker(void *p)
{
    int thread_num;
    thread_num=(int)p;  //强转 让thread_num=i  c++语法不支持
    for(;;)   //无限循环
    {
        counter[thread_num]++;
        main_counter++;
    }
}

int main(int argc,char* argv[])
{
    int i,rth,ch;
    pthread_t pthread_id[MAX_THREAD]={0}; //存放线程id
    for(i=0;i<MAX_THREAD;i++)
    {
        //用pthread_create创建3个普通线程，线程id存入数组
        //线程执行函数是thread_worker,将i作为参数传入
        rth=pthread_create(&pthread_id[i] ,NULL,thread_worker,(void*)i); //question问题，如果传进去的是&i，则会出现线程为0的情况
        //第一个线程为指向线程标识符的指针，第二个设置线程属性，第三个为线程函数，第四个为函数参数
    }
    do  //用户按一次回车执行循环一次,q退出
    {
        unsigned long long sum=0;
        for(i=0;i<MAX_THREAD;i++)
        {
            sum+=counter[i];
            printf("%llu ",counter[i]);
        }
        printf("%llu/%llu",main_counter,sum);//main_counter是主线程，sum是线程和
    } while ( (ch=getchar())!='q');
    return 0;
}


/*
1.前三列不一定相等,斜杠两边，不一定，可能最开始的时候后面的比前面的大，因为sum执行较慢，所以会执行sum的时候还是之前的值
  因为前面的main_counter是主线程，即每次运行一个线程都会+1,而sum是所有线程和，和肯定包括了每次运行都+1的那个线程的标识符，所有肯定大于等于
2.结果不如我所料，最开始我以为前面三个线程数是不一样的，但是最后发现是随机的
  没有分析出原因
3.cpu占用很高，因为线程无限死循环，所以占用cpu非常高。
4.终端输入q退出，不好，因为直接会退出主线程。
5.好的。
*/