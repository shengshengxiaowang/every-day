#include "task.h"
#include "threadpool.h"
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
#include <netinet/in.h>
#include <arpa/inet.h>


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



/*int main(int argc, char *argv[])
{
	if(argc!=2)
    {
		cout<<"参数格式错误"<<endl;
		return 1;
	}
	int listenfd=socket(PF_INET,SOCK_STREAM,0); //监听套接字
	assert(listenfd>= 0);//断言
    int sockfd, connfd;
   	struct sockaddr_in servaddr, client;
    int port=atoi(argv[1]);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
    {
		cout<<"main sockfd"<<endl;
		return 1;
    }


    int ret=bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    assert(ret>=0);
    ret = listen(sockfd, 10);//监听套接字
    assert(ret>=0);
	addsig(SIGPIPE, SIG_IGN); //忽视该信号
	mythreadpool<task> pool(20);  //创建线程池
	pool.start();  //运行

	/*
		int sockNumber[1000]={0};
		struct epoll_event event;
    struct epoll_event *wait_event;
	int crRet=epoll_create(10);
	if(-1==crRet)
    {
        perror("创建文件描述符失败");
        return 0;
    }
    event.data.fd=sockfd;
    event.events=EPOLLIN;
    int clRet=epoll_ctl(crRet,EPOLL_CTL_ADD,sockfd,&event);
    if(-1==clRet)
    {
        perror("注册监听事件类型失败");
    }
	int max1=0;
    char buf[1024]={0};


	while(1)
    {
		wait_event=new epoll_event[max1+1];
        clRet=epoll_wait(crRet,wait_event,max1+1,-1);
        for(int i=0;i<clRet;i++)
        {
            if((sockfd==wait_event[i].data.fd)&&(EPOLLIN==wait_event[i].events&EPOLLIN) )
            {
				  struct sockaddr_in cli_addr;
                  socklen_t length = sizeof(cli_addr);
                  sockNumber[max1+1]=accept(sockfd,(struct sockaddr*)&cli_addr,&length);
                  if(sockNumber[max1+1]>0)
                  {
                       event.data.fd = sockNumber[max1+1];
                       event.events = EPOLLIN;
                       int ret1 = epoll_ctl(crRet, EPOLL_CTL_ADD, sockNumber[max1+1], &event);
                       max1++;
                       if(-1==ret1)
                       {
                           perror("新连接的客户端注册失败");
                       }
                    printf("客户端%d上线\n",max1);

				    //socklen_t len = sizeof(client);
   					//接受连接
   					connfd=accept(sockfd, (struct sockaddr *)&client, &length);

   					task *ta=new task(connfd);
   					//向线程池添加任务
   					pool.append(ta);

                  }
             }
            else if(wait_event[i].data.fd>3&&( EPOLLIN == wait_event[i].events & (EPOLLIN|EPOLLERR)))
              {      memset(buf,0,sizeof(buf));
                     int len=recv(wait_event[i].data.fd,buf,sizeof(buf),0);
                     if(len<=0)
                      {
                            for(int j=1;j<=max1;j++)
                             {
                                  if(wait_event[i].data.fd==sockNumber[j])
                                    {
                                            clRet=epoll_ctl(crRet,EPOLL_CTL_DEL,wait_event[i].data.fd,wait_event+i);
                                            printf("客户端%d下线\n",max1);
                                            sockNumber[j] =sockNumber[max1] ;
                                            close(sockNumber[max1]);
                                            sockNumber[max1] =-1;
                                            max1--;
                                            usleep(50000);
                                    }
                             }
                      }
                   else
                     {
                      printf("%s\n",buf);
                     }
           }
        }
        delete[] wait_event;
	}
*/




int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("usage : %s port\n", argv[0]);
		return 1;
	}

	int sockfd, connfd;
	struct sockaddr_in servaddr, client;
	int port = atoi(argv[1]);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		cout<<"main sockfd"<<endl;
		return 1;
	}

	int ret = bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(ret < 0)
	{
		cout<<"main ret"<<endl;
		return 1;
	}

	ret = listen(sockfd, 10);
	if(ret < 0)
	{
		cout<<"main listen"<<endl;
		return 1;
	}
	//创建线程池
	addsig(SIGPIPE, SIG_IGN); //忽视该信号
	mythreadpool<task> pool(20);
	pool.start();  //线程池开始运行

	while(1)
	{

		socklen_t len = sizeof(client);

		connfd = accept(sockfd, (struct sockaddr *)&client, &len);
		task *ta = new task(connfd);

		pool.append(ta);
	}
	return 0;
}
