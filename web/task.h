#ifndef _TASK_
#define _TASK_
#include<iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/wait.h>
using namespace std;
const char* path="/home/sheng/Desktop/aaa";

const int BUFFER_SIZE=4096;

class task
{
private:
	int connfd;
public:
	task(){}
	task(int fd):connfd(fd){}
	~task(){}

	void response(char *message, int status)  //错误响应函数
	{
		char buf[512];
		sprintf(buf,"HTTP/1.1 %d OK\r\nConnection: Close\r\n""content-length:%zuu\r\n\r\n", status, strlen(message));
		sprintf(buf, "%s%s", buf, message);//把格式化的数据写入字符串中
		write(connfd,buf,strlen(buf));//写到文件中
	}
	void response_file(int size, int status)  //请求静态文件响应
	{
		char buf[128];
		sprintf(buf,"HTTP/1.1 %d OK\r\nConnection: Close\r\n""content-length:%d\r\n\r\n", status, size);
		write(connfd, buf, strlen(buf));
	}
	void response_get(char *filename);
    void response_post(char *filename, char *argv);
    void doit();
};

void task::doit()
{
	char buffer[BUFFER_SIZE];
	int size;
    while(1)  //读取
	{
		size=read(connfd,buffer,BUFFER_SIZE-1);
		if(size>0)//如果有数据的话
		{
			char method[5];//请求方法
			char filename[50];//文件
			int i=0,j=0;
			while(buffer[j]!=' ' && buffer[j]!='\0')//获取请求方法
			{
				method[i++]=buffer[j++];
			}
			j++;
			method[i]='\0';
			i=0;
			while(buffer[j]!=' ' && buffer[j]!='\0')//请求文件
			{
				filename[i++]=buffer[j++];
			}
			filename[i]='\0';

			if(strcasecmp(method, "GET")==0)  //如果是get方法
			{
				response_get(filename);
			}
			else if(strcasecmp(method,"POST")==0)  //如果是post方法
			{
				char argvs[100];
				memset(argvs, 0, sizeof(argvs));
				int k=0;
				char *ch=NULL;
				j++;
				while((ch=strstr(argvs,"Content-Length"))==NULL) //查找请求头部中的Content-Length行
				{
					k=0;
					memset(argvs,0,sizeof(argvs));
					while(buffer[j]!='\r' && buffer[j]!='\0')//不是换行不是结束
					{
						argvs[k++]=buffer[j++];
					}
					j++;
				}
				int length;
				char *str=strchr(argvs,':');  //查找字符串s中首次出现字符c的位置。 post数据长度
				str++;
				sscanf(str,"%d",&length);
				j=strlen(buffer)-length;    //从尾部获取请求数据
				k=0;
				memset(argvs,0,sizeof(argvs));
				while(buffer[j]!='\r' && buffer[j]!='\0')
				{
					argvs[k++]=buffer[j++];
				}
				argvs[k]='\0';

				response_post(filename, argvs);  //post
			}
			else  //其他方法
			{
				char message[512];
				sprintf(message,"<html><title>Tinyhttpd Error</title>");
				sprintf(message,"%s<body>\r\n", message);
				sprintf(message,"%s 501\r\n", message);
				sprintf(message,"%s <p>%s: Httpd does not implement this method",
				message,method);
				sprintf(message,"%s<hr><h3>The Tiny Web Server<h3></body>", message);
				response(message, 501);
			}

		}
 		else if(size<0)//读取失败，重新读取
		{
			break;
		}
	//sleep(3);
		close(connfd);
		break;
	}
}

void task::response_get(char *filename)//get
{
	char file[100];
	strcpy(file, path);
	int i = 0;
	bool is_dynamic = false;
	char argv[20];
	while(filename[i]!='?' && filename[i]!='\0')//没有问号
	{
		++i;
	}
	if(filename[i]=='?')//有问号，是动态请求
	{
		int j=i++;
		int k=0;
		while(filename[i]!='\0')  //分离参数和文件名
		{
			argv[k++]=filename[i++];
		}
		argv[k]='\0';
		filename[j]='\0';
		is_dynamic=true;
	}
	if(strcmp(filename,"/")==0)
	{
		strcat(file,"/index.html");
	}
	else
	{
		strcat(file,filename);
	}
	struct stat filestat;
	int ret=stat(file, &filestat);
	if(ret<0 || S_ISDIR(filestat.st_mode)) //如果不存在的话
	{
		char message[512];
		sprintf(message, "<html><title>Tinyhttpd Error</title>");
		sprintf(message, "%s<body>\r\n", message);
		sprintf(message, "%s 404\r\n", message);
		sprintf(message, "%s <p>GET: Can't find the file", message);
		sprintf(message, "%s<hr><h3>The Tiny Web Server<h3></body>",message);
		response(message, 404);
		return;
	}

	if(is_dynamic)
	{
		if(fork() == 0)
		{
			dup2(connfd, STDOUT_FILENO);
	    	execl(file, argv);
		}
		wait(NULL);
	}
	else
	{
		int filefd = open(file, O_RDONLY);
		response_file(filestat.st_size, 200);
		sendfile(connfd, filefd, 0, filestat.st_size);
	}
}

void task::response_post(char *filename, char *argvs)//post
{
	char file[100];
	strcpy(file, path);
	strcat(file, filename);
	struct stat filestat;
	int ret = stat(file, &filestat);
	printf("%s\n", file);
	if(ret < 0 || S_ISDIR(filestat.st_mode))
	{
		char message[512];
		sprintf(message,"<html><title>Tinyhttpd Error</title>");
		sprintf(message,"%s<body>\r\n", message);
		sprintf(message,"%s 404\r\n", message);
		sprintf(message,"%s <p>GET: Can't find the file", message);
		sprintf(message,"%s<hr><h3>The Tiny Web Server<h3></body>",message);
		response(message, 404);
		return;
	}

	char argv[20];
	int a,b;
	ret=sscanf(argvs,"a=%d&b=%d",&a,&b);
	if(ret<0||ret!=2)
	{
		char message[512];
		sprintf(message,"<html><title>Tinyhttpd Error</title>");
		sprintf(message,"%s<body>\r\n", message);
		sprintf(message,"%s 404\r\n", message);
		sprintf(message,"%s <p>GET: Parameter error", message);
		sprintf(message,"%s<hr><h3>The Tiny Web Server<h3></body>",message);
		response(message, 404);
		return;
	}
	sprintf(argv,"%d&%d",a,b);
	if(fork()==0)
	{
		dup2(connfd,STDOUT_FILENO);
		execl(file,argv);
	}
	wait(NULL);
}
#endif
