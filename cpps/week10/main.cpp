#include "algorithm"
#include "cstdio"
#include "map"
#include "math.h"
#include "queue"
#include "set"
#include "stack"
#include "tuple"
#include <iostream>

using namespace std;
#define int long long
#define endl '\n'
typedef long long ll;
const int N = 1e5 + 10;
const double eps = 1e-8;
typedef pair<int, int> pii;

struct node
{
    // int id;
    int size;
    int imp;
    int sumimp;
    int fa;
    bool operator < (node &a)
    {
        return size < a.size;
    }
} a[N];

vector<int> son[N];
priority_queue<node> sons[N];

void build(int r)
{
    a[r].size = 1;
    a[r].sumimp = a[r].imp;

    for (int i = 0; i < son[i].size(); ++i)
    {
        build(son[r][i]);
        a[r].size += a[son[r][i]].size;
        a[r].sumimp += a[son[r][i]].sumimp;
        sons[r].push(a[son[r][i]]);
    }
    return;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].imp;
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        son[u].push_back(v);
        a[v].fa = u;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}
