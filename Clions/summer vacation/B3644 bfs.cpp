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

int topo[N];
int rd[N];
vector<int> edges[N];

inline void addEdge(int from, int to)
{
    edges[from].push_back(to);
    ++rd[to];
    return;
}

void bfs(int n)
{
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (rd[i] == 0)
            q.push(i);
    int cnt = 0;
    while (!q.empty())
    {
        int top = q.front();
        q.pop();
        cout<<top<<" ";
        rd[top]=-1;
        for (auto to: edges[top])
        {
            --rd[to];
            if(rd[to]==0)
                q.push(to);
        }
    }
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
    bfs(n);
    return 0;
}