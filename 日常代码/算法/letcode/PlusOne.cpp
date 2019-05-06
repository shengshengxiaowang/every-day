//给表示非空非负整数的数组加上整数的1
//注意的点就是如果末位是9，需要考虑进位
//这个代码运行速度很快，但是内存只超过了6%的c++，没设啥内存啊
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits)
    {
        auto it=digits.end()-1;
        int k=1;
        while(it!=digits.begin())
        {
            if(*it==9)
            {
                *it=0;
                it--;
            }
            else if(k==1)
            {
                *it+=1;
                k=0;
                break;
            }

        }
        if(k==1)
        {
            if(*it==9)
            {
                *it=0;//也可以把第一个设为1，后面补加一个0
                digits.insert(it,1);
            }
            else
            {
                *it+=1;
            }
        }
        return digits;
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
    nums=a.plusOne(nums);
    for(auto it=nums.begin();it!=nums.end();it++)
    {
        cout<<*it<<' ';
    }
    cout<<endl;




}
