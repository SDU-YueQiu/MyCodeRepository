#include "deque"
#include "iomanip"
#include "map"
#include "math.h"
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
//#define double long double
const double eps = 1e-8;

inline int sgn(double x)
{
    if (fabs(x) < eps) return true;
    return x < 0 ? -1 : 1;
}
inline int dcmp(double x, double y)
{
    if (fabs(x - y) < eps) return 0;
    else
        return x < y ? -1 : 1;
}
struct point {
    double x, y;
    point(double x, double y) : x(x), y(y){};
    point(){};
};
struct line {
    point p1, p2;
    line(){};
    line(point &p1, point &p2) : p1(p1), p2(p2){};
};
struct circle {
    point c;
    double r;
    circle(){};
    circle(point c, double r) : c(c), r(r){};
};
double getM(point &a, point &b) { return fabs(a.x - b.x) + fabs(a.y - b.y); }
double getE(point &a, point &b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }

signed main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
    {
        point p11, p12, p21, p22;
        cin >> p11.x >> p11.y;
        cin >> p12.x >> p12.y;
        cin >> p21.x >> p21.y;
        cin >> p22.x >> p22.y;
        double r1 = getE(p11, p12) / 2;
        double r2 = getE(p21, p22) / 2;
        point c1 = {(p11.x + p12.x) / 2, (p11.y + p12.y) / 2};
        point c2 = {(p21.x + p22.x) / 2, (p21.y + p22.y) / 2};

        double dy1, dx1;
        double sit= sqrt(2)/2;
        dy1 = sgn(c2.y - c1.y) * r1 * sit;
        dx1 = sgn(c2.x - c1.x) * r1 * sit;
        double dy2, dx2;
        dy2 = -sgn(c2.y - c1.y) * r2 * sit;
        dx2 = -sgn(c2.x - c1.x) * r2 * sit;
        point P1(c1.x, c1.y), P2(c2.x + dx2, c2.y + dy2);
        cout << fixed << setprecision(10) << getM(P1, P2) << endl;
    }
    return 0;
}
