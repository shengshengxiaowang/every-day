//最大最小值
//动态规划
#include<iostream>
using namespace std;

int fun(int n,int m)
{
    int a[n];
    int f[n+1][n+1];
    int i,j,min,k;
    for(i=0;i<n;i++) //输入数据
    {
        cin>>a[i];
    }
    for(i=0;i<n;i++)  //初始化
    {
        for(j=0;j<m;j++)
        {
            f[i][j]=0;
        }
    }

    f[0][1]=a[0];       //前i个数分为1段
    for(i=1;i<n;i++)
    {
        f[i][1]=f[i-1][1]+a[i];//前i个和
    }

    for(i=2;i<n;i++) //前i个数分为j段
    {

        for(j=2;j<=m;j++) //j从2开始
        {

            min=999;
            for(k=1;k<i;k++)//选出最大值
            {
                int x=f[k][j-1]; //k个数分为j-1段最小最大值
                //前i个数减去前k个数分为一段
                if( (f[i][1]-f[k][1]) > f[k][j-1] )
                {
                    x=f[i][1]-f[k][1];
                }
                if(x<min)
                {
                    min=x;
                }
            }
            //cout<<min<<endl;
            f[i][j]=min;
        }

    }
    return f[n-1][m];
}


int main()
{
    int n,m;
    cin>>n>>m;
    cout<<fun(n,m)<<endl;

}
