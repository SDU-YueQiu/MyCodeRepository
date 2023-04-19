#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;
#define int long long
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> pii;
const int mod = 10007;
int tnode[3][4 * N], tagchg[4 * N], tagadd[4 * N], tagmul[4 * N];
inline int ls(int p) { return p << 1; }
inline int rs(int p) { return (p << 1) | 1; }

void pushup(int p)
{
    for (int i = 0; i < 3; ++i)
        tnode[i][p] = tnode[i][ls(p)] + tnode[i][rs(p)];
}
inline int mmid(int pl, int pr) { return (pl + pr) >> 1; }
void build(int p, int pl, int pr)
{
    tagadd[p] = 0;
    tagchg[p] = 0;
    tagmul[p] = 0;
    if (pl == pr)
    {
        tnode[0][p] = 0;
        tnode[1][p] = 0;
        tnode[2][p] = 0;
        return;
    }
    int mid = mmid(pl, pr);
    build(ls(p), pl, mid);
    build(rs(p), mid + 1, pr);
    pushup(p);
}
void addtag(int p, int pl, int pr, int mode, int d)
{
    if (mode == 1)
    {
        tagadd[p] += d;
        tagadd[p] %= mod;
        tnode[0][p] += (pr - pl + 1) * d;
        tnode[0][p] %= mod;
        tnode[1][p] += (pr - pl + 1) * d * d + 2 * d * tnode[0][p];
        tnode[1][p] %= mod;
        tnode[2][p] += (pr - pl + 1) * d * d * d % mod + 3 * d * tnode[1][p] % mod + 3 * d * d * tnode[0][p] % mod;
        tnode[2][p] %= mod;
    }
    if (mode == 2)
    {
        tagmul[p] *= d;
        tagadd[p] *= d;
        tagadd[p] %= mod;
        tagchg[p] *= d;
        tagchg[p] %= mod;
        tagmul[p] %= mod;
        for (int i = 0; i < 3; ++i)
        {
            tnode[i][p] *= d;
            tnode[i][p] %= mod;
        }
    }
    if (mode == 3)
    {
        tagchg[p] = d;
        tagadd[p] = tagmul[p] = 0;
        tnode[0][p] = (pr - pl + 1) * d;
        tnode[0][p] %= mod;
        tnode[1][p] = (pr - pl + 1) * d * d;
        tnode[1][p] %= mod;
        tnode[2][p] = (pr - pl + 1) * d * d * d;
        tnode[2][p] %= mod;
    }
}
void pushdown(int p, int pl, int pr)
{
    int mid = mmid(pl, pr);
    if (tagchg[p])
    {
        addtag(ls(p), pl, mid, 3, tagchg[p]);
        addtag(rs(p), mid + 1, pr, 3, tagchg[p]);
        tagchg[p] = 0;
    }
    if (tagmul[p])
    {
        addtag(ls(p), pl, mid, 2, tagmul[p]);
        addtag(rs(p), mid + 1, pr, 2, tagmul[p]);
        tagmul[p] = 0;
    }
    if (tagadd[p])
    {
        addtag(ls(p), pl, mid, 1, tagadd[p]);
        addtag(rs(p), mid + 1, pr, 1, tagadd[p]);
        tagadd[p] = 0;
    }
    return;
}
void update(int p, int pl, int pr, int l, int r, int mode, int d)
{

    if (l <= pl && pr <= r)
    {
        addtag(p, pl, pr, mode, d);
        return;
    }
    pushdown(p, pl, pr);
    int mid = mmid(pl, pr);
    if (l <= mid)
        update(ls(p), pl, mid, l, r, mode, d);
    if (r > mid)
        update(rs(p), mid + 1, pr, l, r, mode, d);
    pushup(p);
    return;
}
int qur(int p, int pl, int pr, int l, int r, int mode)
{
    if (l <= pl && pr <= r)
        return tnode[mode][p];
    pushdown(p, pl, pr);
    int res = 0;
    int mid = mmid(pl, pr);
    if (l <= mid)
        res += qur(ls(p), pl, mid, l, r, mode);
    res %= mod;
    if (r > mid)
        res += qur(rs(p), mid + 1, pr, l, r, mode);
    res %= mod;
    return res;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    build(1, 1, n);
    while (m--)
    {
        int o, x, y, z;
        cin >> o >> x >> y >> z;
        if (o <= 3 && o > 0)
        {
            update(1, 1, n, x, y, o, z);
            cout << qur(1, 1, n, x, y, 1) << endl;
        }
        if (o == 4)
            cout << qur(1, 1, n, x, y, z - 1) << endl;
    }
    cin >> m >> n;
    return 0;
}