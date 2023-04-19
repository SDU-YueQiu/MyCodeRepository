#include<iostream>
#include<algorithm>
#include<map>
using namespace std;
#define int long long
const int maxn = 1e5 + 10;
struct node
{
	int l, r;
}e[maxn];
map<pair<int, int>, int>mp;
pair<int, int>ans[maxn];
bool vis[maxn];
struct node1
{
	int val, num;
	inline bool operator<(const node1&cf)const
	{
		return val < cf.val;
	}
}a[maxn];
signed main()
{
	int n;
	cin >> n;
	for (int i = 1; i < n; i++) {
		cin >> e[i].l >> e[i].r;
		if (e[i].l > e[i].r)
			swap(e[i].l, e[i].r);
		mp[{e[i].l, e[i].r}]++;
		if ((e[i].r != n && e[i].l != n) || (e[i].l == e[i].r))
		{
			cout << "NO" << endl;
			return 0;
		}
	}
	int cnt = 0;
	int cnm = 0;
	for (int i = 1; i < n; i++)
	{
		if (mp[{e[i].l, e[i].r}] == 1)
		{
			ans[++cnt].first = e[i].l, ans[cnt].second = e[i].r;
			vis[e[i].l] = 1, vis[e[i].r] = 1;
		}
		else
		{
			if (mp[{e[i].l, e[i].r}] != 0) {
				a[++cnm].val = min(e[i].l, e[i].r);
				a[cnm].num = mp[{e[i].l, e[i].r}];
				mp[{e[i].l, e[i].r}] = 0;
			}
		}
	}
	sort(a + 1, a + 1 + cnm);
	int l = 1;
	for (int i = 1; i <= cnm; i++)
	{
		int per = n;
		int num1 = 0;
		while (num1 < a[i].num)
		{
			num1++;
			if (num1 != a[i].num) {
				while (vis[l] && l < n)
				{
					l++;
				}
				if (l < a[i].val&&num1 != a[i].num)
				{
					ans[++cnt].first = per, ans[cnt].second = l;
					per = l;
					vis[l] = 1;
				}
				else if (l >= a[i].val)
				{
					cout << "NO";
					return 0;
				}
			}
			else
			{
				ans[++cnt].first = per, ans[cnt].second = a[i].val;
				vis[a[i].val] = 1;
				break;
			}
		}
	}
	cout << "YES" << endl;
	for (int i = 1; i <= n - 1; i++)
	{
		cout << ans[i].first << ' ' << ans[i].second << endl;
	}


}