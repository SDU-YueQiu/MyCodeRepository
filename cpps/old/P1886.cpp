#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <cmath>

using namespace std;
typedef long long ll;
const int MAXN = 1e6 + 10;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;

deque<pair<int, int>> maxq;
deque<pair<int, int>> minq;
vector<pair<int, int>> maxans;

int main()
{
    int a=10;
    int *b(&a);
    cout<<b<<endl;
    return 0;
}