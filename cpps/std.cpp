#include <iostream>
#include <string>
using namespace std;

int main()
{
    char s[10];
    s[1] = 'a';
    s[2] = 'b';
    s[3] = 'c';
    s[4] = 0;
    string ss = s+1;
    cout << ss << endl;
    return 0;
}