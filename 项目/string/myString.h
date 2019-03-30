#ifndef  _MYSTRING_
#define _MYSTRING_
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include <cstring>
#include <malloc.h>
#include <cstdio>
using namespace std;
class myString
{
public:
    myString(const char *cstr =NULL);    //构造函数
    myString(const myString& str);   //拷贝构造
    myString& operator=(const myString& str);  //拷贝赋值函数
    ~myString(); //析构函数
    char* get_cstr() //返回输出
    {
        return data;
    }
private:
    char* data;  //字符串指针
};

inline
myString::myString(const char *cstr)  //构造函数
{
    if(cstr)  //如果初值不为空的话
    {
        data= new char[strlen(cstr)+1];
        strcpy(data,cstr);
    }
    else       //未指定初值
    {
        data= new char[1];
        *data='\0';
    }
}

inline
myString::myString(const myString& str)   //拷贝构造函数
{
    data= new char[strlen(str.data)+1];  //构造空间
    strcpy(data,str.data);   //复制
}

inline
myString& myString::operator=(const myString& str)  //拷贝赋值函数s2=s1
{
    if(this == &str)    //如果两个相等
    {
        return *this;
    }
    delete[] data;  //删掉s2
    data= new char[strlen(str.data)+1];  //申请空间
    strcpy(data,str.data);  //复制
    return *this;    //返回
}

inline
myString::~myString()
{
    delete[] data;
}

ostream&
operator<<(ostream& os, myString& str)
{
    os << str.get_cstr();
    return os;
}

#endif
