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

void print(int a, int b, int c, int n, int num)
{
    if (num == 0) return;
    int s1 = pow(a, n), s2 = pow(b, n), s3 = pow(c, n);
    if (s1 + s2 < s3)
        printf("%d^%d+%d^%d<%d^%d\n", a, n, b, n, c, n);
    else
        printf("%d^%d+%d^%d>%d^%d\n", a, n, b, n, c, n);
    c++;
    if (c > n) c -= n, b++;
    if (b > n) b -= n, a++;
    if (a > n) a -= n, n++;
    print(a, b, c, n, num - 1);
}

void find(int a, int b, int c, int n, int l, int num)
{
    while (l > n * n * n) l -= n * n * n, n++;
    while (l > n * n) l -= n * n, a ++;
    while (l > n) l -= n, b++;
    c = l;
    print(a, b, c, n, num);
}

signed main()
{
//    ios::sync_with_stdio(false);
//    int l = read(), r = read();
    freopen("1.in", "r", stdin);
    freopen("my.out", "w", stdout);
    int l, r;
    cin >> l >> r;
    find(1, 1, 1, 3, l, r - l + 1);
    return 0;
}
