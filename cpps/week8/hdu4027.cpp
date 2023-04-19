#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>

#define endl '\n'
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> pii;
inline int ls(int p) { return p * 2; }
inline int rs(int p) { return p * 2 + 1; }
inline int mmid(int pl, int pr) { return (pl + pr) >> 1; }
int tnode[4 * N];
bool tag[4 * N];
void pushup(int p)
{
    tnode[p] = tnode[ls(p)] + tnode[rs(p)];
    tag[p] = tag[ls(p)] && tag[rs(p)];
}
void build(int p, int pl, int pr)
{
    if (pl == pr)
    {
        cin >> tnode[p];
        if (tnode[p] == 1)
            tag[p] = 1;
        return;
    }
    int mid = mmid(pl, pr);
    build(ls(p), pl, mid);
    build(rs(p), mid + 1, pr);
    pushup(p);
}
void update(int p, int pl, int pr, int l, int r)
{
    if (tag[p])
        return;
    int mid = mmid(pl, pr);
    if (l <= pl && pr <= r)
    {
        if (pl == pr)
        {
            tnode[p] = sqrt(tnode[p]);
            if (tnode[p] == 1)
                tag[p] = 1;
            return;
        }
        update(ls(p), pl, mid, l, r);
        update(rs(p), mid + 1, pr, l, r);
        pushup(p);
        return;
    }
    if (l <= mid)
        update(ls(p), pl, mid, l, r);
    if (r > mid)
        update(rs(p), mid + 1, pr, l, r);
    pushup(p);
}
int qur(int p, int pl, int pr, int l, int r)
{
    if (l <= pl && pr <= r)
        return tnode[p];
    int res = 0;
    int mid = mmid(pl, pr);
    if (l <= mid)
        res += qur(ls(p), pl, mid, l, r);
    if (r > mid)
        res += qur(rs(p), mid + 1, pr, l, r);
    return res;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    int t=1;
    while (cin >> n)
    {
        cout<<"Case #"<<t++<<":\n";
        build(1, 1, n);
        cin >> m;
        while (m--)
        {
            int x, y, z;
            cin >> x >> y >> z;
            if(y>z) swap(y,z);
            if (x == 0)
                update(1, 1, n, y, z);
            else
                cout << qur(1, 1, n, y, z) << endl;
        }
        cout<<endl;
    }
    return 0;
}