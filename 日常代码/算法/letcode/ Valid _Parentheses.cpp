//确定输入字符串有效，[](){}这三种，必须成对且顺序是对的
//这道题要用栈，我对栈不是很熟悉，但是按自己理解做出了一下
//超过了100%的c++代码，小开心，也就能在这种简单题上找找开心了emmmm
//有个内存报错找了半天，同样的例子我的编译器就好着呢，letcode就有问题，很迷，待解决.
#include<iostream>
using namespace std;
class solution
{
public:
    bool fun(string s)
    {
        string ss(s.size(),'q');//letcode编译器报错内存部分！注意！
        int top=0,i=0;
        //ss[0]='q';

        while(top>=0&& i<s.size())
        {

            //cout<<ss.size()<<endl;
            if((s[i]==']' && ss[top]=='[')|| (s[i]=='}' && ss[top]=='{') || (s[i]==')' && ss[top]=='(') )
            {
                top--;
                i++;
                continue;
            }
            else
            {
                ss[++top]=s[i++];
            }

        }

        if(top==0)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
};


int main()
{
    string s;
    cin>>s;
    solution a;
    cout<<a.fun(s)<<endl;

}
