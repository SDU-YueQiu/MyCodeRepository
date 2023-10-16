#include <iostream>
#include <math.h>
using namespace std;
int jiecheng(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return n * jiecheng(n - 1);
}
int main()
{
    int n, x = 0;
    cin >> n;
    int ori[n];
    for (int i = 0; i < n; i++)
    {
        cin >> ori[i];
    }
    int length = jiecheng(n);
    int result[length];
    int judge = 1;
    int mid[n];
    long long int stop = n * pow(10, n - 1);
    for (long long int i = pow(10, n - 2); i < stop; i++)
    {
        for (int h = 0; h < n; h++)
        {
            int d = pow(10, h);
            int e = pow(10, h + 1);
            mid[h] = (i % e - i % d) / d;
        }
        for (int m = 0; m < n - 1; m++)
        {
            for (int j = m + 1; j < n; j++)
            {
                if (mid[m] == mid[j] || mid[m] >= n)
                {
                    judge = 0;
                    break;
                }
            }
            if (judge == 0)
            {
                break;
            }
        }
        if (judge == 0)
        {
            judge = 1;
            continue;
        }
        int final = 0;
        for (int z = 0; z < n; z++)
        {
            final += (z + 1) ^ ori[mid[z]];
        }
        result[x] = final;
        x++;
    }
    int sum = result[0];
    for (int i = 1; i < length; i++)
    {
        sum = result[i] | sum;
    }
    cout << sum;
    return 0;
}