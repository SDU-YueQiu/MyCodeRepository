#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <cmath>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 3e3 + 10;
typedef pair<int, int> pii;
typedef long double ldb;
const double INF = 1e100;

struct node
{
    double x;
    double y;
    int di;
    double dis;
    int id;
    node(int b, double c)
    {
        id = b;
        dis = c;
    };
    node()
    {
        id = 0;
    }
    bool operator<(const node &a) const
    {
        return dis > a.dis;
    }
};
node nodes[MAXN];

inline double dist(node &a, node &b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int n;
double dis[MAXN];
bool done[MAXN];
double v[10];
double edis[MAXN][MAXN];

void dij(int s, int t)
{
    for (int i = 1; i <= n; i++)
    {
        dis[i] = INF;
        done[i] = false;
    }
    dis[s] = 0;
    priority_queue<node> Q;
    Q.push(node(s, dis[s]));
    while (!Q.empty())
    {
        node u = Q.top();
        Q.pop();
        if (done[u.id])
            continue;
        done[u.id] = true;
        if (u.id == t)
        {
            printf("%.10f", dis[t]);
            return;
        }
        for (int i = 1; i <= n; ++i)
        {
            if (i != u.id)
            {
                if (done[i])
                    continue;
                if (dis[i] > edis[u.id][i] + u.dis)
                {
                    dis[i] = edis[u.id][i] + u.dis;
                    Q.push(node(i, dis[i]));
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= 4; ++i)
        cin >> v[i];
    cin >> v[0];
    int s, t;
    cin >> s >> t;
    for (int i = 1; i <= n; ++i)
    {
        cin >> nodes[i].x >> nodes[i].y;
        nodes[i].id = i;
        if (nodes[i].x >= 1)
        {
            if (nodes[i].y >= 1)
                nodes[i].di = 1;
            else
                nodes[i].di = 4;
        }
        else
        {
            if (nodes[i].y >= 1)
                nodes[i].di = 2;
            else
                nodes[i].di = 3;
        }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
        {
            double mv = v[0];
            if (nodes[i].di == nodes[j].di)
                mv = v[nodes[i].di];
            double tmpt = dist(nodes[i], nodes[j]) / mv;
            edis[i][j] = tmpt;
            edis[j][i] = tmpt;
        }
    dij(s, t);
    return 0;
}