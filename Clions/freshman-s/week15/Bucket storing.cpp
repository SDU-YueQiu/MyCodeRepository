#include "algorithm"
#include "cmath"
#include "cstdio"
#include "iostream"
#include "map"
#include "set"
#include "vector"

using namespace std;
#define endl '\n'
//#define int long long
const int N = 1e6 + 10;
typedef long long ll;
typedef pair<int, int> pii;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, k, l;
    cin >> n >> k >> l;
    int sum = n * k;
    int suml = sum / l + (sum % l == 0 ? 0 : 1);
    cout << suml;
    return 0;
}