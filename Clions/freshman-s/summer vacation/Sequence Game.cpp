#include "algorithm"
#include "cmath"
#include "cstring"
#include "iomanip"
#include "iostream"
#include "map"
#include "queue"
#include "set"
#include "string"
#include "vector"

using namespace std;
//#define int long long
#define endl '\n'
typedef long long ll;
const int N = 2e5 + 10;
typedef pair<int, int> pii;
const double eps = 1e-6;

int a[N];
bool flag[N];

signed main()
{
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--)
    {
        int m;
        cin >> m;
        int n = 0;
        fill(flag, flag + m + 1, false);
        for (int i = 0; i < m; i++)
            cin >> a[i];
        for (int i = 1; i < m; ++i) {
            if (a[i] < a[i - 1])
            {
                ++n;
                flag[i] = true;
            }
        }
        cout << m + n << endl;
        for (int i = 0; i < m; ++i) {
            if (flag[i])
                cout << ((a[i] - 1 == 0) ? 1 : (a[i] - 1)) << " ";
            cout << a[i] << " ";
        }
        cout << endl;
    }

    return 0;
}