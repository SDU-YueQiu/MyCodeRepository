#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <algorithm>
#include <time.h>

using namespace std;
const int MAXN = 1e5 + 10;
const int INF = 0x3f3f3f3f;
typedef long long ll;
typedef pair<int, int> pii;
#define int long long

signed main()
{
    srand(time(NULL));
    int t = rand() % 3 + 1;
    cout << t << endl;
    while (t--)
    {
        int N = rand()%20+1, M = rand()%10000+1, K = rand()%100+1, T = rand()%600+1;
        cout << N << " " << M << " " << K << " " << T << endl;
        cout << rand() % 200 + 1 << " " << rand() % 200 + 1 << " " << rand() % 200 + 1 << " " << rand() % 200 + 1 << " " << rand() % 200 + 1 << endl;
        cout << rand() % 200 + 1 << " " << rand() % 200 + 1 << " " << rand() % 200 + 1 << " " << rand() % 200 + 1 << " " << rand() % 200 + 1 << endl;
    }
    return 0;
}