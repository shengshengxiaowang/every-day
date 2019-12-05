//会场安排问题 贪心算法
#include<iostream>
#include<algorithm>
using namespace std;

struct aa
{
  int start,end,flag;
};

int cmp(aa first,aa second)
{
    return first.end<second.end;
}
int main()
{

    int n;
    cin>>n;
    struct aa a[n];
    int i,j,count=n,m=0,k;
    for(i=0;i<n;i++)
    {
        cin>>a[i].start;
        cin>>a[i].end;
        a[i].flag=0;
    }
    sort(a,a+n,cmp);

    /*for(i=0;i<n;i++)
    {
      cout<<a[i].start<<' '<<a[i].end<<endl;
    }*/
    k=-1;
    while(count>0)
    {
        for(i=0;i<n;i++)
        {
            if(a[i].flag==0 && a[i].start>k)//如果没有被安排并且满足条件，count数减1
            {
                count--;
                a[i].flag=1;
                k=a[i].end;
            }
        }
        k=-1;
        m++;
    }
    cout<<m<<endl;
}
