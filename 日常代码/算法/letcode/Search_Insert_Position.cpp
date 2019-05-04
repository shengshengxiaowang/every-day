//给定有序数组和指定值，如果数组中找到该值，输出位置，如果没有，输出应该插入位置
//水题
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    int searchinsert(vector<int>& nums,int target)
    {

        int i=0;
        for(i=0;i<nums.size();i++)
        {
            if(nums[i]==target || nums[i]>target)
            {
                return i;
            }
        }
        return i;
    }
};
int main()
{
    int n,s;
    cin>>n;
    vector<int> nums(n);
    for(int i=0;i<n;i++)
    {
        cin>>nums[i];
    }
    cin>>s;
    Solution a;
    cout<<a.searchinsert(nums,s)<<endl;

}
