#include <iostream>
using namespace std;

int *a()
{
  static int i = 0;
  return &i;
}

int main()
{
  int *p = a();
  cout << p << endl;
  return 0;
}
