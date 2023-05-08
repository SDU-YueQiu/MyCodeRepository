#include <iostream>
#include "link.h"
using namespace std;

int main()
{
    LinkedList<int> a;
    LinkedList<int> b;
    for(int i=1;i<=5;++i)
        a.insertRear(i);
    for(int i=6;i<=10;++i)
        b.insertRear(i);
    b.reset();
    for(int i=1;i<=5;++i)
    {
        a.insertRear(b.data());
        b.next();
    }
    a.reset();
    for(int i=1;i<=10;++i)
    {
        cout<<a.data()<<" ";
        a.next();
    }
    return 0;
}