#include"myString.h"

#include <iostream>
using namespace std;

int main()
{
    myString s1("");
    myString s2("hello");

    myString s3(s1);
    cout << s3 << endl;
    s3=s2;
    cout << s3<<endl;
}
