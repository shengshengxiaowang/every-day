#include"myString.h"

#include <iostream>
using namespace std;

int main()
{
    myString s1("world");
    myString s2("hello");

    myString s3(s1);
    cout << s3 << endl;
    s3=s2;
    cout << s3<<endl;
    s3=s3+s2;
    cout<<s3<<endl;
    swap(s1,s2);
    cout<<s1<<s2<<endl;
    s1=s1+"lala";
    cout<<s1<<endl;
    cout<<s1.length()<<endl;
    s1="haha"; //s2="haha";
    cout<<s1<< s2<<endl;
    cout<< (s1==s2) <<endl;
    cout<< (s1!=s2) <<endl;
    cout<<s1[1]<<endl;
    cout<< s1.substr(1,3)<<endl;
    //cout << compare(s1,s2) <<endl;
    //cout<< (s1=="haha") <<endl;
    //cout<<(s1<s2)<<endl;
    //cout<<(s1<"aa")<<endl;
}
