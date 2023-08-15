#include "cmath"
#include "iostream"
#include "map"
#include "queue"
#include "set"
#include "stack"
#include "stdio.h"
#include "vector"

using namespace std;
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
//#define int long long
const int N = 100 + 5;

stack<int> topo;
vector<int> edges[N];

inline void addEdge(int from, int to)
{
    edges[from].push_back(to);
    return;
}

short vis[N];

void dfs(int x)
{
    vis[x] = -1;
    for (int i=0;i<edges[x].size();++i)
        if (vis[edges[x][i]] == 0)
            dfs(edges[x][i]);
    vis[x] = 1;
    topo.push(x);
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        int x;
        cin >> x;
        while (x != 0)
        {
            addEdge(i, x);
            cin >> x;
        }
    }
    for (int i = 1; i <= n; ++i)
        if (vis[i] == 0)
            dfs(i);
    while (!topo.empty())
    {
        cout << topo.top()<<" ";
        topo.pop();
    }
    return 0;
}