#include "algorithm"
#include "cmath"
#include "map"
#include "set"
#include "vector"
#include <iostream>
#include <ctime>
using namespace std;
//#define int long long
typedef long long ll;
const int N = 1e5 + 10;

signed main()
{
    //    ios::sync_with_stdio(false);
    srand(time(NULL));
    freopen("1.in", "w", stdout);
    int l = rand() % 1000000 + 1, r = l + (rand() % 10000);
    cout << l << ' ' << r;
    return 0;
}
