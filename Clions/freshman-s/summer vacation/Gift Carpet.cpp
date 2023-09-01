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
const int N = 1e6 + 10;
typedef pair<int, int> pii;
const double eps = 1e-6;

char a[25][25];

signed main()
{
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        char c;
        char s[5] = "vika";
        int cnt = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> a[i][j];
        int nowcnt = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (a[j][i] == s[cnt])
                    cnt = nowcnt + 1;
            }
            nowcnt = cnt;
        }
        if (cnt == 4)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}