#include<iostream>
using namespace std;

typedef long long LL;   //不开long long见祖宗
typedef pair<int, int> P;

const int maxn = 1e5 + 10;
const int max_log_n = 20;
const int INF = 0x3f3f3f3f;
const double eps = 1e-6;
const LL mod = 10007;

struct Node {
    int l, r;
    LL ch, muti, add, q1, q2, q3;
}tr[maxn * 4];

int n, m;

void change3(Node &u) {
    LL len = u.r - u.l + 1;
    u.q1 = len * u.ch % mod;
    u.q2 = u.q1 * u.ch % mod;
    u.q3 = u.q2 * u.ch % mod;
}

void change2(Node& u, LL m) {
    u.q1 = u.q1 * m % mod;
    u.q2 = u.q2 * m % mod * m % mod;
    u.q3 = u.q3 * m % mod * m % mod * m % mod;
}

void change1(Node &u, LL a) {
    LL len = u.r - u.l + 1;
    u.q3 = (u.q3 + 3 * u.q2 % mod * a % mod + 3 * u.q1 % mod * a  % mod * a % mod + len * a % mod * a % mod * a % mod) % mod;
    u.q2 = (u.q2 + 2 * u.q1 * a % mod + len * a % mod * a % mod) % mod;
    u.q1 = (u.q1 + len * a % mod) % mod;
}

void pushdown(int u) {
    Node &root = tr[u], &lsn = tr[u << 1], &rsn = tr[u << 1 | 1];
    if(root.ch != 0) {
        lsn.ch = rsn.ch = root.ch;
        lsn.add = rsn.add = 0;
        lsn.muti = rsn.muti = 1;
        change3(lsn);
        change3(rsn);
    }
    lsn.muti = lsn.muti * root.muti % mod;
    rsn.muti = rsn.muti * root.muti % mod;
    lsn.add = lsn.add * root.muti % mod;
    rsn.add = rsn.add * root.muti % mod;
    change2(lsn, root.muti);
    change2(rsn, root.muti);
    lsn.add = (lsn.add + root.add) % mod;
    rsn.add = (rsn.add + root.add) % mod;
    change1(lsn, root.add);
    change1(rsn, root.add);
    root.add = 0;
    root.muti = 1;
    root.ch = 0;
}

void pushup(int u) {
    Node &root = tr[u], &lsn = tr[u << 1], &rsn = tr[u << 1 | 1];
    root.q1 = (lsn.q1 + rsn.q1) % mod;
    root.q2 = (lsn.q2 + rsn.q2) % mod;
    root.q3 = (lsn.q3 + rsn.q3) % mod;
}

void build(int u, int l, int r) {
    int mid = l + r >> 1;
    tr[u] = {l, r, 0, 1, 0, 0, 0, 0};
    if(l == r) return ;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

void modify(int u, int l, int r, LL m, LL a, LL c) {
    if(tr[u].l >= l && tr[u].r <= r) {
        if(m != 1) {
            tr[u].add = (tr[u].add * m ) % mod;
            tr[u].muti = (tr[u].muti * m) % mod;
            change2(tr[u], m);
        }
        else if(a != 0) {
            tr[u].add = (tr[u].add + a) % mod;
            change1(tr[u], a);
        }
        else if(c != 0) {
            tr[u].ch = c;
            tr[u].add = 0; tr[u].muti = 1;
            change3(tr[u]);
        }
    }
    else{
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if(l <= mid) modify(u << 1, l, r, m, a, c);
        if(r > mid) modify(u << 1 | 1, l, r, m, a, c);
        pushup(u);
    }
}


LL query(int u, int l, int r, int p) {
    if(tr[u].l >= l && tr[u].r <= r) {
        if(p == 1) return tr[u].q1 % mod;
        else if(p == 2) return tr[u].q2 % mod;
        else if(p == 3) return tr[u].q3 % mod;
    }
    else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if(r <= mid) return query(u << 1, l, r, p);
        else if(l > mid) return query(u << 1 | 1, l, r, p);

        return (query(u << 1, l, r, p) + query(u << 1 | 1, l, r, p)) % mod;
    }
}

void solve() {
    build(1, 1, n);
    for(int k = 1; k <= m; k++) {
        int op, l, r, v;
        cin >> op >> l >> r >> v;
        if(op == 1) modify(1, l, r, 1, v, 0);
        else if(op == 2) modify(1, l, r, v, 0, 0);
        else if(op == 3) modify(1, l, r, 1, 0, v);
        else if(op == 4) cout << query(1, l, r, v) % mod << endl;
    }
}


int main() {
    ios::sync_with_stdio(false);
    int t = 1;
    while(cin >> n >> m && n) {
        solve();
    }
    return 0;
}
