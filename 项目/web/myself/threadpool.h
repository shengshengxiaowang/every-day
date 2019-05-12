#ifndef THREADPOOL_H
#define THREADPOOL_H

#include<iostream>
#include<cstdio>
#include<queue>
#include<exception>
#include<pthread.h>
#include<list>
#include <queue>
#include"mylocker.h"

using namespace std;

template<typename T>
class mythreadpool
{
private:
    int my_threadnumber;  //线程池中线程数量
    int my_requestmax;   //请求队列最大请求数
    pthread_t* my_pthread;  //线程池数组
    bool my_stop;    //是否结束线程
    mylocker my_queuelocker;  //互斥锁
    std::queue<T *> task_queue;  //请求队列
    mycond my_queuecond; //cond
    mysem my_queuestat;  //

public:
    mythreadpool(int threadnum=8);
    ~mythreadpool();
    bool append(T *task);
    void start();
    void stop();
private:
    static void* worker(void* arg);
    void run();  //消息循环
    T *gettask();
};

template<typename T>
mythreadpool<T>::mythreadpool(int threadnumber):
    my_threadnumber(threadnumber),//线程池中线程数量
    my_pthread(NULL),  //线程池数组
    my_stop(false)    //不结束线程
    {
        if(threadnumber<=0)//如果参数小于０，抛出异常
        {
            cout<<"threadnumber"<<endl;
            throw exception();
        }
        my_pthread=new pthread_t[my_threadnumber]; //线程池
        if(!my_pthread)
        {
            cout<<"threadpool pthread"<<endl;
            throw exception();
        }
    }

template<typename T>
void mythreadpool<T>::start()
{
    int i;
    for(i=0;i<my_threadnumber;i++)
    {
        printf("正在创建第%d个线程\n",i);
        if(pthread_create(my_pthread+i,NULL,worker,this)!=0)//创建线程
        {
            delete [] my_pthread;
            cout<<"threadpool create"<<endl;
            throw exception();
        }
        if(pthread_detach(my_pthread[i]))  //设置脱离线程
        {
            delete [] my_pthread;
            cout<<"threadpool detach"<<endl;
            throw exception();
        }
    }
}


template<typename T>
mythreadpool<T>::~mythreadpool()
{
    delete [] my_pthread;   //删除线程池
    stop();           //结束线程
}

template<typename T>
void mythreadpool<T>::stop()
{
        my_stop = true;
        //queue_sem_locker.add();
        my_queuecond.broadcast();
}

template<typename T>
bool mythreadpool<T>::append(T *task)
{   //获取互斥锁
    my_queuelocker.lock();

    bool is_signal = task_queue.empty();
    //添加进入队列
    task_queue.push(task);
    my_queuelocker.unlock();
    //唤醒等待任务的线程
    if(is_signal)
    {
            my_queuecond.signal();
    }
    return true;
/*my_queuelocker.lock();    //加锁
    if(my_workqueue.size()>my_requestmax)  //如果请求队列数大于最大队列数
    {
        my_queuelocker.unlock();  //解锁，抛出异常
        throw exception();
        return false;
    }
    my_workqueue.push_back(request); //将请求加入队列
    my_queuelocker.unlock(); //解锁
    my_queuestat.post();  //信号量加１
    return true;*/
}

template<typename T>
void* mythreadpool<T>::worker(void* arg)
{
    mythreadpool* pool=(mythreadpool*)arg;
    pool->run();
    return pool;
}



template<typename T>
T* mythreadpool<T>::gettask()
{
    T *task = NULL;
    my_queuelocker.lock();
    if(!task_queue.empty())
    {
        task = task_queue.front();
        task_queue.pop();
    }
    my_queuelocker.unlock();
    return task;
}


template<typename T>
void mythreadpool<T>::run()
{
    while(!my_stop)  //如果线程没有结束
    {
        while(!my_stop)
        {
            T *task = gettask();
            if(task == NULL)
                    my_queuecond.wait();
            else
    	    {
                task->doit();
    		    delete task;
    	    }
        }

    }
}

#endif
