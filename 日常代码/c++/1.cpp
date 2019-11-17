#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int n;//人数
    double x,sum,flag; //价钱,总和
    cin>>n>>x;
    if(n<50)
    {
        sum=n*x;
    }
    else if(n>=50&&n<100)
    {
        sum=n*x*0.9;
    }
    else
    {
        sum=n*x*0.85;
    }
    
    if(sum>(int)sum)
    {
        cout << setprecision(2) << setiosflags(ios::fixed);//设置小数点后两位
        cout<<sum<<endl;
    }
    else
    {
        cout<<sum<<endl;
    }
    
    
    
}