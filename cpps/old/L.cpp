#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x = 1e18; // 定义一个double类型的变量x，赋值为1e18
    double y = sqrt(x); // 计算x的开根号，并赋值给另一个double类型的变量y
    cout << "y = " << y << endl; // 输出y的值
    return 0;
}