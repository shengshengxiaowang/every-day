//不转换成字符串判断回文数字
//开始以为是个水题，结果，做了很久．．．
//这道题看着简单，实际上坑不少，比如双数位和单数位的处理，比如最后一位是0时候的处理，嗯．．．脑子是个好东西，希望我能多一点。
#include<iostream>
using namespace std;
class Solution
{
public:
     bool isPalindrome(int x)
     {
         if(x>=0&&x<10)
         {
             return 1;
         }
         else if(x<0 || (x!=0&&x%10==0))
         {
             return 0;
         }
         int a=0;
         while(a<x)
         {
             a=a*10+x%10;
             x=x/10;
         }
         if(a==x || a/10==x)
         {
             return 1;
         }


         return 0;
     }
};

int main()
{
    Solution a;
    int x;
    cin>>x;
    cout<<a.isPalindrome(x)<<endl;
}
