//
// Created by Yue_Qiu on 2023/4/16.
//
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
const int maxn=1e6+10;
const double eps=1e-8;
typedef pair<int,int> pii;
struct edge
{
    int to;
    int nex;
}e[maxn];
int first[maxn],tot;
void add(int a,int b)
{
    e[++tot].to=b;
    e[tot].nex=first[a];
    first[a]=tot;
}
int cnt1[maxn],cnt0[maxn],val[maxn],s[maxn];
void dfs1(int now,int fa)
{
    int son=0;
    for(int i=first[now];i;i=e[i].nex)
    {
        int to = e[i].to;
        if(to==fa) continue;
        dfs1(to,now);
        son++;
        if(val[to]==1)cnt1[now]++;
        else cnt0[now]++;
    }
    if(son==0) val[now]=1;
    else
    {
        if(son==cnt0[now]) val[now]=1;
        else val[now]=0;
    }
    s[now]=son;
}
void dfs2(int now,int fa)
{
    int tmp=val[now];
    int tmp1=cnt1[now];
    int tmp0=cnt0[now];
    if(now!=1)
    {

        if(val[now]==1)
        {
            if(val[fa]==0 && cnt1[fa]==1)
            {
                val[now]=0;
            }
            else
            {
                cout<<"Alice";
                exit(0);
            }
        }
        else if(val[now]==0)
        {
            if(val[fa]==1)
                cnt1[now]++;
            else
                cnt0[now]++;
        }
    }
    for(int i= first[now];i;i=e[i].nex)
    {
        int to=e[i].to;
        if(to==fa) continue;
        dfs2(to,now);
    }
    val[now]=tmp;
    cnt1[now]=tmp1;
    cnt0[now]=tmp0;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;cin>>n; int a,b;
    if(n==1)
    {
        cout<<"Alice";
        return 0;
    }
    for(int i=1;i<n;i++)
    {
        cin>>a>>b;
        add(a,b);add(b,a);
    }
    dfs1(1,0);
    if(val[1]==1)
        cout<<"Alice";
    dfs2(1,0);
    cout<<"Bob";
    return 0;
}
