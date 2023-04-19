#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;
const int N = 2e5 + 10;

struct soldier
{
    int first;
    int second;
    int id;
    bool operator<(const soldier &a) const
    {
        return this->first < a.first;
    }
} raw[2 * N];

int n, m, bestgo[2 * N][20], rans[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> raw[i].first >> raw[i].second;
        raw[i].id = i;
        if (raw[i].second < raw[i].first)
            raw[i].second += m;
    }
    sort(raw + 1, raw + 1 + n);
    for (int i = n + 1; i <= 2 * n; ++i)
    {
        raw[i] = raw[i - n];
        raw[i].first += m;
        raw[i].second += m;
    }

    int nxt = 1;
    for (int i = 1; i <= 2 * n; ++i)
    {
        while (nxt <= n * 2 && raw[nxt].first <= raw[i].second)
            ++nxt;
        bestgo[i][0] = nxt - 1;
    }
    for (int p = 1; (1 << p) <= n; ++p)
        for (int i = 1; i <= 2 * n; ++i)
            bestgo[i][p] = bestgo[bestgo[i][p - 1]][p - 1];

    for (int i = 1; i <= n; ++i)
    {
        int cur = i, pos = i, ans = 2;
        int p = log2(n);
        for (p; p >= 0; --p)
        {
            pos = bestgo[cur][p];
            if (pos != 0 && raw[pos].second < raw[i].first + m)
            {
                cur = pos;
                ans += (1 << p);
            }
        }
        rans[raw[i].id] = ans;
    }
    for (int i = 1; i <= n; ++i)
        cout << rans[i] << " ";
    return 0;
}