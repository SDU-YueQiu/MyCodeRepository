//WA???
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

using namespace std;
const long long MAXN = 2e5 + 10;
typedef long long ll;
const long long INF = 1e13;

long long sumh[MAXN];
pair<long long, long long> airs[MAXN];
long long n, h;

long long findh(long long num)
{
    long long l = num, r = n;
    long long th = h + sumh[num];
    while (l < r)
    {
        long long mid = l + (r - l + 1) / 2;
        if (sumh[mid] <= th)
            l = mid;
        else
            r = mid - 1;
    }
    if (th == sumh[l])
        return airs[l].first - airs[num].first;
    return airs[l].second + th - sumh[l] - airs[num].first;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> h;
    cin >> airs[0].first >> airs[0].second;
    for (long long i = 1; i < n; ++i)
    {
        cin >> airs[i].first >> airs[i].second;
        sumh[i] = sumh[i - 1] + airs[i].first - airs[i - 1].second;
    }
    sumh[n] = INF;
    long long maxans = 0;
    for (long long i = 0; i < n; ++i)
        maxans = max(maxans, findh(i));
    cout << maxans;
    return 0;
}