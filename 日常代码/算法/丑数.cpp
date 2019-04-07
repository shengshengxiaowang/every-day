//丑数问题:我们把只包含质因子2,3,5的称为丑数，1是特殊的丑数，输出第k个丑数
#include<iostream>
using namespace std;
int min(int a,int b,int c)
{
    if( (b>=c && c>=a) || (c>=b && b>=a))
    {
        return a;
    }
    else if((a>=c && c>=b) || (c>=a && a>=b))
    {
        return b;
    }
    else
    {
        return c;
    }
}
int main()
{
    int *a,*b,*c;
    int k,count=1,a1,b1,c1;
    cin >> k;
    int* s=new int[k];
    s[0]=1;
    a=&s[0];b=&s[0];c=&s[0];
    while(count<k)
    {
        a1=(*a)*2;
        b1=(*b)*3;
        c1=(*c)*5;
        s[count]=min(a1,b1,c1);
        //cout<<s[count]<< a1<< b1 << c1 <<endl;
        if(s[count]==a1)
        {
            a++;
        }
        else if(s[count]==b1)
        {
            b++;
        }
        else
        {
            c++;
        }
        count++;
    }
    cout<<s[count-1]<<endl;
}
