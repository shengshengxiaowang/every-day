//题目描述：给定32位有符号整数，输出整数的反向数字
//题目重点在如果反向数字超过32位，也就是不在-2147483648~2147483647之间的话，输出0。
//要注意如果把加和步骤放在if判断语句之前,则会多进行一步，导致程序错误
#include<iostream>
using namespace std;
class Solution
{
public:
    int reverse(int x)
    {
        int num=0;
        while(x!=0)
        {
            int a=x%10;
            x=x/10;
            if( (num>(2147483647/10) ) || (num==(2147483647/10) && x>=7) )
            {
                return 0;
            }
            if( (num<(-2147483648/10) )|| (num==(-2147483648/10)&& x<=-8) )
            {
                return 0;
            }
            num=num*10+a;
        }
        return num;
        //return 0;
    }
};

int main()
{
    Solution a;
    int x;
    cin>>x;
    cout<<a.reverse(x)<<endl;
    /*int b;
    cin>>b;
    cout<<b*10<<endl;*/
}
