#include "cstring"
#include "deque"
#include "map"
#include "stack"
#include "vector"
#include <algorithm>
#include <iostream>

using namespace std;
#define endl '\n'
#define int long long
const int N = 1e6 + 10;
typedef pair<int, int> pii;

vector<int> G[N];
int n, m;
int scc[N];
int cnt;

inline int getN(int x) { return x * (x - 1) / 2; }

void dfs(int u)
{
    scc[u] = cnt;
    for (int i = 0; i < G[u].size(); ++i)
        if (scc[G[u][i]] == 0)
            dfs(G[u][i]);
}

pii vs[N];
bool vis[N];
bool cmp(pii &a, pii &b) { return a.first > b.first; }

int solve()
{
    for (int i = 1; i <= n; ++i)
    {
        vs[scc[i]].first++;
        vs[scc[i]].second += G[i].size();
    }
    for (int i = 1; i <= n; ++i)
        if (!vis[scc[i]])
        {
            vs[scc[i]].second /= 2;
            vis[scc[i]] = true;
        }
    sort(vs + 1, vs + n + 1, cmp);
    int ret = 0;
    int size = 0;
    for (int i = 1; vs[i].first != 0; ++i)
    {
        ret += getN(vs[i].first) - vs[i].second;
        size = i;
    }
    if (ret == 0)
        ret = getN(vs[size].first + vs[size - 1].first) - vs[size].second - vs[size - 1].second;
    return ret;
}

signed main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i)
        if (scc[i] == 0)
        {
            ++cnt;
            dfs(i);
        }
    cout << solve() << endl;
    return 0;
}
