#include<iostream>
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
