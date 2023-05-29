#include "iostream"
#include "vector"
#include "map"
#include "set"
#include "algorithm"
#include "cstdio"
#include "cmath"
#include "string"

using namespace std;
#define endl '\n'
//#define int long long
const int N=1e6+10;
typedef long long ll;
typedef pair<int,int> pii;
multiset<int> a;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;++i)
    {
        int t;
        cin>>t;
        a.insert(t);
    }

    return 0;
}