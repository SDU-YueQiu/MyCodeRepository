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

    int t;
    cin >> t;
    while (t--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (c % 2 == 0)
        {
            if (a > b)
                cout << "First" << endl;
            else
                cout << "Second" << endl;
        } else
        {
            if (a >= b)
                cout << "First" << endl;
            else
                cout << "Second" << endl;
        }
    }

    return 0;
}