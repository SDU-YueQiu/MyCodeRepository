#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int M = 2048 + 10;
int n, m, cnt, cishu;
int mn[M], mx[M], flag[M];
vector<int> v;
int hs()
{
    ++cishu;
    if (cishu > 10) return 0;
    for (int i = 1; i <= m; ++i)
        if (flag[i] == 0) return 1;
    return 0;
}
char s[M];
string ss;
void zou(int x, int y)
{
    for (int i = 1; i <= x; ++i) s[++cnt] = 'R';
    for (int i = 1; i <= y; ++i) s[++cnt] = 'D';
    // xxx
    //y
    //y
    //y
}
void check()
{
    s[cnt + 1] = 0;
    ss = s + 1;
    cout << "? " << ss << endl;
    cout.flush();
    int T, x, y;
    cin >> T;
    while (T--)
    {
        cin >> x >> y;
        mn[y] = min(mn[y], x);
        mx[y] = max(mx[y], x);
    }
}
void erfen()
{
    while (hs())//check done
    {
        cnt = 0;
        int l = 1, r = 1, mid;//interesting erfen
        ss = "";
        mx[1] = 1;//天才！！
        for (; l < m; l = r)
        {
            for (r = l + 1; r < m && flag[r] == 0; ++r);
            // 1: r==m
            if (r == l + 1)
            {
                zou(1, mx[r] - mx[l]);
                flag[r] = 1;
                continue;
            }
            mid = (l + r) / 2;
            zou(mid - l, mx[r] - mx[l]);
            zou(r - mid, 0);
            flag[mid] = 1;
        }
        flag[r] = 1;
        check();
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    memset(mn, 0x3f, sizeof(mn));
    cin >> n >> m;
    mn[m + 1] = mx[m + 1] = n;
    flag[1] = 1;
    mn[1] = mx[1] = 1;
    mn[m] = mx[m] = n;//?
    erfen();
    mx[1] = max(mx[1], mn[2]);
    mn[m] = min(mn[m], mx[m - 1]);
    cnt = 0;
    for (int i = 1; i < mx[1]; ++i) s[++cnt] = 'D';
    for (int y = 1; y < m; ++y)
        zou(1, mx[y + 1] - mx[y]);
    ss = s + 1;
    cout << "! " << ss << endl;
    cout.flush();
    return 0;
}