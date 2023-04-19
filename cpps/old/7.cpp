//101353B
#pragma GCC optimize(2)
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
#define llu unsigned long long
#define lint long long

inline llu readInt() {
    llu fx = 1, xx = 0;
    char ch = getchar();
    while (!isdigit(ch)) {
        ch = getchar();
    }
    while (isdigit(ch)) {
        xx *= 10;
        xx += ch - 48;
        ch = getchar();
    }
    return fx * xx;
}
unsigned long long n, m, p;
int T;
void solve() {
    n = readInt(), m = readInt(), p = readInt();
    if (p <= n) {
        printf("Case %d: 0\n", ++T);
        return;
    }
    double now = 1.0 * p / n;
    double ans = 1.0 * ceil((log(now)) / log((m * 0.01 + 1)));
    lint anss = ans;
    // cout << "Case " << ++T << ": ";
    // cout << anss << endl;
    printf("Case %d: %lld\n", ++T, anss);
}
int main() {
    T = 0;
    int t = (int) readInt();
    while (t--)
        solve();
    return 0;
}