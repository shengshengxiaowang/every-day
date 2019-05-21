//删数问题
//将输入正整数转换为字符串，在不改变顺序情况下，取出位数为x的最小值
#include<iostream>
using namespace std;
int main()
{
    long n;
    int x,i,n1,c=0,m=10,f;
    cin>>n>>x;//x是剩多少数
    n1=n;//n1代替n
    while(n1>0)
    {
        n1=n1/10;
        c++;//c是位数
    }
    n1=n;
    int a[c];
    int b=0;
    for(i=c-1;i>=0;i--)       //转换成字符串a[]
    {
        a[i]=n1%10;
        n1=n1/10;
    }

    for(i=c-x;i>=0;i--)          //从c-x倒着遍历，找到第一位m
    {
        //cout<<a[i]<<endl;
        if(a[i]<m &&a[i]!=0)     //第一位循环单独放出来，因为不能取 0
        {
            m=a[i];
            f=i;//f标记i位置
            if(m==1) //如果不是个位数的话，取1就是最小，可以直接跳出
            {
                break;
            }
        }
    }
    b=b*10+m;       //将第一位放入b

    while(--x)         //继续循环,位数为退出条件
    {
        m=10;
        for(i=c-x;i>f;i--)   //找到下一位m，从c-x开始倒序到标记的f;
        {
            //cout<<i<<a[i]<<endl;
            if(a[i]<=m)
            {
                m=a[i];
                n1=i;//n1先暂代f,直接保存为f会影响循环退出
            }
        }
        f=n1;//更新f
        b=b*10+m;//放入b
    }
    cout<<b<<endl;
}
