#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define MAX 100
#define N 10
typedef struct
{
    int x;   //横坐标
    int y;  //纵坐标
    int place;   //用来记录上一结点
}node;             //队列

typedef struct
{
    node data[MAX];  //队列
    int head;    //对头
    int end;      //对尾

}queue;


queue *create_queue()  //初始化队
{
    queue *p;
    p=(queue *)malloc(sizeof(queue));
    p->head=-1;      //初始化头指针为0
    p->end=1;       //初始化尾指针为-1
    return p;
}

int empty_queue(queue *p)   //判队空
{
    if (p->head==p->end)
        return 0;
    else
        return 1;
}

void Iputqueue(queue *p,node s)    //入队
{
    //if (empty_queue(p))
    //{
        p->data[++(p->end)] = s;//将元素s入栈（尾指针先加，因为首次是从-1开始的）
        //p->head=(p->head+1)%
        //printf("*** %d %d \n",p->head,p->end);
    //}
}

int myself_rand()
{
    srand(time(NULL));
    return rand()%11;
}

void Init_maze(int maze[N][N],int n)  //从文件中读取数据，初始化迷宫size_t
{
    int my_rand;
    my_rand=myself_rand();
//printf("\n* %d* *\n",my_rand);
	FILE *file = fopen("tezt.txt", "r");
    int i,j;
    fseek(file,my_rand,SEEK_SET);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n; )
		{
			char ch=fgetc(file);
			if(ch=='0' || ch=='1')
			{
				maze[i][j]=ch-'0';//将字符类型转为整型
				j++;
			}
		}
	}

    for(i=0;i<=n+12;i++)
    {
        printf("■");
    }
    printf("\n");
    for (i=0;i<n;i++)        //打印迷宫
    {
        printf("■ ");
        for (j=0;j<n;j++)
        {
            if(maze[i][j]==1)
            {
                printf("■ ");
            }
            else
            {
                printf("  ");
            }
        }
            //printf("%d,", maze[j][i]);
        printf("■");
        printf("\n");

    }
    for(i=0;i<=n+12;i++)
    {
        printf("■");
    }
    printf("\n");
}



int import()
{
    queue *p;
    int M[N][N];
    node head,end,s;
    int i, j=0, x,f=0,ff=0;
    Init_maze(M,N);   //从文件中读取迷宫
    p = create_queue();               //调用函数 初始化队

    if(M[0][0]==1)
    {
        printf("没有出口\n");
        return 0;
    }

    head.x=0;
    head.y=0;
    head.place=0;            //起始坐标 和起始位置（H.place=0）打包在变量H中
    end.x = 9;
    end.y = 9;               //同理尾位置打包在E变量
    Iputqueue(p, head);          //将起始位置入队
    M[head.x][head.y]=2;        //标记走过
    while(p->head!=p->end)     //头指针没追上尾指针 表示有路，追上了退出 无路
    {
        p->head++;     //每次头指针后移一位
        for (i=1;i<=4;i++)               //四个方向的循环
        {                               /*将头指针里的数据拿出来作为 参考点 遍历其周围四个方向*/
            s.x = p->data[p->head].x;
            s.y = p->data[p->head].y;
            s.place = p->head;//将参考点坐标 记下 它周围有满足条件的坐标时 一起入队（方便找到出口时可以根据线索返回）
            switch (i)
            {
                case 1:         //上方向
                {
                    if (M[s.x-1][s.y]==0  &&  s.x!=0)
                    {
                        f=1;
                        s.x=s.x-1;
                        s.y=s.y;
                        Iputqueue(p,s);
                        M[s.x][s.y] = 2;
                    }
                }; break;
                case 2:        //右方向
                {
                    if (M[s.x][s.y + 1]==0  && s.y!=9 )
                    {
                        f=1;
                        s.x=s.x;
                        s.y=s.y+1;
                        Iputqueue(p,s);
                        M[s.x][s.y] = 2;
                    }
                }; break;
                case 3:       //下方向
                {
                    if (M[s.x+1][s.y]==0  &&  s.x!=9)
                    {
                        f=1;
                        s.x=s.x+1;
                        s.y=s.y;
                        Iputqueue(p,s);
                        M[s.x][s.y]=2;
                    }
                }; break;
                case 4:       //左方向
                {

                    if (M[s.x][s.y-1]==0  && s.y!=0)
                    {
                        f=1;
                        s.x=s.x;
                        s.y=s.y-1;
                        Iputqueue(p,s);
                        M[s.x][s.y]=2;
                    }
                }; break;
            }

        }

        //printf("*** %d %d \n",p->head,p->end);
        if (p->data[p->head].x==end.x && p->data[p->head].y==end.y)//找到出口 退出循环
        {
            ff=1;
            break;
        }

    }

    /*for (j=0;j<10;j++)
    {
        for (i = 0; i<10; i++)
            printf("%d,", M[j][i]);
        printf("\n");

    }        //打印迷宫*/
    if(ff==0)
    {
        printf("没有出口\n");
        return 0;
    }

    int lu[N][N];
    for(i=0;i<=N;i++)
    {
        for(j=0;j<=N;j++)
        {
            lu[i][j]=0;
        }
    }
    lu[0][0]=1;
    lu[N-1][N-1]=1;
    x=p->head;      //结束时的坐标的下标
    while(x>0)
    {
        printf("(%d,%d)\n", p->data[x].x, p->data[x].y);
        lu[p->data[x].x][p->data[x].y]=1;
        x=p->data[x].place;//上一个（结点）的下标是本（结点）的place存的值
    }
    int n=N;
    for(i=0;i<=n+12;i++)
    {
        printf("■");
    }
    printf("\n");
    for (i=0;i<n;i++)        //打印迷宫
    {
        printf("■ ");
        for (j=0;j<n;j++)
        {
            if(M[i][j]==1)
            {
                printf("■ ");
            }
            else if(lu[i][j]==1)
            {
                printf("☆ ");
            }
            else
            {
                printf("  ");
            }
        }
            //printf("%d,", maze[j][i]);
        printf("■");
        printf("\n");

    }
    for(i=0;i<=n+12;i++)
    {
        printf("■");
    }
    printf("\n");


    return 0;
}

int main()
{
    int flag;
    while(1)
    {
        system("clear");
        printf("--------迷宫--------\n");
        import();
        printf("1-重新生成迷宫\n");
        printf("0-退出");
        scanf("%d",&flag);
        if(flag!=1)
        {
            break;
        }
    }
}
