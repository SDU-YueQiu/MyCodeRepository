//https://codeforces.com/gym/101911/problem/A
#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<cstring>
using namespace std;
#define int long long
const int maxn = 1e6 + 10;
int ans1[maxn];
struct node
{
  int id, val;
  inline bool operator<(const node&cf)const
  {
    return val < cf.val;
  }
};
multiset<node>st;
void solve()
{
  int n, m, d;
  cin >> n >> m >> d;
  int ans = 0;
  for (int i = 1; i <= n; i++)
  {
    int x;
    cin >> x;
    node xx;
    xx.id = i, xx.val = x;
    st.insert(xx);
  }
  while (!st.empty())
  {
    ans++;
    int now = (*(st.begin())).val;
    ans1[(*st.begin()).id] = ans;
    st.erase(st.begin()); 
    while (1)
    {
      auto p = st.upper_bound({ 0,now + d });
    //  cout << (*p).id << endl;
      
      if (p == st.end())
      {
        break;
      }
      else 
      {
        now = (*p).val;
        ans1[(*p).id] = ans;
        st.erase(p);
      }
      
    }
  }
  cout << ans<<endl;
  for (int i = 1; i <= n; i++)
    cout << ans1[i] << ' ';
  cout << endl;
}
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int t=1;
  //cin >> t;
  while (t--)
    solve();

}