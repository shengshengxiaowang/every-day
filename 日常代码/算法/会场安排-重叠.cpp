//会场安排问题：最大重叠数算法
#include<iostream>
#include<algorithm>
using namespace std;

struct bb
{
    int time,flag;//flag为0即是开始时间，为1即是结束时间
};
int cmp(const bb &first, const bb &second) { //根据需要定制排序
	return first.time < second.time; //根据a从大到小排列

}

int main()
{

    int n;
    cout<<endl;
    cin>>n;
    struct bb b[2*n];
    int i,m=0,max;
    for(i=0;i<2*n;)
    {
        cin>>b[i].time;//输入开始时间
        b[i++].flag=0;
        cin>>b[i].time;//输入结束时间
        b[i++].flag=1;
    }
    sort(b,b+2*n,cmp);//排序
    cout<<endl<<"排序结果";
    for(i=0;i<2*n;i++)
    {
      cout<<b[i].time<<" ";
    }
    cout<<endl;
    max=0;
    for(i=0;i<2*n;i++)
    {
        if(b[i].flag==0)
       {
           m++;
           if(m>max)
           {
               max=m;
           }
       }
       else
       {
          m--;
       }

    }
    cout<<endl<<max<<endl<<endl;;
}
