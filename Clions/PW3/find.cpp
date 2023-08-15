#include "algorithm"
#include "cmath"
#include "map"
#include "set"
#include "vector"
#include <iostream>

using namespace std;
//#define int long long
typedef long long ll;
const int N = 1e5 + 10;

signed main()
{
    //    ios::sync_with_stdio(false);
    int sum = 0;
    for (int i = 1; i <= 20; i++)
    {
        sum += i * i * i;
        cout << sum << endl;
    }
    return 0;
}
