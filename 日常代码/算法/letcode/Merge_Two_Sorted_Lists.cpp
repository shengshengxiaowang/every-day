//合并两个有序链表
//用c语言方式建的链表，有问题！
//递归简单
#include<iostream>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode (int x):val(x),next (NULL){}
};
class solution
{
public:
    ListNode * merge(ListNode * l1,ListNode * l2)
    {
        if(l1==nullptr && l2!=nullptr)
     {
         return l2;
     }
     if(l2==nullptr&& l1!=nullptr)
     {
         return l1;
     }
     if(l2==nullptr&& l1==nullptr)
     {
         return l1;
     }

    ListNode * l=l1, *ll=l2,*head = nullptr;
     if( (l1->val)>(l2->val) )
     {
         l=l2;
         ll=l1;
     }
     head=l;
     while(l->next!=NULL && ll!=NULL)
     {

         ListNode *q,*p;
         if( (l->next->val)>=(ll->val)) //如果大，插入小的
         {
             q=ll->next;
             p=l->next;
             l->next=ll;
             l->next->next=p;
             l=l->next;
             ll=q;
         }
         else    //如果不大，继续
         {
             l=l->next;
         }

     }

     if(ll!=NULL)
     {
         l->next=ll;
     }
     return head;
    }
};

class solution2
{
public:
    ListNode * merge(ListNode * l1,ListNode * l2)
    {
        ListNode *m=nullptr;
        if(l1==NULL)
        {
            return l2;
        }
        else if(l2==NULL)
        {
            return l1;
        }
        if(l1->val<l2->val)
        {
            m=l1;
            m->next=merge(l1->next ,l2);
        }
        else
        {
            m=l2;
            m->next=merge(l2->next,l1);
        }
        return m;
    }
};


int main()
{
    ListNode *q;
    ListNode *l1=new ListNode(-1);
    ListNode *l2=new ListNode(-1);
    int n1,n2;
    cin>>n1;
    q=l1;
    while((n1--)!=0)
    {
        cin>>q->val;
        ListNode *p=new ListNode(-1);
        p->next=nullptr;
        q->next=p;
        q=p;
    }
/*    q=l1;
    while(q->next!=NULL)
    {
        cout<<q->val;
        q=q->next;
    }
cout<<endl;*/
    q=l2;
    cin>>n2;
    while((n2--)!=0)
    {
        cin>>q->val;
        ListNode *p=new ListNode(-1);
        p->next=nullptr;
        q->next=p;
        q=p;
    }
    /*q=l2;
    while(q->next!=NULL)
    {
        cout<<q->val;
        q=q->next;
    }
cout <<endl;*/
    solution a;
    ListNode *s=a.merge(l1,l2);
    while(s->next!=NULL)
    {
        cout<<s->val;
        s=s->next;
    }
}
