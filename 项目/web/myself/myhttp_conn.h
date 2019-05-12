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
    {};
    ~myhttp_conn()
    {};
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

//被process_read调用解析HTTP请求
    HTTP_CODE parse_request_line(char* text);
    HTTP_CODE parse_headers(char* text);
    HTTP_CODE parse_content(char* text);
    HTTP_CODE do_request();
    char* get_line()
    {
        return my_readbuf+my_startline;
    }
    LINE_STATUS parse_line();

//被process_write调用填充HTTP应答
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
    int my_sockfd;  //http连接的socket
    sockaddr_in my_address; //对方的socket

    char my_readbuf[READ_BUFFER_SIZE]; //读缓冲区
    int my_readidx;  //标识缓冲区中已经读入的客户数据的最后一个字节的下一个位置
    int my_checkedidx;  //当前正在解析的字符在读缓冲区中的位置
    int my_startline;  //当前正在解析的行的起始位置

    char my_writebuf[WRITE_BUFFER_SIZE]; //写缓冲区
    int my_writeidx;  //写缓冲区中待发送的字节数

    CHECK_STATE my_checkstate;  //主机状态机当前所处状态
    METHOD my_method;  //请求方法

    char my_realfile[FILENAME_LEN]; //客户请求的目标文件的完整路径
    char* my_url; //目标文件文件名
    char* my_version;  //HTTP协议版本号
    char* my_host;   //主机名
    int my_contentlength; //HTTP请求的消息体长度
    bool my_linger; //HTTP请求是否要保持连接

    char* my_fileaddress;//客户请求的目标文件被mmap到内存中的起始位置
    struct stat my_filestat; //目标文件状态，是否存在，目录或者文件等

    struct iovec my_iv[2];
    int my_ivcount;  //被写内存块的数量


};

#endif
