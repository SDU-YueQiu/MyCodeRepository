#include "algorithm"
#include "cmath"
#include "map"
#include "set"
#include "vector"
#include <iostream>

using namespace std;
//#define int long long
typedef long long ll;
const int N = 1e5 + 10;

signed main()
{
//    ios::sync_with_stdio(false);

    freopen("1.in", "r", stdin);
    freopen("std.out", "w", stdout);
    int l, r;
    cin >> l >> r;
    int a = 1, b = 1, c = 0, n = 3;
    for (int i = 1; i <= r; i++)
    {
        c++;
        if (c > n) c -= n, b++;
        if (b > n) b -= n, a++;
        if (a > n) a -= n, n++;
        if (i >= l)
        {
            int s1 = pow(a, n), s2 = pow(b, n), s3 = pow(c, n);
            if (s1 + s2 < s3)
                printf("%d^%d+%d^%d<%d^%d\n", a, n, b, n, c, n);
            else
                printf("%d^%d+%d^%d>%d^%d\n", a, n, b, n, c, n);
        }
    }
    return 0;
}
