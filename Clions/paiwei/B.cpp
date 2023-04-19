#include <iostream>
#include "cstdio"
#include "math.h"
#include "tuple"
#include "queue"
#include "map"
#include "stack"
#include "algorithm"
#include "set"

using namespace std;
//#define int long long
#define endl '\n'
typedef long long ll;
const int N=1e6+10;
const double eps=1e-8;
#define MAXN 2000000

typedef pair<int,int> pii;

int a[MAXN], s[MAXN], p[MAXN], w[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n = read();
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
        p[i] = p[i - 1] + i * a[i];
        w[i] = s[i] * i;
        w[i] -= p[i];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, p[i]);

    }
    cout << ans;
    return 0;
}


//选j不选k: w[j] - w[k] + s[i] * (k - j) >= 0
