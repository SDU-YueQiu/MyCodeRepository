#include <iostream>
#include <cstdlib>

using namespace std;
const int MAXN = 100;

class touzi
{
private:
    int mianshu;
    int num;
    int nums[MAXN];

public:
    touzi(int mianshu, int num);
    int roll();
};

touzi::touzi(int mianshu = 6, int num = 0)
{
    this->mianshu = mianshu;
    this->num = num;
}

int touzi::roll()
{
    num = rand() % mianshu + 1;
    return num;
}

//上面是你作为后端提供给我的类，下面是我写的程序
//我调用你写的类的函数（接口）来实现我的程序的功能

void init()
{
    int seed;
    cin >> seed;
    srand(seed);
}

int main()
{
    init();
    int mian;
    cin>>mian;
    touzi t(mian);
    cout<<t.roll()<<endl;
    //dosomething
    return 0;
}
