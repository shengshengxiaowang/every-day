//海豚算法，循环右移k，时间复杂的O(n),空间复杂度O(1)
#include<iostream>
using namespace std;
int main()
{
    int s;
    cout<<"请输入数组大小"<<endl;
    cin >> s;
    char* a=new char[s];
    int i,j,k,h,g;
    cout<<"请输入数组"<<endl;
    for(i=0;i<s;i++)
    {
        cin>>a[i];
    }
    cout<<"请输入k大小"<<endl;
    cin >>k;
    i=0;j=0;
    g=1;
    while(g<s)
    {
        j=(j+s-k)%s;
        if(i!=j)
        {
            h=a[i];
            a[i]=a[j];
            a[j]=h;        //交换A[i]与A[j]的位置,一次到位 ,由于画出过程来像海豚在跳跃，因此得名o(╯□╰)o
        }
        else
        {
            i++;
            j++;
        }
        g++;
    }
    cout<<a<<endl;
}
