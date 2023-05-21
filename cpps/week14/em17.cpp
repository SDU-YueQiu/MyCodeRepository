#include <iostream>
#include <cmath>
using namespace std;

void ShellSort(int *Array, int n)
{
    int i, j, gap;
    int temp;
    for (gap = n / 2; gap > 0; gap /= 2)
    {
        for (i = gap; i < n; i++)
        {
            temp = Array[i];
            for (j = i; j >= gap && temp < Array[j - gap]; j -= gap)
                Array[j] = Array[j - gap];
            Array[j] = temp;
        }
    }
}   

int main()
{
    const int MAXSIZE = 8;
    int Array[MAXSIZE];
    cout << "请输入数据\n";
    for (int k = 0; k < MAXSIZE; k++)
        cin >> Array[k];

    ShellSort(Array, MAXSIZE);

    for (int k = 0; k < MAXSIZE; k++)
        cout << Array[k] << " ";

    return 0;
}
