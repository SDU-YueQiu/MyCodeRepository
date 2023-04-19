#include "algorithm"
#include "cstdio"
#include "map"
#include "math.h"
#include "queue"
#include "set"
#include "stack"
#include "tuple"
#include <iostream>

using namespace std;
//#define int long long
#define endl '\n'
typedef long long ll;
const int N = 1e6 + 10;
const double eps = 1e-8;
typedef pair<int, int> pii;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T[100][100]={{}};
    int row=1;
    int K = 2, p = 1, L = 0;
    int l = 1, r = K + 1;
    int tofind = p - L;
    while (l < r)
    {
        int mmid = (l + r) >> 1;
        if (T[row][mmid] >= tofind)
            r = mmid;
        else
            l = mmid + 1;
    }
    return 0;
}
