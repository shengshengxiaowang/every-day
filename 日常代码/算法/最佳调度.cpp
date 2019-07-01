#include <iostream>
#include <algorithm>
using namespace std;


int a[30],s[30];
int n,k,m=1000;

bool cmp(int a,int b)
{
	return a>b;
}

void shensou(int dep,int tim) //dep为加入的第几个任务，tim为现在的时间
{
    if(tim>=m)     //如果已经比最大的大了就不用再放了
    {
        return;
    }
    if(dep>n)      //如果放完了
    {
        m=tim;
        return;
    }
    for(int i=1; i<=k; i++) 
    {
        if(s[i]+a[dep]<=m) //剪枝
        { 
            s[i]+=a[dep];
            shensou(dep+1,max(tim,s[i]));  //回溯
            s[i]-=a[dep];
        }
    }
    return;
}
	
	

int main() 
{
    cout<<endl;
    cin>>n>>k;
    for(int i=1; i<=n; i++) //输入每个时间
    {
        cin>>a[i];
    }
    sort(a+1,a+n+1,cmp);//排序
    shensou(1,0);//加入第一个时间，现在花费的时间是0；
    cout<<endl;
    cout<<m<<endl;
    cout<<endl;
    return 0;
}
