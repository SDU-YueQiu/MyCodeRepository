#include <bits/stdc++.h>
using namespace std;
#define int long long
#define random(a, b) (rand() % (b - a + 1) + a)
const int inf = 1e18;
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
int dp[maxn][11][2]; // dp[i][j][k]代表到第i个点已经发动j次咆哮，且第i-1到第i个点是否发动技能
int x, n, k, m;
int a[maxn];
void solve()
{
    cin >> x >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    memset(dp, 0x3f, sizeof dp);
    dp[1][1][1] = 0;
    dp[1][0][0] = a[1];
    n++;
    a[n] = x;
    for (int i = 2; i <= n; i++)
    {
        for (int k1 = 0; k1 < k; k1++) // 前面发动了几次技能
        {
            dp[i][k1 + 1][1] = min(dp[i][k1 + 1][1], dp[i - 1][k1][0]);
            dp[i][k1][0] = min(dp[i][k][0], dp[i - 1][k1][1] + (a[i] - a[i - 1]) * 2);
            dp[i][k1][0] = min(dp[i][k1][0], dp[i - 1][k1][0] + (a[i] - a[i - 1]));
        }
    }
    int ans = 1e18;
    for (int i = 0; i <= k; i++)
    {
        ans = min({ans, dp[n][i][0], dp[n][i][1]});
    }
    cout << ans;
}
signed main()
{
    solve();
    return 0;
}