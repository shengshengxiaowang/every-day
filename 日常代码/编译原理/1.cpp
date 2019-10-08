#include<iostream>
#include<fstream>
using namespace std;


int main(int argc,char *argv[])
{
    if(argc<2)     //判断输入文件
    {
        cout<<"没有检测到文件"<<endl;
        exit(1);
    }
    else
    {
        cout<<argv[1]<<endl;
    }
    ifstream file(argv[1],ios::in);
    if(!file)
    {
        cerr<<"文件错误"<<endl;
        exit(1);
    }
    else
    {
        char c=file.get();
        cout<<c<<endl;
        c=file.get();
        cout<<c<<endl;
        //cout<<file.get()<<endl;
    }
    
    file.close();
}
