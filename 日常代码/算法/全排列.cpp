//全排列问题：打印出一个序列的全部顺序（observe函数为去重函数，如果当前k值与i值重复，则跳过这一轮）

#include<iostream>
using namespace std;
void swap(char &a,char &b) //交换
{
    int k=a;
    a=b;
    b=k;
}

bool observe(char *s,int n,char a,int k)  //查重 如果跟后面数字一样，则交换结果一样，则不需要交换，也不需要递归
{
    for(int i=k+1;i<n;i++)
    {
        if(s[i]==a)
        {
            return false;
        }
    }
    return true;
}

void prim(int k,char *s,int n)   //递归
{
    if(k==n-1)
    {
        cout <<s<<endl;
        return;
    }
    for(int i=k;i<n;i++)
    {
        if(observe(s,n,s[i],i)==0)
        {
            continue;
        }
        swap(s[i],s[k]);
        prim(k+1,s,n);
        swap(s[i],s[k]);
    }
}


int main()
{
    int n;
    cin>>n;
    char *s=new char(n);
    cin >> s;
    prim(0,s,n);
}
