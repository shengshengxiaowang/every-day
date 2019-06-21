//会场安排问题
#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int start[n],end[n],flag[n];
    int i,count=n,m=1,k;
    for(i=0;i<n;i++)
    {
        cin>>start[i];
        cin>>end[i];
        flag[i]=0;
    }
    flag[0]=1;
    k=end[0];
    sort(start,start+n);
    sort(end,end+n);
    while(count>0)
    {
        for(i=1;i<n;i++)
        {
            if(flag[i]==0 &&start[i]>k)//如果没有被安排并且满足条件，count数减1
            {
                count--;
                k=start[i];
            }
        }
        k=0;
        m++;
    }
    cout<<m<<endl;
}
