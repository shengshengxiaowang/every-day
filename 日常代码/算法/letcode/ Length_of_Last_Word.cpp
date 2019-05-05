//求字符串最后一个单词的长度
//不知道为什么Solution2的代码比我的运行速度快很多emmmm
//注意的点就是处理最后的空格，算水题
#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s)
    {
        if(s.empty())
        {
            return 0;
        }
        int k=0;
        for(int i=s.length()-1;i>=0;i--)
        {
            if(s[i]==' ' && k!=0)
            {
                break;
            }
            if(s[i]!=' ')
            {
                k++;
            }

        }
        return k;
    }
};

class Solution2 {
public:
    int lengthOfLastWord(string s) {
       if(s.size()==0)
            return 0;
        int i=s.size()-1;
        int res=0;
        while(i>=0)
        {
            if(s[i]==' ')
                i--;
            else
                break;
        }
        while(i>=0)
        {
            if(s[i]!=' ')
                res++;
            else
                break;
            i--;
        }
        return res;
    }
};

int main()
{
    string s;
    getline(cin,s);
    Solution a;
    cout<<a.lengthOfLastWord(s)<<endl;

}
