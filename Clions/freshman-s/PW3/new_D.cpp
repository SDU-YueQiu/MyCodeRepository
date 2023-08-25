#include "algorithm"
#include "cmath"
#include "cstring"
#include "map"
#include "set"
#include "string"
#include "vector"
#include <iostream>

using namespace std;
const int N = 1e3 + 10;
//#define int long long
typedef pair<int, int> pii;
//#define endl '/n'

int m, n;
string s;
int mn[N], mx[N];
bool done[N];

void print(int d1, int r, int d2)
{
    while (d1--)
        cout << 'D';
    while (r--)
        cout << 'R';
    while (d2--)
        cout << 'D';
}

bool check()
{
    for (int i = 1; i <= m; ++i)
        if (!done[i])
            return true;
    return false;
}

void up()
{
    cout << endl;
    //cout << "? " << s << endl;
    int t;
    cin >> t;
    int x, y;
    while (t--)
    {
        cin >> x >> y;
        mx[x] = max(mx[x], y);
        mn[x] = min(mn[x], y);
    }
}

void qurry()
{
    while (check())
    {
        cout << "? ";
        s.clear();
        int l = 1, r = 2;
        mx[1] = 1;
        for (l; l < m; l = r)//=?
        {
            r = l + 1;
            while (r < m && !done[r]) ++r;
            if (r == l + 1)
            {
                print(1, mx[r] - mx[l], 0);//?
                done[r] = true;
                continue;
            }
            int mid = (l + r) / 2;
            print(mid - l, mx[r] - mx[l], r - mid);
            done[mid] = true;
        }
        //done[m] = 1;
        up();
    }
}

void printAns()
{
    cout << "! ";
    for (int i = 1; i <= m; ++i)
    {
        for (int j = mx[i] - mn[i]; j > 0; --j)
            cout << 'R';
        if (i < m)
            cout << 'D';
    }
    cout << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    memset(mn, 0x3f, sizeof(mn));
    cin >> m >> n;
    mn[1] = mx[1] = 1;
    mx[m] = mn[m] = n;
    mn[m + 1] = mx[m + 1] = n;
    done[1] = true;
    qurry();
    mx[1] = max(mx[1], mn[2]);
    mn[m] = min(mn[m], mx[m - 1]);
    if (mn[m] == 0)
        mn[m] = 1;
    printAns();
    return 0;
}
