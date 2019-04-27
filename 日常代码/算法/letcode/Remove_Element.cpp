//删除数组中指定的val元素，并返回新长度
//论一道简单的水题如何逼疯我．．．
//定两个指针，我是一个从后面开始，一个从前面开始，因为这道题不要求考虑顺序
//but:各种越界内存防不胜防，各种特殊情况防不胜防
//事实证明是我太菜了
//方法２是另一种方法，其实重复赋值多，真正好的还是我这个思路
//但是方法３才是我这个思路的正确打开方式,写的真漂亮!!!
#include<iostream>
#include<vector>
using namespace std;
class Solution1{
public:
    int remove(vector<int>& nums,int val)
    {
        int i=0,j=nums.size()-1;
        if(nums.empty())
        {
          return 0;
        }

        while(i<j)
        {
          if(nums[i]!=val && i<nums.size()-1)
          {
              i++;
          }
          if(nums[j]==val && j>0)
          {
              j--;
          }
          if( (nums[i]==val) && nums[j]!=val && i<j)
          {
              nums[i]=nums[j];
              i++;
              j--;
          }
         //cout<<'*'<<i<<j<<endl;
        }
        if(i==j&&nums[i]!=val)
        {
           i++;
        }
        return i;
    }
};

class Solution2 {
public:
    int remove(vector<int>& nums,int val)
    {
        int i=0,j=0;
        for(j;j<nums.size();j++)
        {
            if(nums[j]!=val)
            {
                nums[i]=nums[j];
                i++;
            }
        }
        return i;
    }
};

class Solution3 {
public:
    int remove(vector<int>& nums,int val)
    {
        int i=0,j=nums.size();
        while(i<j)
        {
            if(nums[i]==val)
            {
                nums[i]=nums[j-1];
                j--;
            }
            else
            {
                i++;
            }
        }
        return j;
    }
};

int main()
{
    int n,val;
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
    cout<<"val:"<<endl;
    cin>>val;
    Solution2 a;
    n=a.remove(num,val);
    for(int i=0;i<n;i++)
    {
        cout<<num[i];
    }

}
