#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

enum XB
{
    man = 1,
    woman
};

class date
{
private:
    int year;
    int month;
    int day;

public:
    date(int y = 0, int m = 0, int d = 0)
    {
        year = y;
        month = m;
        day = d;
    }
    void getdate(int &y, int &m, int &d) const
    {
        y = year;
        m = month;
        d = day;
    }
    void showdate()
    {
        cout << year << "-" << month << "-" << day << endl;
    }
};

class people
{
private:
    int num;
    XB xingbie;
    date riqi;
    string name;

public:
    people(int n, XB xb, date r, string na);
    // 复制构造函数
    people(const people &p)
    {
        num = p.num;
        xingbie = p.xingbie;
        riqi = p.riqi;
        name = p.name;
    }
    // 隐式内联函数
    void show()
    {
        cout << "编号:" << num << endl;
        cout << "性别:";
        if (xingbie == man)
            cout << "男" << endl;
        else
            cout << "女" << endl;
        cout << "出生日期:";
        riqi.showdate();
        cout << "姓名:" << name << endl;
    }

    ~people()
    {
        cout << name << "的资料已删除" << endl;
    }
    // 显式内联函数
    inline void shownum();
    void setnum(int n = -1)
    {
        num = n;
    }
    void setname(string s)
    {
        name = s;
    }
};

people::people(int n, XB xb, date r, string na) : riqi(r)
{
    num = n;
    xingbie = xb;
    name = na;
}

void people::shownum()
{
    cout << "编号:" << num << endl;
}

int main()
{
    people a(1, man, date(2023, 3, 10), "张三");
    people b(a);
    a.show();
    b.show();
    b.setnum();
    a.setnum(2);
    b.setname("李四");
    a.show();
    b.show();
    return 0;
}