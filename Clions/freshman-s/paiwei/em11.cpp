
#include <iostream>
using namespace std;

class Base
{
public:
    ~Base();
};
Base::~Base()
{
    cout << "Base destructor" << endl;
}

class Derived : public Base
{
public:
    Derived();
    ~Derived();

private:
    int *p;
};

Derived::Derived()
{
    p = new int(0);
}

Derived::~Derived()
{
    cout << "Derived destructor" << endl;
    delete p;
}

void fun(Base *b)
{
    delete b;//只执行基类析构
}

int main()
{
    Base *b = new Derived();
    fun(b);
    Derived *d=new Derived();
    //fun(d);
    delete d;
    return 0;
}
