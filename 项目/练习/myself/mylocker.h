#ifndef LOCKER_H
#define LOCKER_H

//#include<list>
//#include<cstdio>
#include<iostream>
#include<exception>
#include<pthread.h>
#include<semaphore.h>
#include<exception>
using namespace std;


class mysem    //封装信号量的类
{
private:
    sem_t m_sem;
public:
    mysem()   //创建并初始化信号量
    {
        if(sem_init(&m_sem,0,0)!=0)
        {
            throw std::exception();
        }
    }
    ~mysem()   //销毁信号量
    {
        sem_destroy(&m_sem);
    }
    bool wait()  //信号量值减１，等待信号量
    {
        return (sem_post(&m_sem)==0);
    }
    bool post()   //信号量值增１
    {
        return (sem_post(&m_sem)==0);
    }
};

class mylocker   //封装互斥锁的类
{
private:
    pthread_mutex_t m_mutex;
public:
    mylocker()  //创建并初始化互斥锁
    {
        if(pthread_mutex_init(&m_mutex,NULL)!=0)
        {
            throw std::exception();
        }
    }
    ~mylocker()  //销毁互斥锁
    {
        pthread_mutex_destroy(&m_mutex);
    }
    bool lock()    //给互斥锁加锁
    {
        return (pthread_mutex_lock(&m_mutex)==0);
    }
    bool unlock()   //解锁
    {
        return (pthread_mutex_unlock(&m_mutex)==0);
    }
};


class mycond   //封装条件变量的类
{
private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
public:
    mycond()    //创建并初始化条件变量
    {
        if(pthread_mutex_init(&m_mutex,NULL)!=0)//创建初始化互斥锁
        {
            throw std::exception();
        }
        if(pthread_cond_init(&m_cond,NULL)!=0)
        {
            throw std::exception();
        }
    }
    ~mycond()     //销毁条件变量
    {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_cond);
    }
    bool wait()   //等待条件变量
    {
        int ret;
        pthread_mutex_lock(&m_mutex );    ///上锁
        ret=pthread_cond_wait(&m_cond,&m_mutex);   //等待目标条件变量
        pthread_mutex_unlock(&m_mutex);    //解锁
        return ret==0;
    }
    bool signal()  //唤醒等待条件变量的线程
    {
        return pthread_cond_signal(&m_cond)==0;
    }
};

#endif
