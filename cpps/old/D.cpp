#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 5e4 + 10;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> pii;

int p;
int ri[55];
int dp[MAXN];
bool done[MAXN];

int dfs(int x)
{
    if (x <= 0)
        return -x;
    if (done[x])
        return dp[x];
    done[x]=1;
    dp[x] = INF;
    for (int i = 0; i < p; ++i)
        dp[x] = min(dp[x], dfs(x - ri[i]));
    return dp[x];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int k;
    cin >> k >> p;
    for (int i = 0; i < p; ++i)
        cin >> ri[i];
    while (k--)
    {
        int x;
        cin >> x;
        cout<<dfs(x)<<"\n";
    }
    return 0;
}