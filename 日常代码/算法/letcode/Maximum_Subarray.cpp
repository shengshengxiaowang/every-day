//给定一个整数数组，找出最大总和连续子数组，返回最大值
//动态规划（ps:我觉得是）
//给出每一步最大值，比较即可，简单。
//还有分治法emmmm没看
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums)
    {
        int max=nums[0];
        for(auto it=nums.begin()+1;it!=nums.end();)
        {
            if( (*it+*(it-1) ) > *it)
            {
                *it+=*(it-1);
            }
            if(*it>max)
            {
                max=*it;
            }
            it++;
        }
        return max;
    }
};

int main()
{
    int n;
    cin>>n;
    vector<int> nums(n);
    for(int i=0;i<n;i++)
    {
        cin>>nums[i];
    }
    Solution a;
    cout<<a.maxSubArray(nums)<<endl;

}
