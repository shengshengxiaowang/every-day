//题目描述：给出一组数据和一个数，求出数组中的两个数字加起来等于已知的数，并返回这两个数字在数组中的下标

#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

/*因为进行了排序，所以不能保存原数字下标
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        sort(nums.begin(),nums.end());
        vector<int> bb(2);
    
        auto a=nums.begin(),b=nums.end()-1;
        cout<<*a<<*b<<endl;
        for( ;a<b; )
        {
            cout<<*a<<' '<<*b<<endl;
            if((*a+*b)==target)
            {
                bb[0]=*a;
                bb[1]=*b;
                //cout << '*';
                break;
            }
            else if((*a+*b)>target)
            {
                b--;
            }
            else
            {
                a++;
            }
        }
        for(auto c:bb)
        {
            cout<<c<<' ';
        }
        return bb;
    }
};*/

//用map容器，哈希表做，map中关键字放值，对应值放下标，直接在将vector存入map的时候，根据要总和值减去当前值，在map中寻找对应的
//找到存入新容器中，找不到继续即可

class Solution 
{
public:
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        map<int,size_t> mapp;
        int i=0;
        for(auto c:nums)
        {
            int k=target-c;
            if(mapp.find(k)!=mapp.end())  //根据下标寻找写法
            {
                vector<int> a;
                //vector<int> a{mapp[k],i};  //这里不能这样写，不知道为啥s
                //vector<int> a(2); 
                //a[0]=mapp[k][k];
                // a[1]=i;
                a.push_back(mapp[k]);
                a.push_back(i);
               
                return a;
            } 
            mapp.insert({c,i++});  
        }
        return nums;
    }
};
int main()
{
    vector<int> a;
    int x,b,n;
    cin>>n;
    while(n--)
    {
        cin>>x;
        a.push_back(x);
    }
    cin>>b;
    vector<int> bb(2);
    Solution aa;
    bb=aa.twoSum(a,b);

    for(auto c:bb)
    {
       cout<<c<<' ';
    }
    cout<<endl;
    //cout<<endl<<b<<endl;
}
