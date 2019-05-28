/*#include<iostream>
#include<cstring>
using namespace std;

int main()
{
    int f[100][100];
    char a[100];
    char b[100];
    int i,j,flag,al,bl;
    cout<<endl;

    cin>>a>>b;
    al=strlen(a);
    bl=strlen(b);
    for(i=1;i<=al;i++) //初始化
    {
        f[i][0]=i;    //a到i的距离
    }
    for(i=1;i<=bl;i++)
    {
        f[0][i]=i;    //b到j的距离
    }
    for(i=1;i<=al;i++)
    {
      for(j=1;j<=bl;j++)
        {
            flag=1;
            if(a[i-1]==b[j-1])
            {
                flag=0;
            }             //  增            减          换
            f[i][j]=min(min(f[i-1][j]+1,f[i][j-1]+1),f[i-1][j-1]+flag);
        }
    }
    cout<<endl<<f[al][bl]<<endl<<endl;
    return 0;
}


#include <iostream>
#include <cstring>
using namespace std;
const int s=15;
int main()
{
    int vi[s]={0,9,5,1,6,6,7};
    int wi[s]={0,10,3,7,2,5,4};
    int f[s][s];
    int n=6,c=12;
        cout<<endl;
    for(int i=1;i<7;i++)
    {
        cout<<vi[i]<<" ";
    }
    cout<<endl;
    for(int i=1;i<7;i++)
    {
        cout<<wi[i]<<" ";
    }
        cout<<endl<<endl;
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=c;j++)
        {
            if(j<wi[i])
            {
                f[i][j]=f[i-1][j];
            }
            else
            {
                f[i][j]=max(f[i-1][j],f[i-1][j-wi[i]]+vi[i]);
            }
        }
    }

    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=c;j++)
        {
            cout<<f[i][j]<<' ';
        }
        cout<<endl;
    }


return 0;
}
*/


#include "iostream"
#include "fstream"
using namespace std;

/*
b[k]表示长度为i的子序列c[i]中，长度为k的最长单调递增子序列的最小结尾元素值
当c[i]>=b[k], k = k + 1; b[k] = c[i]
否则，将c[i]放置到b[]中适当位置
*/

int f[100];
int a[100];

//二分搜索法在b[1,k]中找到下标h，使得b[h-1]<=c[i]<=b[h]
int fun1(int s, int k)
{
    int i,j;
    if(a[s]<f[1])
    {
        return 1;
    }
    for(i=1,j=k;i!=j-1;)
    {
        k=(i+j)/2;
        if(f[k]<=a[s])
        {
            i=k;
        }
        else
        {
            j=k;
        }
    }
    return j;
}

int fun(int n)
{
    int i,j;
    f[1]=a[1];
    for(i=2,j=1;i<=n;i++)
    {
        if(a[i]>=f[j])
        {
            f[++j]=a[i];
        }
        else
        {
            f[fun1(i,j)]=a[i];
        }
    }
    return j;
}

int main()
{
    int n;
    cout <<endl<< "序列长度：" ;
    cin >> n;
    for(int i=1; i<=n; i++)
        cin>>a[i];
    int count = fun(n);
    cout << "最长单调递增子序列为：" << count << endl;
    return 0;
}
