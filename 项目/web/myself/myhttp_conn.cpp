#include "myhttp_conn.h"
//定义http相应的一些状态
const char* ok_200_title="OK\n";  //确定
const char* error_400_title="Bad Request\n";  //错误请求
const char* error_400_form="Your request has bad syntax or is inherently impossible to satisfy.\n";  //您的请求语法错误或者根本无法满足
const char* error_403_title="Forbidden\n";//禁止
const char* error_403_form="You do not have permission to get file from this server.\n"; //你没有从服务器获取此文件的权限
const char* error_404_title="Not Found\n";//未找到
const char* error_404_form="The requested file was not found on this server.\n";//在服务器上找不到请求的文件
const char* error_500_title="Internal Error\n"; //内部错误
const char* error_500_form="There was an unusual problem serving the requested file.\n";//为请求的文件提供服务时出现异常问题

const char* doc_root="/var/www/html"; //网站根目录

int setnonblocking(int fd)  //设置非阻塞
{
    int old_option=fcntl(fd, F_GETFL);//获得文件状态标记
    int new_option=old_option | O_NONBLOCK;//非阻塞I/O
    fcntl(fd,F_SETFL,new_option); //设置新的状态描述符
    return old_option;
}

void addfd(int epollfd,int fd,bool one_shot)//向事件表中注册新的事件
{
    epoll_event event;
    event.data.fd=fd;
    event.events=EPOLLIN | EPOLLET | EPOLLRDHUP;
    if(one_shot)
    {
        event.events |= EPOLLONESHOT;
    }
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
    setnonblocking(fd);
}

void removefd(int epollfd, int fd) //从事件表中删除一个事件
{
    epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,0);
    close(fd);
}

void modfd(int epollfd,int fd,int ev)//修改事件表中的事件属性
{
    epoll_event event;
    event.data.fd=fd;
    event.events=ev | EPOLLET | EPOLLONESHOT | EPOLLRDHUP;
    epoll_ctl(epollfd,EPOLL_CTL_MOD,fd,&event );
}


int myhttp_conn::my_epollfd = -1; //epoll事件表
int myhttp_conn::my_usercount = 0; //用户数量

void myhttp_conn::close_conn(bool real_close)//关闭连接
{
    if(real_close && (my_sockfd!=-1 ))
    {
        removefd(my_epollfd, my_sockfd); //删除该事件
        my_sockfd = -1;
        my_usercount--;//用户数量-1
    }
}

void myhttp_conn::init(int sockfd,const sockaddr_in & addr) //初始化新的连接
{
    my_sockfd=sockfd;
    my_address=addr;
    int error=0;
    socklen_t len=sizeof(error);
    getsockopt(my_sockfd,SOL_SOCKET,SO_ERROR,&error,&len); //获取套接口
    int reuse=1;
    setsockopt(my_sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));//设置套接口
    addfd( my_epollfd,sockfd,true); //添加进事件表
    my_usercount++;//用户数量加１
    init();
}

void myhttp_conn::init() //初始化数据
{
    my_checkstate = CHECK_STATE_REQUESTLINE;
    my_linger = false;

    my_method = GET;
    my_url = 0;
    my_version = 0;
    my_contentlength = 0;
    my_host = 0;
    my_startline = 0;
    my_checkedidx = 0;
    my_readidx = 0;
    my_writeidx = 0;
    memset(my_readbuf,'\0',READ_BUFFER_SIZE);
    memset(my_writebuf,'\0',WRITE_BUFFER_SIZE);
    memset(my_realfile,'\0',FILENAME_LEN );
}

myhttp_conn::LINE_STATUS myhttp_conn::parse_line()
{
    char temp;
    for ( ;my_checkedidx<my_readidx;++my_checkedidx) //从当前正在解析的字符位置到客户数据最末尾
    {
        temp=my_readbuf[my_checkedidx];//读缓冲区
        if(temp=='\r') //遇到回车符
        {
            if((my_checkedidx+1)==my_readidx)//如果读取完毕
            {
                return LINE_OPEN;
            }
            else if(my_readbuf[my_checkedidx+1]=='\n')//如果下一个是换行符
            {
                my_readbuf[my_checkedidx++]='\0';
                my_readbuf[my_checkedidx++]='\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
        else if(temp=='\n') //如果遇到换行符
        {
            if((my_checkedidx>1) && (my_readbuf[my_checkedidx-1]=='\r'))
            {
                my_readbuf[my_checkedidx-1]='\0';
                my_readbuf[my_checkedidx++]='\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
    }

    return LINE_OPEN;
}

bool myhttp_conn::read()  //读操作
{
    if(my_readidx>=READ_BUFFER_SIZE)//如果超出缓冲区
    {
        return false;
    }

    int bytes_read = 0;
    while(true)
    {
        bytes_read=recv(my_sockfd, my_readbuf + my_readidx,READ_BUFFER_SIZE-my_readidx,0);//接收数据

        if(bytes_read==-1)
        {
            if(errno==EAGAIN || errno==EWOULDBLOCK) //如果是非阻塞编程错误，继续接收即可，不破坏同步
            {
                break;
            }
            return false; //否则返回错误
        }
        else if(bytes_read==0)
        {
            return false;
        }

        my_readidx += bytes_read; //更新字符位置
    }
    return true;
}

myhttp_conn::HTTP_CODE myhttp_conn::parse_request_line( char* text )
{
    my_url=strpbrk(text," \t"); //在test中找到 \t,返回目标文件名位置
    if(!my_url)
    {
        return BAD_REQUEST;
    }
    *my_url++='\0';

    char* method = text;
    if(strcasecmp(method,"GET")==0) //使用get方法
    {
        my_method=GET;
    }
    else
    {
        return BAD_REQUEST;
    }

    my_url+=strspn(my_url," \t");
    my_version=strpbrk(my_url," \t");
    if(!my_version ) //HTTP协议版本号
    {
        return BAD_REQUEST;
    }
    *my_version++='\0';
    my_version+=strspn(my_version," \t" );
    if(strcasecmp(my_version,"HTTP/1.1")!=0)
    {
        return BAD_REQUEST;
    }

    if(strncasecmp(my_url,"http://",7)==0)
    {
        my_url+=7;
        my_url=strchr(my_url,'/');
    }

    if(!my_url || my_url[0]!='/')
    {
        return BAD_REQUEST;
    }

    my_checkstate=CHECK_STATE_HEADER; //检查状态
    return NO_REQUEST;
}

myhttp_conn::HTTP_CODE myhttp_conn::parse_headers(char* text)
{
    if(text[0]=='\0')
    {
        if(my_method==HEAD)
        {
            return GET_REQUEST;
        }

        if(my_contentlength!=0)
        {
            my_checkstate=CHECK_STATE_CONTENT;
            return NO_REQUEST;
        }

        return GET_REQUEST;
    }
    else if(strncasecmp(text,"Connection:",11)==0)
    {
        text+=11;
        text+=strspn(text," \t");
        if(strcasecmp(text,"keep-alive")==0)
        {
            my_linger=true;
        }
    }
    else if(strncasecmp(text,"Content-Length:",15)==0)
    {
        text+=15;
        text+=strspn(text," \t");
        my_contentlength=atol(text);//转换成长整形
    }
    else if(strncasecmp(text,"Host:",5)==0)
    {
        text+=5;
        text+=strspn(text," \t");
        my_host=text;
    }
    else
    {
        printf("oop!unknow header %s\n",text );
    }

    return NO_REQUEST;

}

myhttp_conn::HTTP_CODE myhttp_conn::parse_content(char* text)
{
    if(my_readidx>=(my_contentlength+my_checkedidx))//如果消息长度加字符位置大于总长度
    {
        text[my_contentlength]='\0';
        return GET_REQUEST;
    }

    return NO_REQUEST;
}

myhttp_conn::HTTP_CODE myhttp_conn::process_read()//解析HTTP请求
{
    LINE_STATUS line_status=LINE_OK;
    HTTP_CODE ret=NO_REQUEST;
    char* text=0;

    while(((my_checkstate==CHECK_STATE_CONTENT)&&(line_status==LINE_OK))
                ||((line_status=parse_line())==LINE_OK))
    {
        text=get_line();
        my_startline=my_checkedidx;
        printf("got 1 http line:%s\n",text);

        switch(my_checkstate)
        {
            case CHECK_STATE_REQUESTLINE:
            {
                ret=parse_request_line(text);
                if(ret==BAD_REQUEST)
                {
                    return BAD_REQUEST;
                }
                break;
            }
            case CHECK_STATE_HEADER:
            {
                ret=parse_headers(text);
                if(ret==BAD_REQUEST)
                {
                    return BAD_REQUEST;
                }
                else if(ret==GET_REQUEST)
                {
                    return do_request();
                }
                break;
            }
            case CHECK_STATE_CONTENT:
            {
                ret=parse_content(text);
                if(ret==GET_REQUEST)
                {
                    return do_request();
                }
                line_status=LINE_OPEN;
                break;
            }
            default:
            {
                return INTERNAL_ERROR;
            }
        }
    }

    return NO_REQUEST;
}

myhttp_conn::HTTP_CODE myhttp_conn::do_request()
{
    strcpy(my_realfile,doc_root);
    int len=strlen(doc_root);
    strncpy(my_realfile+len,my_url,FILENAME_LEN-len-1);
    if(stat(my_realfile,&my_filestat)<0)
    {
        return NO_RESOURCE;
    }

    if(!(my_filestat.st_mode & S_IROTH))
    {
        return FORBIDDEN_REQUEST;
    }

    if(S_ISDIR(my_filestat.st_mode))
    {
        return BAD_REQUEST;
    }

    int fd=open(my_realfile,O_RDONLY);
    my_fileaddress=(char*)mmap(0,my_filestat.st_size,PROT_READ,MAP_PRIVATE,fd,0);
    close(fd);
    return FILE_REQUEST;
}

void myhttp_conn::unmap()
{
    if(my_fileaddress)
    {
        munmap(my_fileaddress,my_filestat.st_size);
        my_fileaddress=0;
    }
}

bool myhttp_conn::write()
{
    int temp=0;
    int bytes_have_send=0;
    int bytes_to_send=my_writeidx;
    if(bytes_to_send==0)
    {
        modfd(my_epollfd,my_sockfd,EPOLLIN);
        init();
        return true;
    }

    while( 1 )
    {
        temp=writev(my_sockfd,my_iv,my_ivcount);
        if(temp<=-1)
        {
            if(errno==EAGAIN)
            {
                modfd(my_epollfd,my_sockfd,EPOLLOUT);
                return true;
            }
            unmap();
            return false;
        }

        bytes_to_send-=temp;
        bytes_have_send+=temp;
        if(bytes_to_send<=bytes_have_send)
        {
            unmap();
            if(my_linger)
            {
                init();
                modfd(my_epollfd,my_sockfd,EPOLLIN);
                return true;
            }
            else
            {
                modfd(my_epollfd,my_sockfd,EPOLLIN);
                return false;
            }
        }
    }
}

bool myhttp_conn::add_response(const char* format,...)
{
    if(my_writeidx>=WRITE_BUFFER_SIZE)
    {
        return false;
    }
    va_list arg_list;
    va_start(arg_list,format);
    int len=vsnprintf(my_writebuf+my_writeidx,WRITE_BUFFER_SIZE-1-my_writeidx,format,arg_list);
    if(len>=(WRITE_BUFFER_SIZE-1-my_writeidx))
    {
        return false;
    }
    my_writeidx+=len;
    va_end(arg_list);
    return true;
}

bool myhttp_conn::add_status_line(int status,const char* title)
{
    return add_response("%s %d %s\r\n","HTTP/1.1",status,title);
}

bool myhttp_conn::add_headers(int content_len)
{
    add_content_length(content_len);
    add_linger();
    add_blank_line();
/* */    return  0;
}

bool myhttp_conn::add_content_length(int content_len)
{
    return add_response("Content-Length: %d\r\n",content_len);
}

bool myhttp_conn::add_linger()
{
    return add_response("Connection: %s\r\n",(my_linger==true)?"keep-alive":"close");
}

bool myhttp_conn::add_blank_line()
{
    return add_response("%s","\r\n");
}

bool myhttp_conn::add_content(const char* content)
{
    return add_response("%s",content);
}

bool myhttp_conn::process_write(HTTP_CODE ret)
{
    switch(ret)
    {
        case INTERNAL_ERROR:
        {
            add_status_line(500,error_500_title);
            add_headers(strlen(error_500_form));
            if(!add_content(error_500_form))
            {
                return false;
            }
            break;
        }
        case BAD_REQUEST:
        {
            add_status_line(400,error_400_title);
            add_headers(strlen(error_400_form));
            if(!add_content(error_400_form))
            {
                return false;
            }
            break;
        }
        case NO_RESOURCE:
        {
            add_status_line(404,error_404_title);
            add_headers(strlen(error_404_form));
            if(!add_content(error_404_form))
            {
                return false;
            }
            break;
        }
        case FORBIDDEN_REQUEST:
        {
            add_status_line(403,error_403_title);
            add_headers(strlen(error_403_form));
            if(!add_content(error_403_form))
            {
                return false;
            }
            break;
        }
        case FILE_REQUEST:
        {
            add_status_line(200,ok_200_title);
            if(my_filestat.st_size!=0)
            {
                add_headers(my_filestat.st_size);
                my_iv[0].iov_base=my_writebuf;
                my_iv[0].iov_len=my_writeidx;
                my_iv[1].iov_base=my_fileaddress;
                my_iv[1].iov_len=my_filestat.st_size;
                my_ivcount=2;
                return true;
            }
            else
            {
                const char* ok_string="<html><body></body></html>";
                add_headers(strlen(ok_string));
                if(!add_content(ok_string))
                {
                    return false;
                }
            }
        }
        default:
        {
            return false;
        }
    }

    my_iv[0].iov_base=my_writebuf;
    my_iv[0].iov_len=my_writeidx;
    my_ivcount=1;
    return true;
}

void myhttp_conn::process()
{
    HTTP_CODE read_ret=process_read();
    if(read_ret==NO_REQUEST)
    {
        modfd(my_epollfd,my_sockfd,EPOLLIN);
        return;
    }

    bool write_ret=process_write(read_ret);
    if(!write_ret)
    {
        close_conn();
    }
    modfd(my_epollfd,my_sockfd,EPOLLOUT);
}
