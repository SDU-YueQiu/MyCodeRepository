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
const int N = 1e5 + 10;
const double eps = 1e-8;
typedef pair<int, int> pii;

struct vecs {
    int x1, y1;
    int x2, y2;
} vec[N];

bool cmp(vecs &a, vecs &b)
{
    return a.x2 < b.x2;
}

int mmap[N];
int sum[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> vec[i].x1 >> vec[i].y1 >> vec[i].x2 >> vec[i].y2;
        mmap[vec[i].x1]++;
        mmap[vec[i].x2]--;
    }

    sum[0] = mmap[0];
    for (int i = 1; i < N; ++i)
    {
        sum[i] = sum[i - 1] + mmap[i];
    }
    int ans = 0;
    for (int i = 0; i < N; ++i)
        if (sum[i])
            ans++;
    cout << ans;
    return 0;
}
