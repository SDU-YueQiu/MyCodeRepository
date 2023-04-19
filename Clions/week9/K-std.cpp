#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <map>
#include <queue>
#include <algorithm>
#define maxn 100005
using namespace std;
#define int long long
const int inf = 0x7fffffffffffff; // 13

int n, m;
int a[maxn];
int ans = inf;

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i + m - 1 <= n; i++)
    {
        ans = min(ans, a[i + m - 1] - a[i]);
    }
    cout << ans;

    return 0;
}