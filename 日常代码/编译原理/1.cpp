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
    FILE *myfile;

    if( (myfile=fopen(argv[1],"r"))==NULL)
    {
        cerr<<"文件错误"<<endl;
        exit(1);
    }
    else
    {
        cout<<fgetc(myfile)<<endl;
    }
    fclose(myfile);
    return 0;
}
