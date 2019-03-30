#include<iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <cassert>
#include <sys/epoll.h>

#include "mylocker.h"
#include "mythreadpool.h"
#include "myhttp_conn.h"

#define MAX_FD 65536
#define MAX_EVENT_NUMBER 10000

extern int addfd(int epollfd,int fd,bool one_shot);//添加事件
extern int removefd(int epollfd,int fd);//删除事件

void addsig(int sig,void(handler)(int),bool restart=true)
{
    struct sigaction sa;
    memset(&sa,'\0',sizeof(sa));
    sa.sa_handler=handler;
    if(restart)
    {
        sa.sa_flags|=SA_RESTART;
    }
    sigfillset(&sa.sa_mask);//sa_mask信号集初始化，将所有信号加到此信号集里
    assert(sigaction(sig,&sa,NULL)!=-1);//断言
}

void show_error(int connfd,const char* info)
{
    printf("%s",info);
    send(connfd,info,strlen(info),0);
    close( connfd );
}


int main(int argc,char* argv[])
{
    if( argc <= 2 )
    {
        printf("usage: %s ip_address port_number\n",basename(argv[0]));
        return 1;
    }
    const char* ip=argv[1];
    int port=atoi(argv[2]);

    addsig(SIGPIPE, SIG_IGN); //忽视该信号
    mythreadpool< myhttp_conn >* pool;
    pool = new mythreadpool<myhttp_conn>;
    /*pool=new mythreadpool < myhttp_conn >::mythreadpool;
    /*mythreadpool< myhttp_conn >* pool=NULL;
    pool = new mythreadpool<myhttp_conn>;*/

    /*try
    {
        pool= new mythreadpool< >;
    }
    catch(...)
    {
        return 1;
    }*/

    myhttp_conn* users= new myhttp_conn[MAX_FD];
    assert(users); //断言
    //int user_count = 0;

    int listenfd=socket(PF_INET,SOCK_STREAM,0); //监听套接字
    assert(listenfd>= 0);//断言
    struct linger tmp={1,0};
    setsockopt(listenfd,SOL_SOCKET,SO_LINGER,&tmp,sizeof(tmp));

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family=AF_INET;
    inet_pton(AF_INET,ip,&address.sin_addr);
    address.sin_port=htons(port);

    ret=bind(listenfd,(struct sockaddr*)&address,sizeof(address));
    assert(ret>=0);

    ret=listen(listenfd,5);
    assert(ret>=0);

    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd=epoll_create(5);
    assert(epollfd!=-1);
    addfd(epollfd,listenfd,false);
    myhttp_conn::my_epollfd=epollfd;

    while(true)
    {
        int number=epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
        if ( (number<0) && (errno!=EINTR) )
        {
            printf("epoll failure\n");
            break;
        }

        for(int i=0;i<number;i++)
        {
            int sockfd=events[i].data.fd;
            if(sockfd==listenfd)
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength=sizeof(client_address);
                int connfd=accept(listenfd,(struct sockaddr*)&client_address,&client_addrlength);
                if(connfd<0)
                {
                    printf("errno is: %d\n",errno);
                    continue;
                }
                if(myhttp_conn::my_usercount>=MAX_FD)
                {
                    show_error(connfd,"Internal server busy");
                    continue;
                }

                users[connfd].init(connfd,client_address);
            }
            else if(events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
            {
                users[sockfd].close_conn();
            }
            else if(events[i].events & EPOLLIN)
            {
                if(users[sockfd].read())
                {
                    pool->append(users+sockfd);
                }
                else
                {
                    users[sockfd].close_conn();
                }
            }
            else if(events[i].events & EPOLLOUT)
            {
                if(!users[sockfd].write())
                {
                    users[sockfd].close_conn();
                }
            }
            else
            {}
        }
    }

    close(epollfd);
    close(listenfd);
    delete [] users;
    delete pool;
    return 0;
}
