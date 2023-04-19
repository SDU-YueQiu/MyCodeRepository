//https://codeforces.com/gym/103389/problem/F
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define int long long
const int maxn = 2e3 + 10;
const int base = 27;
const int mod = 998244353;
int p[maxn];
char s[maxn][maxn];
int hash_h[maxn][maxn],hash_l[maxn][maxn];
int fail[maxn];
int n, m;//n为地图大小，m为询问次数
int a[maxn];
int kmp(int len)
{
	int j = 0;
	fail[0] = -1;
	for (int i = 2; i <= len; i++)
	{
		while (j != -1 && a[j + 1] != a[i])j = fail[j];
		fail[i] = ++j;
	}
	return len - fail[len];
}
signed main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> (s[i] + 1);
	p[0] = 1;
	for (int i = 1; i <= n; i++)
		p[i] = (p[i - 1] * base) % mod;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			hash_h[i][j] = (hash_h[i][j - 1] * base + (s[i][j] - 'a'+1))%mod;
			hash_l[i][j] = (hash_l[i - 1][j] * base + (s[i][j] - 'a' + 1)) % mod;
		}
   }
	for (int i = 1; i <= m; i++)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		int cnt = 0;
		memset(a, 0, sizeof a);
		for (int i = x1; i <= x2; i++)
		{
			a[++cnt] = (hash_h[i][y2] - hash_h[i][y1 - 1] * p[y2 - y1 + 1] % mod + mod) % mod;
		}
		int x = kmp(cnt);
		cnt = 0;
		memset(a, 0, sizeof a);
		for (int i = y1; i <= y2; i++)
		{
			a[++cnt] = (hash_l[x2][i] - hash_l[x1 - 1][i] * p[x2 - x1 + 1] % mod + mod) % mod;
		}
		int y = kmp(cnt);
		cout << x * y << endl;

	}
}