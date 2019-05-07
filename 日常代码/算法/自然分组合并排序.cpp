
#include<iostream>
#include<vector>
using namespace std;
class solution
{
private:
    int *b;int n,k=1;
public:
    int* ziran(int *a,int s)
    {
        b=a;n=s;
        int temp[n];
        temp[0]=0;
        int i,j=1;

        for(i=0;i<n;i++) //分段
        {
            if(a[i]>a[i+1])
            {
                temp[j++]=i+1;
                k++;//k是总共有多少段
            }
        }

        temp[j]=n;
        for(i=0;i<k;i++)//输出子段
        {
            cout<<temp[i];
        }
        cout<<endl;

        int f=k;
        while(k>1)
        {

            for(j=0,i=0;j<k/2;j++,i+=2) //两个相邻的进行合并
            {
                //cout<<i<<j<<endl;
            //cout<<"k:"<<k<<"temp:"<<i<<temp[i]<<temp[i+1]<<temp[i+2]<<endl;

                hebing(temp[i],temp[i+1],temp[i+2]);

                f--;
            }
            //cout<<"*"<<endl;
            newtemp(temp,k);
            k=f;

        }

        return a;
    }
    void newtemp(int *temp,int f)
    {
        int i,j=0;
        for(i=0;i<=f;i+=2)
        {
            temp[j++]=temp[i];
        }
        if(temp[j-1]!=n)
        {
            temp[j]=n;
        }
        /*for(i=0;i<=f;i++)
        {
            cout<<"f:"<<temp[i]<<endl;
        }*/


    }
    void hebing(int begin,int mid ,int end )
    {
        int i=0,j;
        int x[end-begin];
        int l1=begin,l2=mid;
        while(l1!=mid && l2!=end)//合并入新数组x
        {
            if(b[l1]<b[l2])
            {
                x[i++]=b[l1++];
            }
            else
            {
                x[i++]=b[l2++];
            }
        }
        if(l1==mid) //如果l1排完了，该l2
        {
            while(l2!=end)
            {
                x[i++]=b[l2++];
            }
        }
        if(l2==end) //如果l2排完了，该l1
        {
            while(l1!=mid)
            {
                x[i++]=b[l1++];
            }
        }

        for(i=0,j=begin;i<end-begin;i++)
        {
            b[j++]=x[i];
        }

        /*cout<<"排序：" <<endl;//输出排好序的部分
        for(i=0;i<end;i++)
        {
            cout<<b[i];
        }
        cout<<endl<<endl;*/


    }


};

int main()
{
    int n,i;
    cout<<endl;
    cout<<"数组个数：";
    cin>>n;
    int a[n];
    cout<<endl;
    for(i=0;i<n;i++)
    {
        cin>>a[i];
    }

    /*for(i=0;i<n;i++)
    {
        cout<<a[i]<<" ";
    }*/
    cout<<endl;
    int *b;
    solution k;
    b=k.ziran(a,n);
    for(i=0;i<n;i++)
    {
        cout<<b[i];
    }
}
