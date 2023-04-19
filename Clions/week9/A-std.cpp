#include <cstdio>

using namespace std;

const int N = 1.5e6 + 10;

#define isdigit(x) (x >= '0' && x <= '9')
template <typename T>
void read(T &x) {
    x = 0;
    bool f = false;
    char ch = getchar();
    while(!isdigit(ch)) f |= ch == '-', ch = getchar();
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    x = f ? -x : x;
    return;
}

int n, m;

#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
int val[N << 2], cnt[N << 2];
void insert(int now, int l, int r, int p, int x) {
    ++cnt[now];
    if(l == r) {
        val[now] = x;
        return;
    }
    int mid = (l + r) >> 1;
    if(p <= mid) insert(ls(now), l, mid, p, x);
    else insert(rs(now), mid + 1, r, p, x);
    return;
}
int query(int now, int l, int r, int p) {
    --cnt[now];
    if(l == r) return val[now];
    int mid = (l + r) >> 1;
    if(cnt[ls(now)] >= p) return query(ls(now), l, mid, p);
    else return query(rs(now), mid + 1, r, p - cnt[ls(now)]);
}

int main() {
    read(n), read(m);
    const int L = 1, R = n + m * 2;
    for(int i = 1, tmp;i <= n; ++i)
        read(tmp), insert(1, L, R, m + i, tmp);
    for(int i = 1, opt, x, ans; i <= m; ++i) {
        read(opt), read(x);
        ans = query(1, L, R, x);
        printf("%d\n", ans);
        if(opt == 1)
            insert(1, L, R, n + m + i, ans);
        else
            insert(1, L, R, m - i, ans);
    }
    return 0;
}
