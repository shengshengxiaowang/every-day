//编译原理实验之--词法分析器
#include<iostream>
#include<fstream>
#include<map>
using namespace std;

map<string,int> mapkey;
map<string,int> mapdigit;
map<string,int> mapletter;
int ldig=0,llet=0;

void key_map(); //关键字建表
bool digit(char ch);  //判断是数字
bool letter(char ch);  //判断是字母
bool research_key(char * token);  //查找关键字
int research_digit(char *token); //查找数字
int research_letter(char *token); //查找标识符
void type_key();    //打印关键字表
void type_digit();  //打印数字表
void type_letter(); //打印字母表

void fun(FILE *myfile)//遍历
{
    char ch;  //字符
    int len=0;  //文件当前长度

    fseek(myfile, 0L,SEEK_END);  //计算文件长度
    int x=ftell(myfile);
    fseek(myfile, 0L,SEEK_SET);
     
    while( len< x) //读取整个文件，当当前已读取数大于文件长度时，结束读取
    {
        ch=fgetc(myfile);
        len++;
        if(ch==' '||ch=='\t'||ch=='\n')
        {
            //如果是空格，换行或tab，跳过，不作处理
        }

        else if(letter(ch))  //第一个为字母
        {
            char token[20]={'\0'};
            int i=0;
            while(letter(ch)||digit(ch))  //字母或数字
            {
                token[i++]=ch;
                ch=fgetc(myfile);
                len++;
            }
            fseek(myfile,-1L,SEEK_CUR);  //回退指针，因为while循环里是有读取的，所以回退
            len--;
            //cout<<token<<endl;
            if(research_key(token))
            {
                cout<<"( "<<token<<" 关键字  "<<")"<<endl;
            }
            else
            {
                int nux=research_letter(token);
                cout<<"( "<<token<<" 标识符 "<<nux<<" )"<<endl;
            }
        }
        else if( ch=='-' &&  !digit(fgetc(myfile) ))
        {
            fseek(myfile,-1L,SEEK_CUR);
            ch=fgetc(myfile);
                len++;
                if(ch=='-')
                {
                    cout<<"( "<<"--"<<" 运算符 "<<"  )"<<endl;
                }
                else
                {
                    cout<<"( "<<"-"<<" 运算符 "<<"  )"<<endl;
                    fseek(myfile,-1L,SEEK_CUR);
                    len--;
                }
        }
        else if( digit(ch)|| ch=='.' || (ch=='-' && digit(fgetc(myfile) ) ) ) //如果是数字或者小数点或负数
        {
            //无符号常数,有符号常数待解决
            /*if(ch=='.'&& digit(fgetc(myfile)) )
            {
                fseek(myfile,-1L,SEEK_CUR);  //回退指针，因为while循环里是有读取的，所以回退
            }*/
            char token[20]={'\0'};
            int i=0;
            if(ch=='-') //是负数
            {
                fseek(myfile,-2L,SEEK_CUR);  //回退指针，因为while循环里是有读取的，所以回退
                token[i++]='-';
                ch=fgetc(myfile);
            }
            while(digit(ch)||ch=='.')
            {
                token[i++]=ch;
                ch=fgetc(myfile);
                len++;
            }
            fseek(myfile,-1L,SEEK_CUR);  //回退指针，因为while循环里是有读取的，所以回退
            len--;
            int num=research_digit(token); //查找数字表序号
            cout<<"( "<<token<<" 数字 "<<num<<" )"<<endl;
        }
        else if(ch=='#')
        {
            char token[20]={'\0'};
            int i=1;
            ch=fgetc(myfile);
            len++;
            if(ch=='i')
            {
                token[0]='#';
                while(letter(ch)||ch=='.'||ch=='<' || ch=='>')  //字母或.<>
                {
                    token[i++]=ch;
                    ch=fgetc(myfile);
                    len++;
                }
                fseek(myfile,-1L,SEEK_CUR);  //回退指针，因为while循环里是有读取的，所以回退
                len--;
                cout<<"( "<<token<<" 头文件 "<<" )"<<endl;
            }
            if(ch=='d')
            {
                token[0]='#';
                while(letter(ch))  //字母
                {
                    token[i++]=ch;
                    ch=fgetc(myfile);
                    len++;
                }
                fseek(myfile,-1L,SEEK_CUR);  //回退指针，因为while循环里是有读取的，所以回退
                len--;
                cout<<"( "<<token<<" 宏定义 "<<" )"<<endl;
            }
        }

        else switch(ch)
        {
            case '+':
            {
                ch=fgetc(myfile);
                len++;
                if(ch=='+')
                {
                    cout<<"("<<"++"<<" 运算符 "<<"  )"<<endl;
                }
                else
                {
                    cout<<'('<<"+"<<" 运算符 "<<"  )"<<endl;
                    fseek(myfile,-1L,SEEK_CUR);
                    len--;
                }
            }break;
            /*case '-':
            {
                ch=fgetc(myfile);
                len++;
                if(ch=='-')
                {
                    cout<<"( "<<"--"<<" 运算符 "<<"  )"<<endl;
                }
                else
                {
                    cout<<"( "<<"-"<<" 运算符 "<<"  )"<<endl;
                    fseek(myfile,-1L,SEEK_CUR);
                    len--;
                }
            }break;*/
            case '*':cout<<"( "<<"*"<<" 运算符 "<<"  )"<<endl;break;
            case '/':
            {
                ch=fgetc(myfile);
                len++;
                if(ch=='/')
                {
                    cout<<"( "<<"//"<<" 注释内容 "<<"  )"<<endl;
                }
                else
                {
                    cout<<"( "<<"/"<<" 运算符 "<<"  )"<<endl;
                    fseek(myfile,-1L,SEEK_CUR);
                    len--;
                }
            }break;
            case '(':cout<<"( "<<"("<<" 分界符 "<<"  )"<<endl;break;
            case ')':cout<<"( "<<")"<<" 分界符 "<<"  )"<<endl;break;
            case '[':cout<<"( "<<"["<<" 分界符 "<<"  )"<<endl;break;
            case ']':cout<<"( "<<"]"<<" 分界符 "<<"  )"<<endl;break;
            case ';':cout<<"( "<<";"<<" 分界符 "<<"  )"<<endl;break;
            case '{':cout<<"( "<<"{"<<" 分界符 "<<"  )"<<endl;break;
            case '}':cout<<"( "<<"}"<<" 分界符 "<<"  )"<<endl;break;

            case '=':
            {
                ch=fgetc(myfile);
                len++;
                if(ch=='=')
                {
                    cout<<"( "<<"=="<<" 运算符 "<<"  )"<<endl;
                }
                else
                {
                    cout<<"( "<<"="<<" 运算符 "<<"  )"<<endl;
                    fseek(myfile,-1L,SEEK_CUR);
                    len--;
                }
            }break;
            case '!':
            {
                ch=fgetc(myfile);
                len++;
                if(ch=='=')
                {
                    cout<<"( "<<"!="<<" 运算符 "<<"  )"<<endl;
                }
                else
                {
                    cout<<"( "<<"!"<<" 运算符 "<<"  )"<<endl;
                    fseek(myfile,-1L,SEEK_CUR);
                    len--;
                }
            }break;
            case '>':
            {
                ch=fgetc(myfile);
                len++;
                if(ch=='=')
                {
                    cout<<"( "<<">="<<" 运算符 "<<"  )"<<endl;
                }
                else
                {
                    cout<<"( "<<">"<<" 运算符 "<<"  )"<<endl;
                    fseek(myfile,-1L,SEEK_CUR);
                    len--;
                }
            }break;
            case '<':
            {
                ch=fgetc(myfile);
                len++;
                if(ch=='=')
                {
                    cout<<"( "<<"<="<<" 运算符 "<<"  )"<<endl;
                }
                else
                {
                    cout<<"( "<<"<"<<" 运算符 "<<"  )"<<endl;
                    fseek(myfile,-1L,SEEK_CUR);
                    len--;
                }
            }break;
            default:cout<<"( "<<" 错误 "<<"  )"<<endl;
        }

    }

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
    key_map();//关键字建表
    //cout<<mapkey.size()<<endl;  //mapkey大小
    fun(myfile);//开始构造
    type_key();    //打印关键字表
    type_digit();  //打印数字表
    type_letter(); //打印字母表
    fclose(myfile);
    mapkey.erase(mapkey.begin(), mapkey.end());  //删除
    mapdigit.erase(mapdigit.begin(), mapdigit.end());
    mapletter.erase(mapletter.begin(), mapletter.end());
    return 0;
}

int research_letter(char *token) //查找标识符
{
    auto iter=mapletter.find(token);
    if(iter!=mapletter.end())
    {
        return iter->second;
    }
    else
    {
        mapletter.insert(pair<string,int>(token,++llet));
        return llet;
    }
    
}

int research_digit(char *token) //查找数字
{
    auto iter=mapdigit.find(token);
    if(iter!=mapdigit.end()) //查找到了，返回序号
    {
        return iter->second; 
    }
    else                   //没有查找到，加入并且返回序号
    {
        mapdigit.insert(pair<string,int>(token,++ldig));
        return ldig;
    }
}

bool research_key(char* token)  //查找关键字
{
    if( mapkey.find(token) !=mapkey.end())
        return true;
    else
        return false;
}

void key_map()  //关键字建表
{
    mapkey.insert(pair<string,int>("auto",1));     mapkey.insert(pair<string,int>("break",2));
    mapkey.insert(pair<string,int>("case",3));     mapkey.insert(pair<string,int>("char",4));
    mapkey.insert(pair<string,int>("const",5));    mapkey.insert(pair<string,int>("continue",6));
    mapkey.insert(pair<string,int>("default",7));  mapkey.insert(pair<string,int>("do",8));
    mapkey.insert(pair<string,int>("double",9));   mapkey.insert(pair<string,int>("else",10));
    mapkey.insert(pair<string,int>("enum",11));     mapkey.insert(pair<string,int>("extern",12));
    mapkey.insert(pair<string,int>("float",13));    mapkey.insert(pair<string,int>("for",14));
    mapkey.insert(pair<string,int>("goto",15));     mapkey.insert(pair<string,int>("if",16));
    mapkey.insert(pair<string,int>("int",17));      mapkey.insert(pair<string,int>("long",18));
    mapkey.insert(pair<string,int>("register",19)); mapkey.insert(pair<string,int>("return",20));
    mapkey.insert(pair<string,int>("short",21));    mapkey.insert(pair<string,int>("signed",22));
    mapkey.insert(pair<string,int>("sizeof",23));   mapkey.insert(pair<string,int>("static",24));
    mapkey.insert(pair<string,int>("struct",25));   mapkey.insert(pair<string,int>("switch",26));
    mapkey.insert(pair<string,int>("typedef",27));  mapkey.insert(pair<string,int>("union",28));
    mapkey.insert(pair<string,int>("unsigned",29)); mapkey.insert(pair<string,int>("void",30));
    mapkey.insert(pair<string,int>("volatile",31)); mapkey.insert(pair<string,int>("while",32));
    return;
}

bool digit(char ch)  //判断是数字
{
    if(ch>='0'&& ch<='9')
    {
        return true;
    }
    return false;
}

bool letter(char ch)  //判断是字母
{
    if( (ch>='a' && ch<='z') || (ch>='A'&& ch<='Z') )
    {
        return true;
    }
    return false;
}


void type_key()    //打印关键字表
{
    cout<<"打印关键字表："<<endl;
    for( map<string,int>::iterator iter = mapkey.begin(); iter != mapkey.end() ; iter++)
    {
        cout << iter->first <<" "<<iter->second << endl;
    }
}
void type_digit()  //打印数字表
{
    cout<<"打印数字表："<<endl;
    for( map<string,int>::iterator iter = mapdigit.begin(); iter != mapdigit.end() ; iter++)
    {
        cout << iter->first << " "<<iter->second << endl;
    }
}
void type_letter() //打印字母表
{
    cout<<"打印字母表："<<endl;
    for( map<string,int>::iterator iter = mapletter.begin(); iter != mapletter.end() ; iter++)
    {
        cout << iter->first << "  "<<iter->second << endl;
    }
}

//只实现了简单的功能，出错报行啊之类的还没有
