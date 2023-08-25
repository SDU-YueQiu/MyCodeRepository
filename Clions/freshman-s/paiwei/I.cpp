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
const int N = 1e4 + 10;
const double eps = 1e-8;
typedef pair<int, int> pii;
const int mod = 1e9 + 7;
const int INF = 1e10;
int K, L, n;
int ans[N][755];
int T[755][755];
int P[N];

inline int mid(int x, int y) { return (x + y) >> 1; }

pii find(int row, int p)
{
    pii lr;
    int l = 1, r = K + 1;
    int tofind = p - L;
    while (l < r)
    {
        int mmid = (l + r) >> 1;
        if (T[row][mmid] >= tofind)
            r = mmid;
        else
            l = mmid + 1;
    }
    lr.first = l;
    l = 1;
    r = K + 1;
    if (l == 1 && r == 2 && T[row][1] > tofind)
    {
        lr.second = 0;
        return lr;
    }
    tofind = p + L;
    while (l < r)
    {
        int mmid = l + (r - l + 1) / 2;
        if (T[row][mmid] <= tofind)
            l = mmid;
        else
            r = mmid - 1;
    }
    if (r == 1 && T[row][1] > tofind)
        lr.second = 0;
    else
        lr.second = r;
    return lr;
}
int d[N][755];

int solve()
{
    int tans = 0;
    for (int i = 1; i <= K; ++i)
        ans[1][i] = 1;
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 1; j <= K; ++j)
        {
            pii lr = find(j, P[i - 1]);
            if (lr.first > lr.second)
                continue;
            if (lr.first == K + 1)
                continue;
            int ii = j;
            d[i][lr.first] += ans[i - 1][ii];
            d[i][lr.second + 1] -= ans[i - 1][ii];
        }
        for (int j = 1; j <= K; ++j)
        {
            ans[i][j] = ans[i][j - 1] + d[i][j];
            ans[i][j] %= mod;
        }
    }
    for (int i = 1; i <= K; ++i)
    {
        tans += ans[n][i];
        tans %= mod;
    }
    return (tans+ mod) % mod;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> K >> L;
    for (int i = 1; i <= K; ++i)
    {
        for (int j = 1; j <= K; ++j)
        {
            cin >> T[i][j];
        }
    }
    cin >> n;
    for (int i = 1; i < n; ++i)
        cin >> P[i];
    cout << solve();
    return 0;
}
