#include <iostream>
#include "vector"

using namespace std;

class fuck
{
private:
    int nmsl;
public:
    fuck():nmsl(0){}
    int nm(){return nmsl;}
};

int main()
{
    fuck *f=new fuck();
    cout<<f->nm();
    return 0;
}
