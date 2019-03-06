#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/sendfile.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<unistd.h>
#include<string.h>
const int port = 8888;      //port是端口
int main(int argc,char *argv[])
{
    if(argc<0)
    {
        printf("need two canshu\n");
        return 1;
    }
    int sock;
    int connfd;
    struct sockaddr_in sever_address;
    bzero(&sever_address,sizeof(sever_address));  //结构体所有字符置0
    sever_address.sin_family = PF_INET;//Address family一般来说AF_INET（地址族）PF_INET（协议族)
    sever_address.sin_addr.s_addr = htons(INADDR_ANY); //sin_addr存储IP地址,s_addr按照网络字节顺序存储IP地址,htons是将整型变量从主机字节顺序转变成网络字节顺序
    sever_address.sin_port = htons(8888);//sin_port存储端口号（使用网络字节顺序）

    sock = socket(AF_INET,SOCK_STREAM,0);  //创建套接字

    assert(sock>=0);  //断言,如果sock<0,则程序退出

    int ret = bind(sock, (struct sockaddr*)&sever_address,sizeof(sever_address));
//将套接字与端口连接，       与协议有关的地址结构指针，存储了套接字信息的指针，大小

    assert(ret != -1);   //断言

    ret = listen(sock,1);  //服务器端启动监听
    assert(ret != -1);
    while(1)
    {
        struct sockaddr_in client;
        socklen_t client_addrlength = sizeof(client);
        connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);//接收连接
        if(connfd<0)
        {
            printf("errno\n");
        }
        else{
                char request[1024];
                recv(connfd,request,1024,0);  //接收数据
                request[strlen(request)+1]='\0';
                printf("%s\n",request);
                printf("successeful!\n");
                char buf[520]="HTTP/1.1 200 ok\r\nconnection: close\r\n\r\n";//HTTP响应
                int s = send(connfd,buf,strlen(buf),0);//发送响应
                //printf("send=%d\n",s);
                int fd = open("hello.html",O_RDONLY);//消息体
                sendfile(connfd,fd,NULL,2500);//零拷贝发送消息体
                close(fd);
                close(connfd);
        }
    }
    return 0;
}
