//读数
//eg: 1 1个1 -> 11
//   11 2个1 ->21
//   21 1个2和1个1 ->1211
// 1211 1个1和1个2和2个1 ->111221
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
public:
    string countandsay(int n)
    {
        string a={'1'};
        int i=0,k=0;
        while(--n)
        {
            string b;
            k=1;
            for(i=1;i<a.size();i++)
            {
                if(a[i]==a[i-1])
                {
                    k++;
                }
                else
                {
                    b+=k+48;
                    b+=a[i-1];
                    k=1;
                }
            }
            b+=k+48;
            b+=a[i-1];
            a=b;
        }
        return a;
    }

};
int main()
{
    int n;
    cin>>n;
    Solution a;
    cout<<a.countandsay(n)<<endl;

}
