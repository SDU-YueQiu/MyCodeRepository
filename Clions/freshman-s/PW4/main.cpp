#include "algorithm"
#include "map"
#include "set"
#include <iostream>
#include <vector>
using namespace std;
#define pii pair<int, int>
#define int long long
const int maxn = 2e5 + 10;
bool cmp(pii a, pii b) { return a.second < b.second; }
pii arr[maxn];
pii a[maxn];
pii fish[maxn];

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, l;
    cin >> n >> m >> l;
    for (int i = 1; i <= n; i++)
        cin >> fish[i].first >> fish[i].second;
    for (int i = 1; i <= m; i++) cin >> arr[i].first, arr[i].second = i;
    sort(arr + 1, arr + 1 + m);
    for(int i=1;i<=m;i++)a[i].second=arr[i].second;
    for (int i = 1; i <= n; i++)
    {
        int len = l-fish[i].second;
        if (len < 0) continue;
        int ql = fish[i].first - len, qr = fish[i].first + len;
        int l = lower_bound(arr + 1, arr + 1 + m, make_pair(ql, 0ll)) - arr;
        int r = lower_bound(arr + 1, arr + 1 + m, make_pair(qr+1, 0ll)) - arr;
        a[l].first++;
        a[r].first--;
    }
    for (int i = 1; i <= m; i++) a[i].first += a[i - 1].first;
    sort(a + 1, a + 1 + m, cmp);
    for (int i = 1; i <= m; i++) cout << a[i].first << '\n';
    return 0;
}
