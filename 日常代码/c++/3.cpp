#include<iostream>
#include<math.h>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int a[n];
    int x1[n+1],x2[n+1];
    int count1=0,count2=0,flag=0;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    for(int i=0 ;i<n;i++)
    {
        flag=0;
        for(int j=2; j<= sqrt(a[i]); j++) 
        {
            if((a[i]%j)==0) // 如果能被除了1和它本身的数整除，就不是素数
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            x1[count1++]=a[i];
        }
        if(a[i]%2==0)
        {
            x2[count2++]=a[i];
        }
    }
    int i,j;
    for(i=0;i<count1-1;i++)
    {
        cout<<x1[i]<<" ";
    }

    cout<<x1[i]<<endl;
    for(j=0;j<count2-1;j++)
    {
        cout<<x2[j]<<" ";
    }
    cout<<x2[j]<<endl;
}
