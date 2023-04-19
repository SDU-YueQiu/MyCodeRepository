#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;
const int MAXN = 1e5 + 10;
const int INF = 0x3f3f3f3f;
typedef long long ll;
typedef pair<int, int> pii;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        ll k, x;
        cin >> k >> x;
        ll n = 1;
        ll sum = 0;
        while (sum < x && n <= 2 * k - 1)
        {
            sum += (n > k) ? 2*k - n : n;
            n++;
        }
        cout << n - 1 << endl;
    }
    return 0;
}