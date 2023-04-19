#include "algorithm"
#include "cmath"
#include "cstdio"
#include "cstring"
#include "queue"
#include "set"
#include "stack"
#include "vector"
#include <iostream>
#include <tuple>

using namespace std;
#define endl '\n'
#define int long long
const int N = 1e6 + 10;
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
const int INF = 1e18;


void solve()
{
    //input
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            cin >> a[i][j];
        }
    }
    vector<vector<vector<pii>>> backto(n + 1, vector<vector<pii>>(m + 1));
    for (int i = 1; i <= n; ++i)
    {
        string s;
        cin >> s;
        for (int j = 1; j <= m; ++j)
        {
            char tj = s[j - 1];
            if (tj == 'U' && i > 1)
            {
                backto[i - 1][j].push_back({i, j});
            } else if (tj == 'D' && i < n)
            {
                backto[i + 1][j].push_back({i, j});
            } else if (tj == 'L' && j > 1)
            {
                backto[i][j - 1].push_back({i, j});
            } else if (tj == 'R' && j < m)
            {
                backto[i][j + 1].push_back({i, j});
            }
        }
    }
    //倍增
    vector<vector<int>> ans(n + 1, vector<int>(m + 1, INF));
    for (int ii = 0; ii < 32; ++ii)
    {
        vector<vector<bool>> vis(n + 1, vector<bool>(m + 1, 0));
        queue<tiii> q;
        int num = (1 << ii);
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (a[i][j] == num)
                    q.push({i, j, 1});
            }
        }
        while (!q.empty())
        {
            tiii top = q.front();
            q.pop();
            int x = get<0>(top);
            int y = get<1>(top);
            int b = get<2>(top);
            vis[x][y] = true;
            ans[x][y] = min(ans[x][y], b * num);
            for(int k=0;k<backto[x][y].size();++k)
                if(!vis[backto[x][y][k].first][backto[x][y][k].second])
                    q.push({backto[x][y][k].first,backto[x][y][k].second,b+1});
        }
    }
    //qurry
    int q;
    cin>>q;
    while(q--)
    {
        int x,y;
        cin>>x>>y;
        cout<<ans[x][y]<<endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}
