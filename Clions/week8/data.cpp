#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <time.h>
#include <vector>

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
    srand(time(NULL));
    ll t = rand() % 10 + 1, m = rand() % 10 + 1;
    printf("%d %d\n", t, m);
    while (m--)
    {
        ll o, x, y, z;
        o = rand() % 4 + 1;
        if (o <= 3)
        {
            x = rand() % t + 1;
            y = rand() % t + 1;
            if (x > y) swap(x, y);
            z = rand() * rand() % 10000;
            printf("%d %d %d %d\n", o, x, y, z);
        } else
        {
            x = rand() % t + 1;
            y = rand() % t + 1;
            if (x > y) swap(x, y);
            z = rand() % 3 + 1;
            printf("%d %d %d %d\n", o, x, y, z);
        }
    }
    printf("0 0");
    return 0;
}