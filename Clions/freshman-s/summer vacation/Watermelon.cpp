#include "cmath"
#include "iostream"
#include "map"
#include "queue"
#include "set"
#include "stack"
#include "stdio.h"
#include "vector"

using namespace std;
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
//#define int long long
const int N = 100 + 5;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int w;
    cin >> w;
    if (w % 2)
        cout << "NO" << endl;
    else
    {
        if (w == 2)
            cout << "NO" << endl;
        else
            cout << "YES" << endl;
    }

    return 0;
}