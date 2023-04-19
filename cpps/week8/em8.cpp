#include <iostream>
#include "cstdio"
#include "cstring"
#include "cmath"
#include "algorithm"
#include "vector"
#include "queue"
#include "set"
#include "stack"

using namespace std;
#define endl '\n'
//#define int long long
const int N=1e6+10;
typedef long long ll;
typedef pair<int,int> pii;

void solve()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>> amn(n+1,vector<int>(m+1));
    int *a[n+1]=new int [m+1];
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            cin>>a[i][j];
        }
    }


}

void qurry()
{

}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    solve();
    qurry();
    return 0;
}
