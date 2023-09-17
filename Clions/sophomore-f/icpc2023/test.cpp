#include "cmath"
#include "deque"
#include "iomanip"
#include "map"
#include "queue"
#include "set"
#include "string"
#include "vector"
#include <algorithm>
#include <iostream>
using namespace std;
#define endl '\n'
//#define int long long
typedef long long ll;
const int N = 1e6 + 10;
typedef pair<int, int> pii;
const double eps = 1e-6;
struct point {
    double x, y;
    point(double x, double y) : x(x), y(y){};
    point(){};
};
double getM(point &a, point &b) { return fabs(a.x - b.x) + fabs(a.y - b.y); }
double getE(point &a, point &b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }

inline int sgn(double x)
{
    if (fabs(x) < eps) return true;
    return x < 0 ? -1 : 1;
}
signed main()
{
    point c1(4.5, 3.5);
    point c2(1, 0.5);
    double r1 = sqrt(10) / 2;
    double r2 = sqrt(5) / 2;

    double sit = 0.785398;
    point p1(4.5 - sqrt(10) / 2 * cos(sit), 3.5 - sqrt(10) / 2 * sin(sit));
    //point p2(1 + sqrt(5) / 2 * cos(sit), 0.5 + sqrt(5) / 2 * sin(sit));
    point p2(1, 0.5);
    cout << getM(p1, p2);
    return 0;
}
//sit=0.785398
