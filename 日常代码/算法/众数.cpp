//众数问题：求出一组数，出现次数最多的数和次数值
/*//递归求解
#include<iostream>
using namespace std;
int m=0,v=-1;

int s;
void sfun(int a,int b,int *c)
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

int main()
{
    cin>>s;
    int *a=new int(s);
    for(int i=0;i<s;i++)ss
    {
        cin >> a[i];
    }
    sfun(0,s,a);

    cout<<m<<" " <<v<<endl;
}*/

//hash求解
#include<iostream>
