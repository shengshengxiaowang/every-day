#include<iostream>
using namespace std;
const int Max_length=640; //最大内存
int a,b;
struct freearea
{
    int ID;   //分区号
    int size; //分区大小
    int address;  //分区大小
    bool flag;  //使用状态，0为未占用，1为已占用
};
typedef struct DuNode  //双向链表结点
{
    freearea data;  //数据域
    DuNode *prior;  //指针域
    DuNode *next;
}*DuLinkList;

DuLinkList m_rid=new DuNode,m_last=new DuNode;//链表首尾指针

void main()
{
    
}
