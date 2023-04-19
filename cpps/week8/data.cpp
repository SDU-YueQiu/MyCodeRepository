#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <algorithm>
#include <time.h>

using namespace std;
const int MAXN = 1e5 + 10;
const int INF = 0x3f3f3f3f;
typedef long long ll;
typedef pair<int, int> pii;
#define int long long

signed main()
{
    srand(time(NULL));
    int n=rand()%10+1,m=rand()%10+1;
    char s[4]={'U','D','L','R'};
    printf("%lld %lld\n",n,m);
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            int num=rand()%32;
            printf("%lld ",(1<<num));
        }
        cout<<endl;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            int k=rand()%4;
            printf("%c ",s[k]);
        }
        printf("\n");
    }
    int t=rand()%10+1;
    printf("%lld\n",t);
    while(t--)
    {
        printf("%lld %lld\n",rand()%n+1,rand()%m+1);
    }
    return 0;
}