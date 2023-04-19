//101353F
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
using namespace std;
#define int long long
const int inf = 1e18;
const int maxn = 1e5 + 10;
int a[maxn];
int n, k;
bool check(int x)
{
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] >x)
			sum += x;
		else
			sum += a[i];
	}
	if (x == 0)
	{
		return 1;
	}
	return ((sum / x) >= k);
}
int T = 0;
void solve()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	int l = 1, r = inf;
	int ans = 0;
	while (l <= r)
	{
		int mid = (l + r) >> 1;
		if (check(mid))
		{
			ans = mid;
			l = mid + 1;
		}
		else
			r = mid - 1;
	}
	cout << "Case " << ++T << ": ";
	cout << ans << endl;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
}