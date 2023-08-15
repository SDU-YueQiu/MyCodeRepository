//
// Created by Yue_Qiu on 2023/7/23.
//
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>
//#define int long long
#pragma GCC optimize (2)
#pragma G++ optimize (2)
#define MAXN 300000
#define Pii pair<int, int>
#define INF 2e10 + 7

using namespace std;

struct node {
    int l,r,x,tag;
}tree[MAXN<<2];
void build(int i,int l,int r)
{
    tree[i].l=l,tree[i].r=r;
    if(l==r){
        tree[i].x=1;
        return;
    }
    int mid=l+r>>1;
    build(i<<1,l,mid);
    build(i<<1|1,mid+1,r);
}
inline int max(int a,int b){return a>b?a:b;}
void push_down(int i)
{
    if(tree[i].tag)
    {
        tree[i].x=0;
        tree[i<<1].tag=tree[i<<1|1].tag=tree[i].tag;
        tree[i].tag=0;
    }
}
void push_up(int i)
{
    int ls=0,rs=0;
    if(!tree[i<<1].tag)ls=tree[i<<1].x;
    if(!tree[i<<1|1].tag)rs=tree[i<<1|1].x;
    tree[i].x=ls+rs;
}
void add(int i,int ql,int qr,int x)
{
    int l=tree[i].l,r=tree[i].r;
    if(l==ql&&r==qr){
        tree[i].tag=x;
        return;
    }
    push_down(i);
    int mid=l+r>>1;
    if(qr<=mid)add(i<<1,ql,qr,x);
    else if(ql>mid)add(i<<1|1,ql,qr,x);
    else add(i<<1,ql,mid,x),add(i<<1|1,mid+1,qr,x);
    push_up(i);
}

struct nod{
    int v;int id;
};
inline nod max(nod a,nod b){return a.v>b.v?a:b;}
struct node2
{
    int l,r;
    nod mx;
}arrt[MAXN<<2];
int arr[MAXN];
void abuild(int i,int l,int r)
{
    arrt[i].l=l,arrt[i].r=r;
    if(l==r){
        arrt[i].mx.v=arr[l];
        arrt[i].mx.id=l;
        return;
    }
    int mid=l+r>>1;
    abuild(i<<1,l,mid);
    abuild(i<<1|1,mid+1,r);
    arrt[i].mx=max(arrt[i<<1].mx,arrt[i<<1|1].mx);
}
nod ask(int i,int ql,int qr)
{
    int l=arrt[i].l,r=arrt[i].r;
    if(l==ql&&r==qr){
        return arrt[i].mx;
    }
    int mid=l+r>>1;
    if(qr<=mid)return ask(i<<1,ql,qr);
    else if(ql>mid)return ask(i<<1|1,ql,qr);
    else return max(ask(i<<1,ql,mid),ask(i<<1|1,mid+1,qr));

}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>arr[i];
    build(1,1,n);
    abuild(1,1,n);
    while(m--)
    {
        int l,r;cin>>l>>r;
        nod tmp=ask(1,l,r);
        add(1,l,r,1);
        add(1,tmp.id,tmp.id,0);
    }
    return 0;
}
/*
3 3 1 3
1 2 1
2 3 2
1 3 4
*/