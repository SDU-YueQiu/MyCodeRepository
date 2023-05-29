#include "algorithm"
#include "cmath"
#include "cstdio"
#include "iostream"
#include "map"
#include "set"
#include "vector"
#include "string"

using namespace std;
#define endl '\n'
//#define int long long
const int N = 1e6 + 10;
typedef long long ll;
typedef pair<int, int> pii;
map<string,int> name;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    string words[25];
    for (int i = 1; i <= n; ++i)
    {
        int t;
        cin>>t;
        for(int j=1;j<=t;++j)
            cin>>words[j];
        string jojo;
        for(int j=1;j<=t;++j)
            jojo+=words[j][0];
        name[jojo]++;
    }
    int ans=0;
    for(auto x:name)
        if(x.second==1)
            ++ans;
    cout<<ans;
    return 0;
}