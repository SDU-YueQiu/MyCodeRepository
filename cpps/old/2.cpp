#include <cstdio>
#include <cstring>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1000000;
struct node
{
    int x;
    int y;
    int z;
    int id;
} s[maxn];
bool cmp1(node a, node b)
{
    return a.x < b.x;
}
bool cmp(node a, node b)
{
    return a.id < b.id;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i].x;
        s[i].id = i;
    }
    sort(s, s + n, cmp1);
    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        int r = i;
        int l = i;
        int k = s[i].x;
        while (s[i].x == s[r + 1].x)
        {
            r++;
        }
        i = r;
        for (int j = 1; j * j <= k; j++)
        {
            if (k % j == 0)
            {
                s[l].y = j;
                s[l].z = k / j;
                l++;
                if (l > r)
                    break;
                if (j == k / j)
                    break;
                s[l].y = k / j;
                s[l].z = j;
                l++; // 成对的话就是两因子交换
                if (l > r)
                    break;
            }
        }
        if (l <= r)
        {
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        cout << "NO" << endl;
    }
    else
    {
        cout << "YES" << endl;
        sort(s, s + n, cmp);
        for (int i = 0; i < n; i++)
        {
            cout << s[i].y << " " << s[i].z << endl;
        }
    }
}
