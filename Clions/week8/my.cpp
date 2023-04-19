#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int maxn = 1e5 + 10;
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> ans(n + 1, vector<int>(m + 1));
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    vector<vector<int>> vis(n + 1, vector<int>(m + 1));
    vector<vector<vector<pair<int, int>>>> to(n + 1, vector<vector<pair<int, int>>>(m + 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            ans[i][j] = a[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        for (int j = 1; j <= m; j++)
        {
            int x = i, y = j;
            if (s[y - 1] == 'D')
            {
                int dx = x + 1, dy = y;
                if (dx <= n)
                    to[dx][dy].push_back({x, y});
            }
            if (s[y - 1] == 'U')
            {
                int dx = x - 1, dy = y;
                if (dx >= 1)
                    to[dx][dy].push_back({x, y});
            }
            if (s[y - 1] == 'L')
            {
                int dx = x, dy = y - 1;
                if (dy >= 1)
                    to[dx][dy].push_back({x, y});
            }
            if (s[y - 1] == 'R')
            {
                int dx = x, dy = y + 1;
                if (dy <= m)
                    to[dx][dy].push_back({x, y});
            }
        }
    }
    int now = 1;
    for (int f1 = 0; f1 < 32; f1++)
    {
        queue<pair<int, int>> q;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                vis[i][j] = 0;
            }
        }
        vector<vector<int>> b(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (a[i][j] == now)
                {
                    q.push({i, j});
                    b[i][j] = 0;
                } else
                    b[i][j] = 1e8;
            }
        }
        while (!q.empty())
        {
            int x = q.front().first, y = q.front().second;
            q.pop();
            if (vis[x][y])
                continue;
            vis[x][y] = 1;
            for (auto x1: to[x][y])
            {
                int dx = x1.first, dy = x1.second;
                if (vis[dx][dy] != 1)
                {
                    b[dx][dy] = min(b[dx][dy], b[x][y] + 1);
                    q.push({dx, dy});
                }
            }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (a[i][j] == now)
                {
                    to[i][j].clear();
                }
            }
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (b[i][j] < 1e7)
                    ans[i][j] = min(ans[i][j], (b[i][j] + 1) * now);
            }
        }
        now *= 2;
    }
    int q;
    cin >> q;
    for (int i = 1; i <= q; i++)
    {
        int x, y;
        cin >> x >> y;
        cout << ans[x][y] << endl;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}