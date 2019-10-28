//posix下线程死锁的演示程序

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#define LOOP_TIMES 10000
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
void *thread_worker(void *);
void critical_section(int thread_num, int i);

int main()
{
    int rtn, i;
    pthread_t pthread_id = 0; //存放子进程的id
    rtn = pthread_create(&pthread_id, NULL, thread_worker, NULL);
    if (rtn != 0)  //0是成功，-1是出错
    {
        printf("pthread_create ERROR!\n");
        return -1;
    }
    //printf("dfgsgs\n");
    for(i=0;i<LOOP_TIMES;i++)
    {
        pthread_mutex_lock(&mutex2);
        pthread_mutex_lock(&mutex1);
        critical_section(1,i);
        pthread_mutex_unlock(&mutex1);
        pthread_mutex_unlock(&mutex2);
    }
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
}

void *thread_worker(void *p)
{
    int i;
    for (i = 0; i < LOOP_TIMES; i++) //10000循环
    {
        pthread_mutex_lock(&mutex2); //加锁
        pthread_mutex_lock(&mutex1);
        critical_section(2, i);        //打印线程2
        //printf("dfgsgs\n");
        pthread_mutex_unlock(&mutex1); //解锁
        pthread_mutex_unlock(&mutex2);
    }
}

void critical_section(int thread_num, int i)
{
    printf("Thread %d :%d\n", thread_num, i);
}

/*
1.我预想的两个应该会交互执行，一直到程序退出。
2.图一为修改之前的代码，可以看到两个线程在交互执行，但是会遇到死锁卡住，需要手动ctrl+c退出，
图二是修改后的代码，执行完自动退出，没有遇到死锁情况。
这是因为：在原本代码中线程1获取mutex1，再获取mutex2后才能继续执行打印，而线程2获取mutex2，再获取mutex1才能继续执行打印。
当线程1获取了mutex1，再去获取mutex2的时候发现mutex2已经被线程2锁住了，而线程2获取mutex2后，发现mutex1被线程1锁住了。
这样2个线程都在等待，都不能继续执行下去，就产生了死锁。解决办法是规定统一的加锁顺序，
这样线程1和线程2都按照先mutex1，再mutex2，就不会死锁住了。

*/