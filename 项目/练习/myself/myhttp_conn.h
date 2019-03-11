#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include<iostream>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include<signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdarg.h>
#include <errno.h>
#include"mylocker.h"

class myhttp_conn
{

public:
    static const int FILENAME_LEN=200;  //文件名的最大长度
    static const int READ_BUFFER_SIZE=2048; //读缓冲区的大小
    static const int WRITE_BUFFER_SIZE=1024;  //写缓冲区的大小
    enum METHOD  //HTTP请求方法
    {
        GET=0,POST,HEAD,PUT,DELETE,TRACE,OPTIONS,CONNECT,PATCH
    };
    enum CHECK_STATE//主状态机状态
    {
        CHECK_STATE_REQUESTLINE=0,CHECK_STATE_HEADER,CHECK_STATE_CONTENT
    };
    enum HTTP_CODE  //服务器处理HTTP请求的可能结果
    {
        NO_REQUEST, GET_REQUEST, BAD_REQUEST, NO_RESOURCE, FORBIDDEN_REQUEST, FILE_REQUEST, INTERNAL_ERROR, CLOSED_CONNECTION
    };

    enum LINE_STATUS //行的读取状态
    {
        LINE_OK = 0, LINE_BAD, LINE_OPEN
    };
public:
    myhttp_conn()
    {}
    ~myhttp_conn()
    {}
public:
    void init(int sockfd,const sockaddr_in & addr);//初始化新接受的连接
    void close_conn(bool real_close=true); //关闭连接
    void process();//处理客户请求
    bool read(); //读操作
    bool write(); //写操作
private:
    void init();
    HTTP_CODE process_read(); //解析HTTP请求
    bool process_write(HTTP_CODE ret); //填充应答

    HTTP_CODE parse_request_line(char* text);
    HTTP_CODE parse_headers(char* text);
    HTTP_CODE parse_content(char* text);
    HTTP_CODE do_request();
    char* get_line()
    {
        return my_readbuf+my_startline;
    }
    LINE_STATUS parse_line();

    void unmap();
    bool add_response(const char* format, ... );
    bool add_content(const char* content );
    bool add_status_line(int status, const char* title );
    bool add_headers(int content_length );
    bool add_content_length(int content_length );
    bool add_linger();
    bool add_blank_line();

public:
    static int my_epollfd;  //epoll事件表
    static int my_usercount;  //用户数量

private:
    int m_sockfd;  //http连接的socket
    sockaddr_in my_address; //对方的socket

    
};

#endif
