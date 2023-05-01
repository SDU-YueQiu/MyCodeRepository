#include "iostream"
#include "Array.h"
using namespace std;
int main()
{
    int n;
    cout << "请输入学生人数：";
    cin >> n;
    Array<double> a(n);
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        cout << "请输入第" << i + 1 << "个学生的成绩：";
        cin >> a[i];
        sum += a[i];
    }
    cout << "平均成绩为：" << sum / n << endl;
    
    return 0;
}