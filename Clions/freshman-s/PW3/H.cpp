#include "algorithm"
#include "cmath"
#include "map"
#include "set"
#include "vector"
#include <iostream>

using namespace std;
#define int long long
typedef long long ll;
const int N = 1e5 + 10;
#define MAXN 200000

int a, b;
int tag[MAXN], x[MAXN], num;

void count()
{
    int s = 10, k = 10;
    while (s < a) s *= 10;
    k = s / 10;
    while (k) s += k, k /= 10;
    int res = s - a;
    int cnt = res / 9 + 1;
    a += cnt * 9;
    while (a - s >= 9) cnt--, a -= 9;
    num++;
    tag[num] = 1;
    x[num] = cnt;

    int l = 1;
    while (l < a) l *= 10;
    l /= 10;
    while (a > 10 && l > 1)
    {
        tag[++num] = 0;
        x[num] = 1;
        a %= l;
        l /= 10;
    }
}

void check(int len)
{
    int s = pow(10, len);
    int res = (b / s) % 10;
    while ((a / s) % 10 != res)
    {
        a += 9 * s;
        tag[++num] = 1;
        x[num] = s;
        if (a / s >= 10)
        {
            tag[++num] = 0;
            x[num] = 1;
            a = a % (s * 10);
        }
    }
    if (a == b) return;
    check(len + 1);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin >> a >> b;
    cout << "Stable\n";
    count();
    check(0);
    cout << num << "\n";
    for (int i = 1; i <= num; i++)
    {
        if (tag[i] == 1) cout << "+ ";
        else cout << "- ";
        cout << x[i] << '\n';
    }
    return 0;
}
