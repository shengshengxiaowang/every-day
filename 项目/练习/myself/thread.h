#ifndef THREADPOOL_H
#define THREADPOOL_H

#include<iostream>
#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>
#include "locker.h"

template< typename T >  //创建线程池
class threadpool
{

public:
    threadpool(int thread_number = 8, int max_requests = 10000 );
    ~threadpool();
    bool append( T* request );

private:
    static void* worker( void* arg );
    void run();
};
private:
    int m_thread_number; //线程总数
    int m_max_requests;  //工作队列总数
    pthread_t* m_threads;  //线程池数
    //*m_threads=NULL;
    std::list< T* > m_workqueue;  //请求队列
    locker m_queuelocker;     //请求互斥锁
    sem m_queuestat;     //用信号量判断处理任务
    bool m_stop=1;

//（有问题）template< typename T >   //创建线程池（有问题）
template< typename T >
threadpool< T >::threadpool( int thread_number, int max_requests ) :
        m_thread_number( thread_number ), m_max_requests( max_requests ), m_stop( false ), m_threads( NULL )
{
    if( ( thread_number <= 0 ) || ( max_requests <= 0 ) )
    {
        throw std::exception();
    }

    m_threads = new pthread_t[ m_thread_number ];
    if( ! m_threads )
    {
        throw std::exception();
    }

    for ( int i = 0; i < thread_number; ++i )
    {
        printf( "创建线程:\n", i );
        if( pthread_create( m_threads + i, NULL, worker, this ) != 0 )
        {
            delete [] m_threads;
            throw std::exception();
        }
        if( pthread_detach( m_threads[i] ) )
        {
            delete [] m_threads;
            throw std::exception();
        }
    }


}

template<typename T >
threadpool<T>::~threadpool()
{
    delete[] m_threads;
    m_stop=true;
}

template<typename T>
bool threadpool<T>::append(T* request)
{
    m_queuelocker.lock();
    if (m_workqueue.size()>m_max_requests)//如果请求队列大于最大请求队列
    {
        m_queuelocker.unlock();  //错误返回
        return false;
    }
    m_workqueue.push_back(request);  //将请求队列加入
    m_queuelocker.unlock();
    m_queuestat.post();//信号量增一
    return true;
}

template< typename T >
void* threadpool< T >::worker( void* arg )
{
    threadpool* pool = ( threadpool* )arg;
    pool->run();
    return pool;
}

template<typename T>
void threadpool<T>::run()
{
    while (!m_stop)
    {
        m_queuestat.wait();   //信号量减１，直到为０时线程挂起等待
        m_queuelocker.lock();
        if(m_workqueue.empty())
        {
            m_queuelocker.unlock();
            continue;
        }
        T* request=m_workqueue.front();
        m_workqueue.pop_front();
        m_queuelocker.unlock();
        if (!request)
        {
            continue;
        }
        request->process();
    }
}

#endif
