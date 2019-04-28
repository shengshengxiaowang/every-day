//找出子串，返回首位置
//水题，重点在如果发现不是子串，应该返回首位置的下一个，而不是直接继续走
//但是运算速度和内存没有100%，不知道为啥，看了一下评论区代码，有直接用函数的，但是速度内存相差不大

#include<iostream>
using namespace std;
class solution
{
public:
    int strstr(string haystack,string needle)
    {
        if(needle.size()==0)
      {
          return 0;
      }
      int j=0,k=0,f=0;
      for(int i=0;i<haystack.size();i++)
      {
          if(haystack[i]==needle[j])
          {
              if(j==0)
              {
                  k=i;
              }
              if(j==needle.size()-1)
              {
                  f=1;
                  break;
              }

              j++;
          }

          else
          {
              i=i-j;//重点
              j=0;
          }
      }

      if(f==1)
      {
          return k;
      }
      return -1;
    }
};
int main()
{
    int n1,n2;
    string a,b;
    cin>>n1>>a;
    cin>>n2>>b;
    solution s;
    cout<<s.strstr(a,b)<<endl;
}
