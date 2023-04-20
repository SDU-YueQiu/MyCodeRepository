#include "stdio.h"

int main()
{
    int grades[3][4];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            scanf("%d", &grades[i][j]);
    int maxid[4];
    for (int i = 0; i < 4; i++)
    {
        int max = 0;
        for (int j = 0; j < 3; j++)
        {
            if (grades[j][i] > max)
            {
                max = grades[j][i];
                maxid[i] = j;
            }
        }
    }
    for (int i = 0; i < 4; i++)
        printf("%d ", maxid[i] + 1);
    return 0;
}