#include "stdio.h"
#include "stdlib.h"

int N;
int sum;

void dfs(int n, int m, bool *vis)
{
    if (m == 0)
    {
        ++sum;
        for (int i = 1; i <= (1 << N); ++i)
        {
            if (vis[i])
                printf("%d ", i);
        }
        printf("\n");
        return;
    }
    for (int i = n + 1; i <= n * 2 + 1; ++i)
    {
        if (vis[i >> 1])
        {
            vis[i] = 1;
            dfs(i, m - 1, vis);
            vis[i] = 0;
        }
    }
}

int main()
{
    scanf("%d", &N);
    bool *vis=(bool*)malloc((1<<N)*sizeof(bool));
    for(int i=1;i<(1<<N);++i)
        vis[i]=0;
    vis[1] = 1;
    dfs(1, N - 1, vis);
    free(vis);
    printf("tree_count is %d when N is %d",sum,N);
    return 0;
}