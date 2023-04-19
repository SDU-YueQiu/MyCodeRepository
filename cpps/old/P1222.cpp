#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
typedef long long ll;
const int MAXN = 10;

bool mmap[MAXN][MAXN];
bool ans[MAXN][MAXN];
bool tans[MAXN][MAXN];

void input()
{
    memset(ans, 0, sizeof(ans));
    for (int i = 1; i <= 5; ++i)
        for (int j = 1; j <= 6; ++j)
        {
            bool b;
            cin >> b;
            mmap[i][j] = b;
        }
    return;
}

void changemn(int m, int n)
{
    int cgx[5] = {0, 1, 0, -1, 0};
    int cgy[5] = {0, 0, 1, 0, -1};
    for (int i = 0; i < 5; ++i)
        mmap[m + cgx[i]][n + cgy[i]] = !mmap[m + cgx[i]][n + cgy[i]];
    return;
}

//dfs可以使用位运算优化掉递归开销，不过常数级优化必要性不大
//但位运算枚举可以提高可读性，比递归枚举更容易理解
bool dfs(int dpt, bool isp)
{
    if (isp)
    {
        changemn(1, dpt);
        ans[1][dpt] = true;
    }

    if (dpt == 6)
    {
        memset(tans, 0, sizeof(tans));
        for (int j = 2; j <= 5; ++j)
        {
            for (int k = 1; k <= 6; ++k)
            {
                if (mmap[j - 1][k])
                {
                    changemn(j, k);
                    tans[j][k] = true;
                }
            }
        }
        for (int i = 1; i <= 6; ++i)
            if (mmap[5][i])
            {
                //可以用pair+vector进一步优化复杂度到o(t) t为按下的开关数
                for (int j = 2; j <= 5; ++j)
                    for (int k = 1; k <= 6; ++k)
                        if (tans[j][k])
                            changemn(j, k);
                if (isp)
                {
                    changemn(1, dpt);
                    ans[1][dpt] = false;
                }
                return false;
            }
        for (int i = 2; i <= 5; ++i)
            for (int j = 1; j <= 6; ++j)
                ans[i][j] = tans[i][j];
        return true;
    }

    if (dfs(dpt + 1, 0))
        return true;
    if (dfs(dpt + 1, 1))
        return true;

    if (isp)
    {
        changemn(1, dpt);
        ans[1][dpt] = false;
    }

    return false;
}

void printans(int n)
{
    cout << "PUZZLE #" << n << "\n";
    for (int i = 1; i <= 5; ++i)
    {
        for (int j = 1; j <= 6; ++j)
            cout << ans[i][j] << " ";
        cout << "\n";
    }
    return;
}

int main()
{
    int n;
    cin >> n;
    int cnt = 1;
    while (n--)
    {
        input();
        dfs(0, 0);
        printans(cnt++);
    }
    return 0;
}