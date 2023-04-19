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
const int MAXN = 100 + 10;
typedef pair<int, int> pii;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    char s[MAXN];
    char he[10] = "hello";
    cin >> s;
    int p = 0, ph = 0;
    int len = strlen(s);
    while (p < len && ph < 5)
    {
        if (s[p] == he[ph])
        {
            ph++;
            p++;
        }
        else
            p++;
    }
    if (ph == 5)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}