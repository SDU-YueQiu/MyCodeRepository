#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <cstring>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 1e5 + 10;
typedef pair<int, int> pii;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    cout << n << " ";
    while (n > 1)
    {
        for (int i = 2; i <= n; ++i)
        {
            if (n % i == 0)
            {
                n = n / i;
                break;
            }
        }
        cout << n << " ";
    }
    return 0;
}