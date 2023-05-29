#include <iostream>
#include "vector"

using namespace std;

int main()
{
    vector<int> s;
    for(int i=1;i<=1e10;++i)
    {
        s.push_back(i);
        cout<<s.capacity()<<endl;
    }
    return 0;
}
