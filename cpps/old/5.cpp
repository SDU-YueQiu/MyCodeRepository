//https://codeforces.com/gym/101911/problem/F
#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<cstring>
using namespace std;
#define int long long
const int maxn = 1e6 + 10;
int pre[maxn][28];
void init()
{
	pre[0][0] = 1;
	for (int i = 1; i < 1e6; i++)
	{
		int len = 0;
		int x = i;
		int cnt1 = 0, cnt2 = 0;
		while (x)
		{
			len++;
			if (len > 3)
			{
				cnt1 += x % 10;
			}
			else
				cnt2 += x % 10;
			x /= 10;
		}
		pre[i][abs(cnt2 - cnt1)]=pre[i-1][abs(cnt2-cnt1)]+1;
		for (int j = 0; j <= 27; j++)
		{
			if (j != abs(cnt2 - cnt1))
			{
				pre[i][j] = pre[i - 1][j];
			}
		}
	}
}
void solve()
{
	string s;
	cin >> s;
	int ans = 0;
	for (int i = 0; i <= 5; i++)
	{
		ans = ans * 10 + s[i] - '0';
	}
	int x = ans;
	int len = 0;
	int cnt1 = 0, cnt2 = 0;
	while (x)
	{
		len++;
		if (len > 3)
		{
			cnt1 += x % 10;
		}
		else
			cnt2 += x % 10;
		x /= 10;
	}
	int anss = 0;
	for (int j = abs(cnt1 - cnt2)-1; j>=0; j--)
	{
		anss += pre[ans-1][j];
	}
	cout << anss << endl;


}
signed main()
{
	init();
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();

}