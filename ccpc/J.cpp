#include "cmath"
#include "iomanip"
#include "iostream"
#include "map"
#include "queue"
#include "set"
#include "stack"
#include "vector"

        using namespace std;
#define int long long
const int N = 60;
#define endl '\n'
typedef pair<int, int> pii;
#define double long double
const double INF = 1e100;
const double eps = 1e-10;


struct point {
    double x, y, z;
};
struct plane {
    point p0;
    point n;
};

point operator+(const point &a, const point &b)
{
    return point{a.x + b.x, a.y + b.y, a.z + b.z};
}
point operator-(const point &a, const point &b)
{
    return point{a.x - b.x, a.y - b.y, a.z - b.z};
}

double dot(const point &a, const point &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
point cross(const point &a, const point &b)
{
    return point{a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z,
                 a.x * b.y - a.y * b.x};
}
point sub(point u, point v)
{
    point ret;
    ret.x = u.x - v.x;
    ret.y = u.y - v.y;
    ret.z = u.z - v.z;
    return ret;
}
double dist(const point &p, const plane &pl)
{
    return fabs(dot(p - pl.p0, pl.n));
}
point normal(point &a, point &b, point &c)
{
    return cross(sub(a, b), sub(b, c));
}

point a[N];

void toOne(point &nor)
{
    double t = sqrt(nor.x * nor.x + nor.y * nor.y + nor.z * nor.z);
    nor.x /= t;
    nor.y /= t;
    nor.z /= t;
}
signed main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i].x >> a[i].y >> a[i].z;
    double ans = INF;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            for (int k = j + 1; k < n; ++k)
            {
                point nor = normal(a[i], a[j], a[k]);
                toOne(nor);
                plane pl1;
                pl1.p0 = a[i];
                pl1.n = nor;
                double d[N];
                double mmax = -1;
                int tt;
                for (int t = 0; t < n; t++)
                {
                    d[t] = dist(a[t], pl1);
                    if (d[t] > mmax)
                    {
                        tt = t;
                        mmax = d[t];
                    }
                }
                plane pl2;
                pl2.n = nor;
                pl2.p0 = a[tt];
                double dpl = dist(a[i], pl2);
                bool flag = true;
                for (int u = 0; u < n; ++u)
                {
                    double d2 = dist(a[u], pl2);
                    if (fabs(d[u] + d2 - dpl) > eps)
                        flag = false;
                }
                if (flag)
                    ans = min(ans, dpl);
            }
    cout << setprecision(16) << ans;
    return 0;
}
