#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int n=0,count=0;  
    cin>>n;
    for(int i=0;i<=n;i++)
    {
        int j=i;
        while(j)  
        {  
            if (j& 0x01)   
            {    
            }  
            else  
            {  
                count++;  
            }  
            j >>= 1;  
         }  
    }
    cout<<count<<endl;
}