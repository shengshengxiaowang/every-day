//开平方根。。。
#include<iostream>
using namespace std;


class Solution {
public:
    int mySqrt(int x)
    {
        long i=0;//不可以用int,不够算
        while( (i*i)<x )
        {
            i++;
        }
        return i-1;

    }
};

int main()
{
    int n;
    cin>>n;
    Solution a;
    cout<<a.mySqrt(n)<<endl;
}
