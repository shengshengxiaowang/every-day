#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<unistd.h>

#define process_name_len 32 //进程名长度
#define default_mem_size 1024//内存大小
#define default_mem_start 0  //起始位置
#define ma_ff 1
#define ma_bf 2
#define ma_wf 3

struct free_block  //空闲块数据结构
{
    int size;       //空闲块大小
    int start_addr; //空闲块起始位置
    struct free_block *next;  //指向下一个空闲块
};
struct free_block *free_block_head=NULL; //空闲块链表的首地址

struct allocated_block
{
    int pid;       //进程id
    int size;      //进程大小
    int start_addr; //进程分配到的内存块的起始地址
    char process_name[process_name_len]; //进程名
    struct allocated_block *next;  //下一个指针
    //struct allocated_block *prior; //上一个指针
};
struct allocated_block *allocked_block_head=NULL;//分配内存块首地址

int free_block_count=0; //空闲块的个数初始为0
int mem_size=default_mem_size; //内存大小
int free_mem_size=0;   //当前空闲内存大小
int algorithm=ma_ff;   //当前分配算法，默认ff
static int pid=0;
int flag=0;     //标志内存是否已经被设置，如果设置过，则不能再设置

struct free_block* init_free_block(int mem_size);//初始化空闲内存块头指针
void menu();//显示菜单
int set_mem_size(); //设置内存大小
void set_algorithm();//设置分配算法
int set_mem_size() //设置内存大小,默认为之前设定的值为1024
{
    int size;
    if(flag!=0)  //如果内存大小已经被设置过了，则退出不能再设置
    {
        printf("已经设置过，不能重复设置\n");
        return 0;
    }
    printf("请输入总内存大小：\n");
    scanf("%d",&size);
    if(size>0)  //如果输入值大于0
    {
        free_mem_size=size; //空闲内存块大小即为总内存
        mem_size=size;  //内存大小更新
        free_block_head->size=size; //空闲内存块头指针内存大小更新
        flag=1;  //标志值设1.之后不能重新设置内存大小
        return 1;
    }
    else
    {
        printf("输入错误，自动返回\n");
        return 0;
    }
}

void menu()
{
    printf("1-设置内存大小(初始值为%d)\n",default_mem_size);
    printf("2-选择内存分配算法\n");
    printf("3-创建新进程\n");
    printf("4-删除进程\n");
    printf("5-显示内存使用情况\n");
    printf("0-退出\n");
}

//申请空闲块(默认为一块),初始化链表头指针，空闲块内存大小及起始位置define设定过了
struct free_block* init_free_block(int mem_size)
{
    struct free_block *fb;
    fb=(struct free_block*)malloc(sizeof(struct free_block));
    if(fb==NULL)  //如果没有成功申请到内存
    {
        printf("内存满了\n");
        return NULL;
    }
    free_mem_size=mem_size; //现在内存块空闲地址等于申请的总内存
    fb->size=mem_size; //空闲块内存大小为之前指定的1024
    fb->start_addr=default_mem_size; //空闲块起始地址为之前指定0
    fb->next=NULL;//链表下一个指向0

    return fb;
}

void set_algorithm()
{
    int a;
    printf("1.ff算法\n2.bf算法\n3.wf算法\n请选择：\n");
    scanf("%d",&a);
    getchar();  //吸收多的回车符号
}
int main()
{
    free_block_head=init_free_block(mem_size); //初始化空闲块的头指针，mem_size为之前设定的大小，函数返回值为头结点
    char choice;   
    pid =0;
    while(1)
    {
        menu();
        choice=getchar();
        getchar();
        switch(choice)
        {
            case '1':
                set_mem_size(); //设置内存大小
                break;
            case '2':
                set_algorithm(); //设置分配算法
                flag=1;
                break;
            case '3':
        }
    }
}