#include <iostream>
#include "cstdio"
#include "math.h"
#include "tuple"
#include "queue"
#include "map"
#include "stack"
#include "algorithm"
#include "set"

using namespace std;
//#define int long long
#define endl '\n'
typedef long long ll;
const int N=1e6+10;
const double eps=1e-8;
typedef pair<int,int> pii;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    double n;
    cin>>n;
    printf("%.10f",n/(2*n-2));
    return 0;
}
