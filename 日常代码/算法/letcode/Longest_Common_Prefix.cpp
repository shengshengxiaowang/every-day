//找字符串的共同前缀子串

#include<iostream>
#include<vector>
using namespace std;
class solution
{
public:
    string longg(vector<string>& strs)
    {
        string s;
        if(strs.size()==0)
        {
            s='\0';
            return s;
        }
        int i,j=0;
        s.assign(strs[0]);
        for(i=1;i<strs.size();i++)
        {
            j=0;
            while(strs[i][j]==s[j] && j<strs[i].size() && j<s.size() )
            {
                //cout<<s[j]<<endl;
                j++;

            }
            s=s.substr(0,j);

        }

        return s;
    }
};

int main()
{
    int n;
    cin>>n;
    vector<string> str(n);
    for(int i=0;i<n;i++)
    {
        cin>>str[i];
    }
    solution a;
    cout<<a.longg(str)<<endl;

}
