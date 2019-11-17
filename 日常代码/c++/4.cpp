#include<iostream>
#include<algorithm>
using namespace std;
struct sss
{
    string name;
    int fen[10]={0};
    int sum=0;
};
bool compare(int a,int b)
{
    return a>b;
}

int main()
{
    int n,k;
    cin>>n>>k;
    sss ss[n];
    for(int i=0;i<n;i++)
    {
        cin>>ss[i].name;
        for(int j=0;j<k;j++)
        {
            cin>>ss[i].fen[j];
        }
    }
    
    for(int i=0;i<n;i++)
    {
        sort(ss[i].fen,ss[i].fen+k,compare);
        ss[i].fen[0]=0;
        ss[i].fen[k-1]=0;
        for(int j=0;j<k;j++)
        {
            ss[i].sum=ss[i].sum+ss[i].fen[j];
        }
    }
    for(int i=0;i<n;i++)
    {
        sort(ss[i].sum,ss[i].sum+n,compare);
    }
    cout<<ss[0].name<<" "<<ss[0].sum<<endl;
}
