#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
#define int long long
const int maxn = 5e5 + 10;
int f[23][maxn];
int a[maxn], n, m, q;
int b[maxn];
int c[maxn];
int stack[maxn];
void st()
{
	for (int i = 1; i <= n; i++)
		f[0][i] = a[i];
	int k = log2(n);
	for (int j = 1; j <= k; j++)
		for (int i = 1; i <= n - (1 << j) + 1; i++)
			f[j][i] = max(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);

}
int find_max(int l, int r)
{
	int k = log2(r - l + 1);
	return max(f[k][l], f[k][r - (1 << k) + 1]);
}
int nex[maxn], pre[maxn];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	st();
	cin >> q;
	while (q--)
	{
		int m;
		cin >> m;
		int ans = 0;
		int cnt=0;
		for (int i = 1; i <= m; i++)
		{
			cin >> c[i];
			ans += a[c[i]];
			if (i > 1)
			{
				b[++cnt] = find_max(c[i - 1], c[i]);
		//		cout << b[cnt] << ' ';
			}
		}
		//cout << endl;
		int top = 0;
		for (int i = 1; i <= cnt; i++) {
			while (top && (b[stack[top]] <= b[i])) {
				nex[stack[top]] = i;
				top--;
			}
			stack[++top] = i;
		}
		while (top)
			nex[stack[top--]] = cnt + 1;
		top = 0;
		for (int i = cnt; i >=1; i--) {
			while (top && (b[stack[top]] < b[i])) {
				pre[stack[top]] = i;
				top--;
			}
			stack[++top] = i;
		}
		while (top)
			pre[stack[top--]]=0;
		
		for (int i = 1; i <= cnt; i++)
		{
			//cout << i << ' ' << pre[i] << ' ' << nex[i] << ' ' << b[i] << endl;
			ans += (i - pre[i])*(nex[i] - i)*b[i];
		}
		cout << ans << '\n';

	}
}