#include <cmath>
#include <cstdio>

using namespace std;

const int N = 1e6 + 1;

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

void swap(int &x, int &y) {
	x += y;
	y = x - y;
	x -= y;
	return;
}

int n,m,lg;

int fa[25][N],dep[N];

int lca(int u,int v)
{
	if(dep[u] < dep[v]) swap(u, v);
	for(int i = lg; i >= 0; --i)
		if(dep[fa[i][u]] >= dep[v])
			u = fa[i][u];
	if(u == v) return u;
	for(int i = lg; i >= 0; --i)
		if(fa[i][u] != fa[i][v])
			u = fa[i][u], v = fa[i][v];
	return fa[0][u];
}

int main() {
	read(n), read(m);
	lg = log2(n);
	for(int i = 1; i <= n; ++i) {
		read(fa[0][i]);
		fa[0][i] += i;
		if(fa[0][i] > n) fa[0][i] = n + 1;
	}
	dep[n + 1] = 1;
	for(int i = n;i >= 1; --i) {
		dep[i] = dep[fa[0][i]] + 1;
		for(int j = 1; j <= lg; ++j)
			fa[j][i] = fa[j - 1][fa[j - 1][i]];
	}
	while(m--) {
		int p1, p2, ans;
		read(p1), read(p2);
        ans = lca(p1, p2);
		printf("%d\n", ans <= n ? ans : -1);
	}
	return 0;
}
