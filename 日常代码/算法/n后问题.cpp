//n后问题，排列数法
//任意两个皇后都不能处于同一行、同一列和同一斜线上
//由于n个数不在同一行也不在同一列，共n个皇后，所以每行都会有一个皇后
//并且这个皇后所在代表列的数是唯一不重复的，这就相当于给n个数全排列，然后判断排列的数在每列上有没有重复即可.
//套用全排列回溯递归即可
#include<iostream>
#include<math.h>
using namespace std;
int n,count=0;


void swap(int *a,int *b)//交换,用指针
{
    int x=*a;
    *a=*b;
    *b=x;
}

int panduan(int *a,int k)
{
    for(int i=1;i<k;i++)
    {
        if( abs(a[i]-a[k])==abs(i-k) )//判断斜率
        {
            return 0;
        }
    }
    return 1;
}

void fun(int *a,int k)//k是行
{
    if(k>n)
    {
        //cout<<a<<endl;
        count++;
        return;
    }
    else
    {
        for(int i=k;i<=n;i++)
        {
            swap(&a[k],&a[i]);//交换，传值地址进去

            if(k==1 || panduan(a,k))
            {
                fun(a,k+1); //这块儿要注意不能用k++,因为下面还要继续用k
            }
            swap(&a[k],&a[i]);

            /*for(int i=1;i<=n;i++)
            {
                cout<<a[i];
            }
            cout<<endl<<k<<endl;*/
        }
    }

}


int main()
{
    cin>>n;
    int i;
    int a[n+1];
    for(i=1;i<=n;i++)//初始化
    {
        a[i]=i;
    }
    fun(a,1);
    cout<<count<<endl;
}
