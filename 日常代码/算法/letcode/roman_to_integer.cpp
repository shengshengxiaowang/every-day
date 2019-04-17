//罗马数字转换为整数
//还有个办法提交有问题不知道为啥emmmmm
#include<iostream>
using namespace std;
class Solution
{
public:
    int romantoint(string s)
    {
        int sum=0;
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='M')
            {
                sum+=1000;
            }
            else if(s[i]=='D')
            {
                sum+=500;
            }
            else if(s[i]=='C' && s[i+1]!='M'&& s[i+1]!='D')
            {
                sum+=100;
            }
            else if(s[i]=='C' )
            {
                sum-=100;
            }
            else if(s[i]=='L')
            {
                sum+=50;
            }
            else if(s[i]=='X' && s[i+1]!='L'&&s[i+1]!='C'&&s[i+1]!='D'&&s[i+1]!='M')
            {
                sum+=10;
            }
            else if(s[i]=='X' )
            {
                sum-=10;
            }
            else if(s[i]=='V')
            {
                sum+=5;
            }
            else if(s[i]=='I' && s[i+1]!='V'&& s[i+1]!='X'&& s[i+1]!='L'&&s[i+1]!='C'&&s[i+1]!='D'&&s[i+1]!='M')
            {
                sum++;
            }
            else if(s[i]=='I')
            {
                sum--;
            }
        }
        return sum;
        /*int sum=0;
        int *a=new int(s.length());
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='I')
            {
                a[i]=1;
            }
            else if(s[i]=='V')
            {
                a[i]=5;
            }
            else if(s[i]=='X')
            {
                a[i]=10;
            }else if(s[i]=='L')
            {
                a[i]=50;
            }else if(s[i]=='C')
            {
                a[i]=100;
            }else if(s[i]=='D')
            {
                a[i]=500;
            }else if(s[i]=='M')
            {
                a[i]=1000;
            }
        }
        for(int i=0;i<s.length();i++)
        {
            if(a[i]>=a[i+1])
            {
                sum+=a[i];
            }
            else
            {
                sum-=a[i];
            }
        }
        return sum;*/
    }
};

int main()
{
    Solution a;
    string s;
    cin>>s;
    cout<<a.romantoint(s)<<endl;
}
