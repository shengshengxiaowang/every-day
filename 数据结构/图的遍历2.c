//图的深搜遍历
#include <stdio.h>
int n,sum=0;
int a[20][20];
int b[20];

void dfs(int x)
{
    printf("%d ",x);
    sum++;
    int i;
    if(sum==n)
    {
        return;
    }
    for(i=1;i<=n;i++)
    {
        if(a[x][i]==1 && b[i]==0)
        {
            b[i]=1;
            dfs(i);
        }
    }
    return;
}
int main()
{
    int i,j;
    printf("请输入顶点总个数\n");
    scanf("%d",&n);

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            a[i][j]=0;
        }
        b[i]=0;

    }
    printf("请输入连接线:\n");
    while(scanf("%d%d",&i,&j)!=EOF)
    {
        a[i][j]=1;
        a[j][i]=1;
    }
    printf("深搜遍历序列为:");

    for(i=1;i<=n;i++)
    {
        if(b[i]==0)
        {
            b[i]=1;
            dfs(i);
        }
    }
    printf("\n");

}
