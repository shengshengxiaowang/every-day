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
public:
    myString& operator+(const myString& str);  //串联字符串函数
    myString& operator+(char str);   //追加字符函数
    void swap(myString& str1,myString& str2);    //交换字符串函数
    int length();   //计算字符串长度函数
    //比较大小
    //索取子串
};

inline
int myString::length()   //计算字符串长度函数
{
    return strlen(data);
}

inline
void myString::swap(myString &str1,myString &str2)  //字符串交换函数s1,s2
{
    int a,b;
    a=strlen(str1.data);
    b=strlen(str2.data);
    char* p=new char[a+b+1]; //创建p临时存储s1
    strcpy(p,str1.data);
    delete[] str1.data;
    str1.data= new char[sizeof(b)+1];   //s1重新构值
    strcpy(str1.data,str2.data);
    delete[] str2.data;
    str2.data= new char[sizeof(a)+1];   //s2重新构值
    strcpy(str2 .data,p);
    delete[] p;
}


inline
myString& myString::operator+(char str)   //追加字符函数
{
    char *p=new char[strlen(data)+1];  //申请新空间暂时存储s1
    strcpy(p,data);
    delete[] data;           //删掉s1
    data=new char[strlen(&str)+strlen(p)+1];  //重新为s1申请空间
    strcpy(data,p);
    strcat(data,&str);
    delete[] p;     //删掉p
    return *this;
}

inline
myString& myString::operator+(const myString& str)   //连接字符串函数s1+s2
{
    char *p=new char[strlen(data)+1];  //申请新空间暂时存储s1
    strcpy(p,data);
    delete[] data;           //删掉s1
    data=new char[strlen(str.data)+strlen(p)+1];  //重新为s1申请空间
    strcpy(data,p);
    strcat(data,str.data);
    delete[] p;     //删掉p
    return *this;
}

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
/*很有必要*/    delete[] data;  //删掉s2
    data= new char[strlen(str.data)+1];  //申请空间
    strcpy(data,str.data);  //复制
    return *this;    //返回
}

inline
myString::~myString()
{
    delete[] data;
}


inline
ostream& operator<<(ostream& os, myString& str)
{
    os << str.get_cstr();
    return os;
}


#endif
