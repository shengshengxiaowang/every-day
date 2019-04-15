//众数问题：求出一组数，出现次数最多的数和次数值(有序数) ,不适用于一组数据中有多个众数
#include<iostream>
#include <vector>
using namespace std;
int m=0,v=-1;

int s;
void sfun(int a,int b,int *c)   //递归求解
{
    int i,k=0,n;
    n=(b-a)/2;
    n=c[n];
//cout<<k<<n<<" ** "<<endl;
    for(i=a;i<b;i++)   //计算中间数有几个
    {
        if(n==c[i])
        {
            k++;
        }
    }
    if(k>m)
    {
        m=k;
        v=n;
    }
    if(k>=(b-a)/2) //如果中间数的众数比数组一半大，则退出，不用计算
    {
//cout<<k<<n<<endl;
        return;
    }
    sfun(a,a+(b-a)/2,c);
    sfun(a+(b-a)/2,b,c);

}

void ssfun(int *num,int s)  //该方法只适合有序数组，若无序必须先进行排序；或者再增加数组用以记录每个数字出现次数，再进行比较
{
    int i,max=0,k=0,count=0,x;
    //vector<int> num(c,c+s);
    for(i=0;i<s;i++)
    {
        if(count==0)
        {
            x=num[i];
            ++count;
        }
        else if(x!=num[i])
        {
            if(count>max)
            {
                k=num[i-1];
                max=count;
            }
            count=0;
        }
        else
        {
            ++count;
        }
    }
    cout << max <<k << endl;
}

int main()
{
    cin>>s;
    int *a=new int(s);
    for(int i=0;i<s;i++)
    {
        cin >> a[i];
    }
    //sfun(0,s,a);
    ssfun(a,s);
    cout<<m<<" " <<v<<endl;
}
