//图的广搜遍历和出度入度计算
#include<stdio.h>
int n,head,tail;
int a[20][20];
int q[500];
int b[20];

void bfs(int x)
{
    int i;
    while(head<tail && tail<=n)
    {
        x=q[head];
        for(i=1;i<=n;i++)
        {
            if(a[x][i]==1 && b[i]==0)
            {
                q[tail]=i;
                tail++;
                b[i]=1;
            }
        }
        head++;
    }
}
int main()
{
    int i,j;
    printf("请输入顶点总个数:");
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
                a[i][j]=0;
        }
        b[i]=0;
    }
    printf("请输入各节点之间的关系:\n");
    while(scanf("%d%d",&i,&j)!=EOF)
    {
        a[i][j]=1;
        //a[j][i]=1;
    }
    head=1;
    tail=1;

    for(i=1;i<=n;i++)
    {
        if(b[i]==0)
        {
            q[tail]=i;
            tail++;
            b[i]=1;
            bfs(i);
        }
    }
    printf("广搜遍历顺序:\n");
    for(i=1;i<tail;i++)
    {
        printf("%d ",q[i]);
    }
    printf("\n");
    printf("邻接矩阵为:\n");
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }

    //出度
    int s;
    for(i=1;i<=n;i++)
    {
        s=0;
        for(j=1;j<=n;j++)
        {
            if(a[i][j]>0)
            {
                s++;
            }
        }
        printf("顶点%d的出度为:%d\n",i,s);
    }
    //入度
    for(i=1;i<=n;i++)
    {
        s=0;
        for(j=1;j<=n;j++)
        {
            if(a[j][i]>0)
            {
                s++;
            }
        }
        printf("顶点%d的入度为:%d\n",i,s);
    }
}
