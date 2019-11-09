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
    struct free_block *prior;  //指向前一个空闲块
};
struct free_block *free_block_head=NULL; //空闲块链表的首地址
struct free_block *free_block_end=NULL;   //空闲块链表的尾地址

struct allocated_block   //已分配的数据结构
{
    int pid;       //进程id
    int size;      //进程大小
    int start_addr; //进程分配到的内存块的起始地址
    char process_name[process_name_len]; //进程名
    struct allocated_block *next;  //下一个指针
    struct allocated_block *prior; //上一个指针
};
struct allocated_block *allocked_block_head=NULL;//分配内存块首地址

int free_block_count=0; //空闲块的个数初始为0
int mem_size=default_mem_size; //内存大小
int free_mem_size=0;   //当前空闲内存大小
int algorithm=ma_ff;   //当前分配算法，默认ff
static int pid=0;       //进程号，即第几个进程
int flag=0;     //标志内存是否已经被设置，如果设置过，则不能再设置

struct free_block* init_free_block(int mem_size);//初始化空闲内存块头指针
void menu();//显示菜单
int set_mem_size(); //设置内存大小
void set_algorithm();//设置分配算法
void rearrange(int a);  //算法跳转函数，跳转到对应算法的函数中去
int rearrange_ff(); //ff算法初始化函数
int new_process();  //创建新进程函数
int allocated_mem(struct allocated_block *ab);  //内存分配算法函数
int allocated_ff(struct allocated_block *ab);  //内存分配ff算法

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

void menu()   //菜单函数
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

int allocated_ff(struct allocated_block *ab)  //内存分配ff算法
{
    int ret=0;
    struct free_block *pre=NULL,*ff=free_block_head;
    if(ff==NULL)  //ff指向空闲块头指针
    {
        return -1;
    }
    while(ff!=NULL)  //开始遍历链表
    {
        if(ff->size>=ab->size)  //遇到的第一个大小合适，则分配
        {
            ret=allocate(pre,ff)
        }
    }
}

int allocated_mem(struct allocated_block *ab)  //内存分配算法函数
{
    int ret=0; //分配是否成功标识
    struct free_block *fbt,*pre;
    int request_size=ab->size;
    fbt=pre=free_block_head; //指向空闲块头指针
    switch(algorithm)  
    {
        case ma_ff:
            ret=allocated_ff(ab);
            break;
    }
    return ret;
}

int new_process()  //创建新进程函数
{
    struct allocated_block *ab; //新空间结构体
    int ret;  //内存分配返回标识
    ab=(struct allocated_block*)malloc(sizeof(struct allocated_block));
    if(!ab)  //如果申请错误
    {
        exit(-5);
    }
    ab->next=NULL;
    printf("请输入内存大小:\n");
    scanf("%d",&ab->size);  //输入大小
    getchar();  //吸收回车字符

    ab->pid=pid+1;  //数据填入结构体
    sprintf(ab->process_name,"process-02%d",ab->pid);
    if(ab->size<=0)  //如果输入负数，返回
    {
        printf("输入错误，返回\n");
        free(ab);  //释放ab空间
        return -1;
    }
    //如果内存大小正确，则分配算法
    ret=allocated_mem(ab);  
    


    pid++;  //进程号 ++
}


int rearrange_ff()  //ff算法函数
{
    struct free_block *head=free_block_head; //指向空闲链表头指针
    struct free_block *forehand=NULL,*pre=NULL,*rear=NULL;
    int i;
    if(head==NULL)
    {
        return -1;
    }
    for(i=0;i<free_block_count-1;i++)
    {
        forehand=head;  //从头结点开始
        pre=forehand->next; //指向头结点的下一个
        rear=pre->next;  //指向头结点的下下一个
        while(pre->next!=NULL)
        {
            //比较第一个跟第二个空闲块的开始位置大小
            if(forehand==head&& forehand->start_addr>=pre->start_addr)
            {
                //如果是第一个结点起始位置大于第一个结点的起始位置，交换
                head->next=pre->next;//head的下一个指向第三个    
                pre->next=head;  //第二个的
                head=pre;
                forehand=head->next;
                pre=forehand->next;
                rear=pre->next;
            }
            else if(pre->start_addr >=rear->start_addr)
            {//比较其他的，如果前一个大于后一个
                pre->next=rear->next;//前一个的下一个等于后一个的下一个
                forehand->next=rear;//前一个的前一个的下一个指向后一个
                rear->next=pre;//后一个的下一个指向前一个
                forehand=rear;  //指针后移
                rear=pre->next;  //指针后移
            }
            else
            {
                forehand=pre;  //指针后移
                pre=rear;
                rear=rear->next;
            }
        }
    }
    return 0;
}


void rearrange(int a)  //算法跳转函数，跳转到对应算法的函数中去
{
    switch(a)
    {
        case ma_ff:  //define中用1表示ff算法
            rearrange_ff();
            break;
       // case ma_bf:  //


    }
}

void set_algorithm()
{
    int a;
    printf("1.ff算法\n2.bf算法\n3.wf算法\n请选择：\n");
    scanf("%d",&a);
    getchar();  //吸收多的回车符号
    if(a<=3&& a>=1)
    {
        printf("设置成功\n");
        algorithm=a;
        rearrange(a);
    }
    else
    {
        printf("错误，返回上一层\n");
    }
    return;    
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
                new_process();   //创建新进程  
                flag=1;
                break;
            //case '4':
        }
    }
}