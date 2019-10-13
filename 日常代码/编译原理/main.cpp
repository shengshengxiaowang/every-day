#include<iostream>
#include<fstream>
using namespace std;

bool digit(char ch)  //数字
{
    if(ch>='0'&& ch<='9')
    {
        return true;
    }
    return false;
}

bool alphabet(char ch)  //字母
{
    if( (ch>='a' && ch<='z') || (ch>='A'&& ch<='Z') )
    {
        return true;
    }
    return false;
}

void fun(FILE *myfile)
{
    

}

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
    fun(myfile);

    fclose(myfile);
    return 0;
}
