#include "algorithm"
#include "cmath"
#include "cstdio"
#include "iostream"
#include "map"
#include "set"
#include "string"
#include "vector"

using namespace std;
#define endl '\n'
//#define int long long
const int N = 5e3 + 10;
typedef long long ll;
typedef pair<int, int> pii;

bool win[N];

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    int cnt = 0;
    win[++cnt] = true;
    int cntnum = 2;
    while (cnt < n)
    {
        for (int i = 1; i <= cntnum; ++i)
            win[++cnt] = false;
        for (int i = 1; i <= cntnum; ++i)
            win[++cnt] = true;
        ++cntnum;
    }
    cout << (win[n] ? "Jane" : "John");
    return 0;
}