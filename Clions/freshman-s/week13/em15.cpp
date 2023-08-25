#include "algorithm"
#include <iostream>
using namespace std;

class Point
{
private:
    int x, y;

public:
    Point(int a, int b) : x(a), y(b) {}
    inline int getx() { return x; }
    inline int gety() { return y; }
};
bool cmp(Point &a, Point &b)
{
    if (a.getx() == b.getx())
        return a.gety() < b.gety();
    return a.getx() < b.getx();
}


int main()
{
    vector<Point> pts = {Point(1, 2), Point(4, 10), Point(5, 1), Point(1, 10), Point(3, 2), Point(2, 6), Point(4, 3), Point(2, 1)};
    sort(pts.begin(), pts.end(), cmp);
    for (auto &p: pts)
        cout << p.getx() << " " << p.gety() << endl;
    return 0;
}
