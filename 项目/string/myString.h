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
    myString& operator=(char str);  //赋字符串函数
    myString& operator+(const myString& str);  //串联字符串函数
    myString& operator+(char str);   //追加字符函数
    void swap(myString& str1,myString& str2);    //交换字符串函数
    size_t length();   //计算字符串长度函数
    bool operator==(const myString& str);   //是否相等s1==s2
    bool operator==(const char str);        //是否与字符串相等
    bool operator!=(const myString& str);   //是否不相等s1!=s2
    bool operator!=(const char str);        //是否与字符串不相等
    bool operator<(const myString& str);   //s1<s2
    bool operator<(const char str);       //s1<字符串
    bool operator>(const myString& str);   //s1>s2
    bool operator>(const char str);       //s1>字符串
    //int compare(const myString& str1,const myString& str2);  //比较s1,s2大小
    char* substr(const int a,int b);//索取子串
    char& operator[](const int n);  //[]取出第n个字符
    friend istream& operator>>(istream &is, myString &str);//输入
	friend ostream& operator<<(ostream &os, myString &str);//输出

};

inline
char* myString::substr(const int a,int b) //索取子串
{
    int l=strlen(data);
    if(a>=l || b<a)   //出错处理
    {
        return  data;
    }
    if(b>l) //出错处理
    {
        b=l;
    }
    int i=0,j;
    char* s=new char[b-a+1];

    for(j=a;j<=b;j++)
    {
        s[i++]=data[j];
    }
    s[i]='\0';
    return s;
}


istream&
operator>>(istream& is, myString& str)//输入
{
	char tem[1000];  //申请一块内存
	is>>tem;
	str.data = new char[strlen(tem)+1];
	strcpy(str.data,tem);
	return is;
}

ostream&
operator<<(ostream& os,myString& str)//输出,为了实现cout<<a<<b的连续输出，需要返回输出流
{
    os << str.get_cstr();
        return os;
}

inline
char& myString::operator[](const int n)
{
    int a=strlen(data);
    if(n>=a)
    {
        return data[a-1]; //错误处理
    }
	else
    {
        return data[n];
    }
}

/*inline
int myString::compare(const myString& str1,const myString& str2)
{
    if(strcmp(str1.data,str2.data)==0)  //如果相等，返回0
    {
        return 0;
    }
    else if(strcmp(str1.data,str2.data)>0)  //如果大于，返回1
    {
        return 1;
    }
    else            //如果小于，返回-1
    {
        return -1;
    }

}*/

inline
bool myString::operator>(const myString& str)  //s1>s2
{
    if(strcmp(data,str.data)>0)    //如果小于0
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline
bool myString::operator>(const char str) //s1>字符串
{
    if(strcmp(data,&str)>0)    //如果大于0
    {
        return true;
    }
    else
    {
        return false;
    }
}



inline
bool myString::operator<(const myString& str)  //s1<s2
{
    if(strcmp(data,str.data)<0)    //如果小于0
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline
bool myString::operator<(const char str)  //s1<字符串
{
    if(strcmp(data,&str)<0)    //如果小于0
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline
bool myString::operator!=(const myString& str)//比较是否不相等s1!=s2
{
    if(strcmp(data,str.data))
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline
bool myString::operator!=(const char str)// 是否与字符串不相等
{
    if(strcmp(data,&str))
    {
        return true;
    }
    else
    {
        return false;
    }
}


inline
bool myString::operator==(const myString& str)//比较是否相等s1==s2
{
    if(strcmp(data,str.data))    //如果相等，if(0),则假
    {
        return false;
    }
    else
    {
        return true;
    }
}

inline
bool myString::operator==(const char str)//比较是否相等s1==s2
{
    if(strcmp(data,&str))    //如果相等，if(0),则假
    {
        return false;
    }
    else
    {
        return true;
    }
}

inline
size_t myString::length()   //计算字符串长度函数
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
myString& myString::operator=(char str)  //赋字符串函数
{

/*很有必要*/    delete[] data;  //删掉
    data= new char[strlen(&str)+1];  //申请空间
    strcpy(data,&str);  //复制
    return *this;    //返回
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



#endif
