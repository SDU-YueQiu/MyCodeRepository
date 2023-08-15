#include "algorithm"
#include "cmath"
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
    while (d1--) s += 'D';
    while (r--) s += 'R';
    while (d2--) s += 'D';
}

bool check()
{
    for (int i = 1; i <= m; ++i)
        if (!done[i])
            return true;
    return false;
}

void qurry()
{
    while (check())
    {
        s.clear();
        int l=1,r=2;
        for(l;l<m;)
    }
}

void printAns()
{
    cout<<'!';
    for (int i = 1; i <= m; ++i)
    {
        for (int j = mx[i] - mn[i]; j > 0; --j)
            cout << 'R';
        cout << 'D';
    }
    cout<<endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin >> m >> n;
    mn[1] = mn[1] = 1;
    mx[m] = mx[1] = n;

    return 0;
}
