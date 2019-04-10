//分解整数因子问题：不能去重！比如8应该为:1*8 2*4 2*2*2 就没有了，但是算法做出来后，还会多一个：4*2。待解决
#include<iostream>
#include<math.h>
using namespace std;
int count=0;
void fun(int n)
{
    for(int i=2;i<n/2;i++)
    {
        if(n%i==0)
        {
            count++;
            fun(n/i);
        }
    }
    return;
}
int main()
{
    int n;
    cin>>n;
    fun(n);
cout<<count+1<<endl;
}
