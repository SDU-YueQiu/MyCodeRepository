#include <iostream>
using namespace std;

int main() {
    int *a=new int[100]{1,2,3,4};
    int *&b=a;
    cout<<b[1];
    return 0;
}