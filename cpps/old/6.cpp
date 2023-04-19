//101353C
#include<iostream>
#include<cmath>
#include<algorithm>
#include<string>
#include<cmath>
#include<vector>
#include<cstring>
#include<map>
using namespace std;
#define int long long
#define double long double
const unsigned long long mod = 1e9 + 1;
const int maxn = 1e5 + 10;
int n, m;
map<int,int>mp1;
map<int, int>mp2;
int T;
int gcd(int a, int b)
{
	if (a%b == 0)
		return b;
	else
		return gcd(b, a%b);
}
void init(int x){
	int tmp = x;
	for (int i = 2; i * i <= tmp; i++) 
	{
	int cnt = 0;
	while (tmp % i == 0) {
		tmp /= i;
		cnt++;
	}
	if (cnt) {	
		if (mp1.count(i) == 0)
		{
			mp1[i]=cnt;
	    }
		else
		{
			int now1 = mp1[i];
			int now2 = mp2[i];
			if (cnt > now1)
			{
				mp1[i] = cnt;
				mp2[i] = now1;
			}
			else if (cnt > now2)
			{
				mp1[i] = now1;
				mp2[i] = cnt;
			}
		}
	}
    }
if (tmp > 1) {  // 自己是质数的情况
	int i = tmp;
	int cnt = 1;
	if (mp1.count(i) == 0)
	{
		mp1[i] = 1;
	}
	else if (mp2.count(i) == 0)
	{
		mp2[i] = cnt;
	}
	else
	{
		int now1 = mp1[i];
		int now2 = mp2[i];
		if (cnt > now1)
		{
			mp1[i] = cnt;
			mp2[i] = now1;
		}
		else if (cnt > now2)
		{
			mp1[i] = now1;
			mp2[i] = cnt;
		}
	}
}
}
int qpow(int a, int b)
{
	int res = 1;
	while(b)
	{
		if (b & 1)
		{
			res = res * a%mod;
		}
		a = a * a%mod;
		b >>= 1;
	}
	return res;
}
unsigned long long a[4];
void solve()
{
	int n;
	cin >> n;
	if (n == 1)
	{
		unsigned long long x;
		cin >> x;
		cout << x % mod;
		return;
	}
	if (n <= 3)
	{
		for (int i = 1; i <= 3; i++)
		{
			cin >> a[i];
		}
		if (n == 3)
		{
			int gg = gcd(gcd(a[1], a[2]),a[3]);
			for (int i = 1; i <= 3; i++)
				a[i] /= gg;
			gg = gcd(a[1], a[2]);
			a[1] /= gg, a[2] /= gg;
			gg = gcd(a[1], a[3]);
			a[1] /= gg;
			a[3] /= gg;
			gg = gcd(a[2], a[3]);
			a[2] /= gg;
			a[3] /= gg;
			cout << (a[1] * a[2])%mod * a[3]%mod << endl;
		}
		else
		{
			int gg = gcd(a[1], a[2]);
			cout << (a[1] / gg * (a[2] / gg) % mod) % mod << endl;
		}
		return;
    }
	else
	{
		for (int i = 1; i <= n; i++)
		{
			int x;
			cin >> x;
			init(x);
		}
		int ans = 1;
		for (auto x : mp1)
		{
			//cout << x.first << ' ' << x.second << ' ' << mp2[x.first] << endl;
			if (mp2.count(x.first) == 0)
			{
				ans *= qpow(x.first,x.second);
				ans %= mod;
			}
			else
			{
				ans *= qpow(x.first, x.second-mp2[x.first]);
				ans %= mod;
			}
		}
		cout << ans;
	}
}
signed main()
{
	//T = 0;
	int t=1;
	//cin >> t;
	while (t--)
		solve();
}