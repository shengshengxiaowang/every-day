//有序数组中去除重复值，返回新长度
//看了题解，说是两个指针就可以，觉得很有道理
//最开始想的是把后面跟前面交换，最后发现不用管后面的，直接赋值即可
//我基本每次做题都会把如果初始为空这个条件忘了
//觉得题简单也好，难也好，简单的话寻求速度更快的解决办法其实更有成就感，就这样从简单开始慢慢做吧，追求每道速度、内存都超过90%以上就可以了
#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int remove(vector<int>& nums)
    {
        int i=0,j;
       if(nums.empty())
       {
           return 0;
       }
       for(j=1;j<nums.size();j++)
       {
           if(nums[i]!=nums[j])
           {
               i++;
               nums[i]=nums[j];
           }
       }

       return i+1;
    }
};

int main()
{
    int n;
    cin>>n;
    vector<int> num(n);
    for(int i=0;i<n;i++)
    {
        cin>>num[i];
    }
    for(int i=0;i<n;i++)
    {
        cout<<num[i];
    }
    cout<<endl;
    Solution a;
    n=a.remove(num);
    for(int i=0;i<n;i++)
    {
        cout<<num[i];
    }

}
