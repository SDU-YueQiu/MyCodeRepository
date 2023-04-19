#include "stdio.h"
#include "stdlib.h"

int N;
int sum;

inline int fa(int x) { return x / 2; }
bool find(int *arr, int x)
{
    for (int i = 1; i <= x; ++i)
    {
        if (arr[i] == x)
            return true;
    }
    return false;
}

void dfs(int n, int m, int *arr)
{
    if (m == N + 1)
    {
        ++sum;
        for (int i = 1; i <= N; ++i)
            printf("%d ", arr[i]);
        printf("\n");
        return;
    }
    for (int i = n + 1; i <= n * 2 + 1; ++i) // 从右边第一个节点开始到右子节点为止，右子节点往后的节点的父节点一定不在arr中，不考虑
    {
        if (find(arr, fa(i)))
        {
            arr[m] = i;
            dfs(i, m + 1, arr);
        }
    }
}

int main()
{
    scanf("%d", &N);
    int *arr = (int *)malloc((N + 1) * sizeof(int));
    arr[1] = 1;
    dfs(1, 2, arr);
    free(arr);
    printf("tree_count is %d when N is %d", sum, N);
    return 0;
}