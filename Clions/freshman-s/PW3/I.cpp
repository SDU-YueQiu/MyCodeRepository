#include "algorithm"
#include "cmath"
#include "map"
#include "set"
#include "vector"
#include <iostream>

using namespace std;
#define int long long
typedef long long ll;
const int N = 1e5 + 10;

signed main()
{
    //ios::sync_with_stdio(false);
    int n;
    cin>>n;
    if(n%3==0)
        cout<<((n+1)/2-2)*n+n/3;
    else
        cout<<((n+1)/2-1)*n;
    return 0;
}
