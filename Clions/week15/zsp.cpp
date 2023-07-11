#include "algorithm"
#include <stdio.h>
#include <string.h>
using namespace std;
int dir[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
int M, N, T;
const int MN = 200 + 10, MM = 200 + 10, MT = 10 + 5;
char mg[100][100];
int vis[MN][MM][MT];
int ans;

inline bool inmap(int x, int y)
{
    return x >= 0 && x < M && y >= 0 && y < N;
}

void dfs(int x, int y, int ckl, int step)
{
    if (mg[x][y] == '+')
    {
        if (ans == -1)
            ans = step;
        else
            ans = min(ans, step);
        return;
    }
    for (int i = 0; i < 4; ++i)
    {
        int tx = x + dir[i][0];
        int ty = y + dir[i][1];
        if (inmap(tx, ty))
        {
            int tckl = ckl;
            if (mg[tx][ty] == '#')
                tckl--;
            if (tckl < 0)
                continue;
            if (vis[tx][ty][tckl] > step + 1 || vis[tx][ty][tckl] == 0)
            {
                vis[tx][ty][tckl] = step + 1;
                dfs(tx, ty, tckl, step + 1);
            }
        }
    }
}

int main()
{
    scanf("%d %d %d", &M, &N, &T);
    for (int i = 0; i < M; i++) {
        scanf("%s", mg[i]);
    }

    int a, b;
    memset(vis, 0, sizeof(vis));
    ans = -1;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (mg[i][j] == '@') {
                a = i;
                b = j;
            }
        }
    }
    vis[a][b][T] = -1;
    dfs(a, b, T, 0);
    printf("%d\n", ans);
    return 0;
}