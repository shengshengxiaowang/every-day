
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
