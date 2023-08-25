#include "algorithm"
#include "queue"
#include "set"
#include "tuple"
#include <iostream>
using namespace std;
#define int long long
#define endl '\n'
typedef long long ll;
const int N = 1e5 + 10;

struct node {
    //int id;
    int size;
    int imp;
    int sumimp;
    int fa;
} a[N];

struct id {
    int r;
    bool operator<(const id &b) const
    {
        return (a[r].size == a[b.r].size) ? (r < b.r) : (a[r].size > a[b.r].size);
    }
};

vector<int> son[N];
set<id> sons[N];
vector<int> e[N];

void build(int r)
{
    a[r].size = 1;
    a[r].sumimp = a[r].imp;

    for (int i = 0; i < son[r].size(); ++i)
    {
        build(son[r][i]);
        a[r].size += a[son[r][i]].size;
        a[r].sumimp += a[son[r][i]].sumimp;
        sons[r].insert({son[r][i]});
    }
    return;
}

inline void era(int r, int s)
{
    sons[r].erase({s});
    a[r].size -= a[s].size;
    a[r].sumimp -= a[s].sumimp;
}

inline void link(int r, int s)
{
    sons[r].insert({s});
    a[r].size += a[s].size;
    a[r].sumimp += a[s].sumimp;
    a[s].fa = r;
}

void cut(int x)
{
    int fa = a[x].fa;
    if (sons[x].empty())
        return;
    era(fa, x);
    auto it = sons[x].begin();
    int hs = it->r;
    era(x, hs);
    link(hs, x);
    link(fa, hs);
}

bool vis[N];

void buildtree(int r)
{
    vis[r] = 1;
    for (int i = 0; i < e[r].size(); ++i)
        if (!vis[e[r][i]])
        {
            son[r].push_back(e[r][i]);
            a[e[r][i]].fa = r;
            buildtree(e[r][i]);
        }
}

void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].imp;
    a[1].fa = 0;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    buildtree(1);
    build(1);
    for (int i = 1; i <= m; ++i)
    {
        int o, x;
        cin >> o >> x;
        if (o == 1)
            cout << a[x].sumimp << endl;
        else
            cut(x);
    }
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}