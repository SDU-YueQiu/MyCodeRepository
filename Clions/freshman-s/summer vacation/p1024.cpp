#include "algorithm"
#include "cmath"
#include "cstring"
#include "iomanip"
#include "iostream"
#include "map"
#include "queue"
#include "set"
#include "string"
#include "vector"

using namespace std;
//#define int long long
#define endl '\n'
typedef long long ll;
const int N = 1e6 + 10;
typedef pair<int, int> pii;
const double eps = 1e-6;

double a, b, c, d;
inline double fun(double x) { return a * x * x * x + b * x * x + c * x + d; }

double erfen(double x1, double x2)
{
    double l = x1, r = x2;
    int t = 10;
    double ret;
    while (t--)
    {
        ret = (l + r) / 2;
        if (fun(ret) * fun(l) < 0)
            r = ret;
        if (fun(ret) * fun(r) < 0)
            l = ret;
    }
    return ret;
}

vector<double> ans;

signed main()
{
    //ios::sync_with_stdio(false);

    cin >> a >> b >> c >> d;

    for (int i = -100; i <= 100; ++i)
    {
        double f1 = fun(i), f2 = fun(i + 1);

        if (fabs(f1 - 0) < eps)
            ans.push_back(i);
        if ((f1 * f2) < 0 && fabs(f1 * f2) > eps)
            ans.push_back(erfen(i, i + 1));
    }

    cout << fixed << setprecision(2) << ans[0] << " " << ans[1] << " " << ans[2];
    return 0;
}