#ifndef THREADPOOL_H
#define THREADPOOL_H

#include<iostream>
#include<exception>
#include<pthread.h>
#include<list>
#include"mylocker.h"
#include"myhttp_conn.h"

using std::exception;

template<typename T>
class mythreadpool
{
private:
    int my_threadnumber;  //线程池中线程数量
    int my_requestmax;   //请求队列最大请求数
    pthread_t* my_pthread;  //线程池数组
    bool my_stop;    //是否结束线程
    mylocker my_queuelocker;  //互斥锁
    std::list<T* > my_workqueue;  //请求队列
    mysem my_queuestat;  //

public:
    mythreadpool(int threadnumber=8 ,int requestmax=1000);
    ~mythreadpool();
    bool append(T* request);

private:
    static void* worker(void* arg);
    void run();  //消息循环
};

template<typename T>
mythreadpool<T>::mythreadpool(int threadnumber,int requestmax):
    my_threadnumber(threadnumber),//线程池中线程数量
    my_requestmax(requestmax),//请求队列最大请求数
    my_pthread(NULL),  //线程池数组
    my_stop(false)    //不结束线程
    {
        if((threadnumber<=0)||(requestmax<=0))//如果参数小于０，抛出异常
        {
            throw exception();
        }
        my_pthread=new pthread_t(my_threadnumber); //线程池
        if(!my_pthread)
        {
            throw exception();
        }
        int i;
        for(i=0;i<threadnumber;i++)
        {
            printf("正在创建第%d个线程\n",i);
            if(pthread_create(my_pthread+i,NULL,worker,this)!=0)//创建线程
            {
                delete [] my_pthread;
                throw exception();
            }
            if(pthread_detach(my_pthread[i]))  //设置脱离线程
            {
                delete [] my_pthread;
                throw exception();
            }
        }
    }

template<typename T>
mythreadpool<T>::~mythreadpool()
{
    delete [] my_pthread;   //删除线程池
    my_stop=true;           //结束线程
}

template<typename T>
bool mythreadpool<T>::append(T* request)
{
    my_queuelocker.lock();    //加锁
    if(my_workqueue.size()>my_requestmax)  //如果请求队列数大于最大队列数
    {
        my_queuelocker.unlock();  //解锁，抛出异常
        throw exception();
    }
    my_workqueue.push_back(request); //将请求加入队列
    my_queuelocker.unlock(); //解锁
    my_queuestat.post();  //信号量加１
    return true;
}

template<typename T>
void* mythreadpool<T>::worker(void* arg)
{
    mythreadpool* pool=(mythreadpool*)arg;
    pool->run();
    return pool;
}

template<typename T>
void mythreadpool<T>::run()
{
    while(!my_stop)  //如果线程没有结束
    {
        my_queuestat.wait(); //信号量减1
        my_queuelocker.lock(); //加锁
        if(my_workqueue.empty()) //如果等待队列为空
        {
            my_queuelocker.unlock();  //解锁
            continue;
        }
        T* re=my_workqueue.front(); //如果等待队列不为空，执行第一个等待线程
        my_workqueue.pop_front();//删除第一个等待线程
        my_queuelocker.unlock(); //解锁
        if(re!=NULL)//如果没有执行,继续
        {
            continue;
        }
        re -> process();

    }
}

#endif
