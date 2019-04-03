#include"unp.h"  //自己定义的头文件，包含了很多系统头文件和定义的很多常值
int main(int argc,char **argv)
{
    int sockfd,n;   //sockfd是套接字,
    char recvline[MAXLINE];
    struct sockaddr_in servaddr;
//sockaddr_in a;
//a.sin_family;指代协议族，在socket编程里只能是AF_INET
//a.sin.port;存储端口号（网络字节顺序）
//a.sin_addr;存储ip地址，使用in_addr结构
    if(argc!=2)
    {
        printf("usage:a.out <ipaddress>\n");
        return 0;
    }
    if( (sockfd=(socket(AF_INET,SOCK_STREAM,0))<0) )
    {
//int socket(int af,int type,int protocol);
//af：一个地址描述，仅支持AF_INET
//type:socket类型：SOCK_STREAM是tcp/ip;SOCK_DGRAM是udp的
        printf("socket error\n");
        return 0;
    }
    bzero(&servaddr,sizeof(servaddr));  //结构体servaddr置０
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(13); //13是时间获取服务器的众所周知端口
//htons()将整型变量从主机字节顺序变为网络字节顺序
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<0)
    {
//inet_pton()将ip地址转换
        printf("inet_pton\n");
        return 0;
    }
    if(connect(sockfd,(SA *)&servaddr,sizeof(servaddr))<0)
    {
        printf("connect\n");
        return 0;
    }
    while((n=read(sockfd,recvline,MAXLINE))>0)
    {
        recvline[n]=0;
        if(fputs(recvline,stdout)==EOF)
        {
            printf("fputs\n");
            return 0;
        }
    }
    if(n<0)
    {
        printf("read\n");
        return 0;
    }
    exit(0);

}
