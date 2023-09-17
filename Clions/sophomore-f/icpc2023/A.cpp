#include "deque"
#include "map"
#include "queue"
#include "set"
#include "string"
#include "vector"
#include <algorithm>
#include <iostream>

using namespace std;
#define endl '\n'
//#define int long long
typedef long long ll;
const int N = 1e6 + 10;
typedef pair<int, int> pii;
const int INF = 0x7f7f7f7f;

struct uni {
    string name;
    int rk1 = INF, rk2 = INF;
    bool operator<(const uni &b) const
    {
        int brk = min(rk1, rk2);
        int bbrk = min(b.rk1, b.rk2);
        if (brk == bbrk)
            return rk1 < rk2;
        return brk < bbrk;
    }
};

map<string, int> rk;
map<string, int> rk2;
map<string, int> id;
vector<uni> univ;

signed main()
{
    int n, m;
    cin >> n >> m;
    string t;
    for (int i = 0; i < n; ++i)
    {
        cin >> t;
        if (rk.find(t) == rk.end())
        {
            rk[t] = univ.size() + 1;
            univ.push_back({t, rk[t], INF});
            id[t] = univ.size() - 1;
        }
    }
    int cnt2 = 0;
    for (int i = 0; i < m; ++i)
    {
        cin >> t;
        if (rk2.find(t) == rk2.end())
        {
            if (id.find(t) != id.end() && univ[id[t]].rk2 == INF)
                univ[id[t]].rk2 = ++cnt2;
            else if (id.find(t) == id.end())
            {
                univ.push_back({t, INF, ++cnt2});
                id[t] = univ.size() - 1;
            }
        }
    }
    sort(univ.begin(), univ.end());
    for (auto x: univ)
        cout << x.name << endl;
    return 0;
}
