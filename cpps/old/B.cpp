#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 1e5 + 10;
typedef pair<int, int> pii;

vector<int> s;
vector<int> cti[200];
char itc[200];
int numOfch = 0;

void add(char c)
{
    if (cti[c].size() == 0)
    {
        cti[c].push_back(++numOfch);
        itc[numOfch] = c;
    }
    s.push_back(cti[c][0]);
}
void del(char c)
{
    if (!s.empty())
        s.pop_back();
}
void chg(char a, char b)
{
    for (int i = 0; i < cti[a].size(); ++i)
    {
        itc[cti[a][i]] = b;
        cti[b].push_back(cti[a][i]);
    }
    cti[a].clear();
}
void print()
{
    if (s.empty())
    {
        cout << "The final string is empty";
        return;
    }
    for (int i = 0; i < s.size(); ++i)
        putchar(itc[s[i]]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int q;
    cin >> q;
    while (q--)
    {
        int o;
        cin >> o;
        switch (o)
        {
        case 1:
            char c;
            cin >> c;
            add(c);
            break;
        case 2:
            del(c);
            break;
        case 3:
        {
            char c;
            cin >> c;
            char d;
            cin >> d;
            chg(c, d);
        }
        break;
        }
    }
    print();
    return 0;
}