#include <iostream>
using namespace std;
int fib(int n)
{
    if (n == 0 || n == 1)
        return 1;
    return fib(n - 1) + fib(n - 2);
}

int ffib(int orin)
{
    int *n = (int *) malloc(25 * sizeof(int));
    int *ret = (int *) malloc(25 * sizeof(int));//存储return值
    int idx = 1;
    n[idx] = orin;
    int *flag = (int *) malloc(25*sizeof(int));
    //0表示初始调用，-1,-2表示两种调用，1表示回溯到lab1,2表示回溯到lab2
    for(int i=1;i<=25;i++)
        flag[i]=0;

    while (idx > 0)
    {
        flag[idx+2] = 0;
        if (flag[idx+1] == 1)
            goto lab1;
        if (flag[idx+1] == 2)
            goto lab2;
        if (n[idx] == 0 || n[idx] == 1)
        {
            flag[idx] = -flag[idx];
            ret[idx] = 1;
            idx--;
            continue;
        }
        ++idx;
        n[idx] = n[idx - 1] - 1;
        flag[idx] = -1;
        continue;
    lab1:
        ret[idx] = ret[idx + 1];

        ++idx;
        n[idx] = n[idx - 1] - 2;
        flag[idx] = -2;
        continue;
    lab2:
        ret[idx] += ret[idx + 1];

        flag[idx] = -flag[idx];
        idx--;
    }

    free(n);
    int rret = ret[1];
    free(ret);
    return rret;
}

int main()
{
    cout << "fuck你吗";
    return 0;
}
