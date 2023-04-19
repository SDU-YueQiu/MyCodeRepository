//https://codeforces.com/gym/101911/problem/B
#include<iostream>
#include<algorithm>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;
int n, h;
struct node
{
  int l, r;
  inline bool operator<(const node&cf)const
  {
    return l < cf.l;
    }
}a[maxn];
int pre[maxn];//前缀下降距离
signed main()
{
  cin >> n >> h;
  for (int i = 1; i <= n; i++)
  {
    cin >> a[i].l >> a[i].r;
  }
  sort(a + 1, a + 1 + n);
  for (int i = 2; i <= n; i++)
  {
    pre[i] = pre[i - 1] + (a[i].l - a[i-1].r);
  }
  n++;
  pre[n] = 1e18;
  int ans = 0;
  for (int i = 1; i <= n-1; i++)
  {
    int now = pre[i];
    int p = lower_bound(pre + 1, pre + 1 + n, pre[i] + h) - pre;
    if (pre[p]>=pre[i] + h)
    {
      p--;
    }
    ans = max(ans, a[p].r - a[i].l + (h -(pre[p]-pre[i])));
  }
  cout << ans;
}