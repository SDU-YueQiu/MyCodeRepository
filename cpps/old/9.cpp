//101353G
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
int T, n, q;
int a[maxn], cnt[2 * maxn];
int s[maxn * 4][2][25];
int p[maxn * 4], f[maxn * 4];
int ans, B, v;
 
int lowbit(int x) {
  return x & (-x);
}
 
void init() {
  for(int i = 1; i < (1 << 20); i ++) {
    cnt[i] = cnt[i - lowbit(i)] + 1;
  }
}
 
void pushUp(int rt) {
  for(int i = 0; i < 21; i ++) {
    s[rt][0][i] = min(s[2 * rt][p[2 * rt]][i],
                      s[2 * rt + 1][p[2 * rt + 1]][i]);
    s[rt][1][i] = min(s[2 * rt][p[2 * rt] ^ 1][i],
                      s[2 * rt + 1][p[2 * rt + 1] ^ 1][i]);
  }
  p[rt] = 0;
}
 
void pushDown(int rt) {
  if(f[rt] == 0) return;
  p[2 * rt] = (p[2 * rt] + f[rt]) % 2;
  f[2 * rt] = (f[2 * rt] + f[rt]) % 2;
  p[2 * rt + 1] = (p[2 * rt + 1] + f[rt]) % 2;
  f[2 * rt + 1] = (f[2 * rt + 1] + f[rt]) % 2;
  f[rt] = 0;
}
 
void build(int l, int r, int rt) {
  p[rt] = 0;
  f[rt] = 0;
  if(l == r) {
    for(int t = 0; t < 2; t ++) {
      for(int i = 0; i < 21; i ++) {
        s[rt][t][i] = n + 1;
      }
    }
    s[rt][0][a[l]] = l;
    s[rt][1][20 - a[l]] = l;
    return;
  }
  int mid = (l + r) / 2;
  build(l, mid, 2 * rt);
  build(mid + 1, r, 2 * rt + 1);
  pushUp(rt);
}
 
void update(int L, int R, int l, int r, int rt) {
  if(L <= l && r <= R) {
    p[rt] = (p[rt] + 1) % 2;
    f[rt] = (f[rt] + 1) % 2;
    return;
  }
  pushDown(rt);
  int mid = (l + r) / 2;
  if(L <= mid) update(L, R, l, mid, 2 * rt);
  if(R > mid) update(L, R, mid + 1, r, 2 * rt + 1);
  pushUp(rt);
}
 
void query(int L, int R, int l, int r, int rt) {
  if(L <= l && r <= R) {
    for(int i = 0; i < 21; i ++) {
      if(s[rt][p[rt]][i] > n) continue;
      if(abs(i - v) < B) {
        B = abs(i - v);
        ans = s[rt][p[rt]][i];
      } else if(abs(i - v) == B) {
        ans = min(ans, s[rt][p[rt]][i]);
      }
    }
    return;
  }
  pushDown(rt);
  int mid = (l + r) / 2;
  if(L <= mid) query(L, R, l, mid, 2 * rt);
  if(R > mid) query(L, R, mid + 1, r, 2 * rt + 1);
  pushUp(rt);
}
 
int main() {
  init();
  scanf("%d", &T);
  int cas = 1;
  while(T --) {
    printf("Case %d:\n", cas ++);
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i ++) {
      scanf("%d", &a[i]);
      a[i] = cnt[a[i]];
    }
    build(1, n, 1);
    while(q --) {
      int op, l, r;
      scanf("%d%d%d", &op, &l, &r);
      if(op == 1) {
        scanf("%d", &v);
        v = cnt[v];
        B = 100;
        ans = n + 1;
        query(l, r, 1, n, 1);
        printf("%d\n", ans);
      } else {
        update(l, r, 1, n, 1);
      }
    }
  }
  return 0;
}
 
/*
 1
 10 9
 47810 337106 289217 728190 763968 210307 934334 929186 401808 365768
 2 8 10
 1 2 10 611293
 2 2 4
 1 1 8 422298
 2 6 8
 2 2 10
 1 5 6 180197
 2 7 8
 1 4 8 712158
 */