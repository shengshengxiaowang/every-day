#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
  int n,m,i,j,k=0,s;  //n是总人数，m是服务窗口数
  double sum=0;
  cin>>n>>m;  //输入n和m
  int a[n],b[m][n/m+1]; //定义等待数组和窗口二维数组

  for(i=0;i<n;i++)
  {
    cin>>a[i];
  }
  for(i=0;i<m;i++)  //初始化
  {
    for(j=0;j<n/m+1;j++)
    {
      b[i][j]=0;
    }
  }
  sort(a,a+n);  //排序

  j=0;k=0;
  for(i=0;i<n;)  //依次放入等待数组值
  {
    b[k++][j]=a[i++];
    if(i%m==0)
    {
      j++;
      k=0;
    }

  }

  for(i=0;i<m;i++)  //计算，k暂存前面所有时间，s每次加上k,就为每个窗口所有等待和
  {
    k=0;s=0;
    for(j=0;j<n/m+1;j++)
    {
      if(b[i][j]!=0)
      {
        k=k+b[i][j];
        s=s+k;
        //cout<<endl<<'#'<<k<<'#'<<endl;
      }
    }
    sum=s+sum;  //求出所有窗口等待和
  }
  cout<<endl<<sum/n<<endl;
}
