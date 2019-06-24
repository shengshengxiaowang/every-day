//整数变换问题
#include <iostream>
using namespace std;
int n,m,step=1; //定义m、n、step的全局变量
char a[20];
int select(int t,int i)//更换函数
{
    if(i==0)
    {
        return 3*t;
    }
    return t/2;
}

int shensou(int k,int num)//深搜，k为层数，num为当前值
{
    if(k>step)//如果超出深搜层数限定范围，就返回0，当返回到最上层时，主函数更新step值
    {
      return 0;
    }
    int t,i;
    for(i=0;i<2;i++)
    {
        t=select(num,i);
        //cout<<t<<' '<<k<<endl;
        if(t==m || shensou(k+1,t))  //如果满足m=n，或者下一步满足，下一步如果超出深搜层数限定范围，就返回0，最后去主函数更新深搜限定值
        {
          //cout<<'8';
          if(i==0)
          {
              a[k-1]='f';
          }
          else
          {
              a[k-1]='g';
          }
          return 1;
        }
    }
    return 0;
}

int main()
{
    cin>>n>>m;
    while(!shensou(1,n))
    {
      ++step;     //限定的深搜步数
      if(step>20)  //如果大于20步，直接返回
      {
          cout<<"找不到"<<endl;
          return 0;
      }
    }
    cout<<step<<endl;
    for(int i=step-1;i>=0;i--)//倒着输出
    {
      cout<<a[i];
    }
}
