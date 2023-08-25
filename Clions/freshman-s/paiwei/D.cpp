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
const int N=1e6+10;
const double eps=1e-8;
#define MAXN 2000000
typedef pair<int,int> pii;

int n, head[MAXN], num, p[MAXN], f[MAXN], ans, tag0[MAXN], tag1[MAXN], son[MAXN], p1[MAXN], p0[MAXN], s[MAXN], c[MAXN];

struct node{
    int u, v, next;
}edge[MAXN];

void build(int u, int v)
{
    num++;
    edge[num].u = u;
    edge[num].v = v;
    edge[num].next = head[u];
    head[u] = num;
}

void dfs(int u, int fa)
{
    f[u] = fa;
    int tag = 0;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].v;
        if (v == fa) continue;
        dfs(v, u);
        tag = 1;
        son[u] += son[v];
        if (p[v] == 0) tag0[u] ++;
        if (p[v] == 1) tag1[u] ++;
    }
    son[u] ++;
    if (tag0[u] && !tag1[u]) p[u] = 1;
    if (tag1[u]) p[u] = 0;
    if (!tag) p[u] = 1;
}

void find(int u, int fa)
{
    /*p1[fa] = tag1[fa];
    p0[fa] = tag0[fa];
    p1[u] = tag1[u];
    p0[u] = tag0[u];
    s[fa] = son[fa];
    s[u] = son[u];


    son[fa] = son[fa] - son[u] + ;
    if (p[u] == 1 && !son[u]) ans = 1;
    if (fa != 0)
    {

        if (p[u] == 1) tag1[fa]--;
        if (p[u] == 0) tag0[fa]--;
        if (tag0[fa] && !tag1[fa]) p[fa] = 1;
        if (tag1[fa]) p[fa] = 0;
        if (son[fa] == 1)
        {
            p[fa] = 1;
            p1[fa] = 0, p0[fa] = 0;
        }
        if (p[fa] == 1) tag1[u]++;
        if (p[fa] == 0) tag0[u]++;
    }
    if (son[u] == 1) p[u] = 0;
    if (tag0[u] && !tag1[u]) p[u] = 1;
    if (tag1[u]) p[u] = 0;
    if (p[u] == 1) ans = 1;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].v;
        if (v == fa) continue;
        find(v, u);
    }


    tag1[fa] = p1[fa];
    tag0[fa] = p0[fa];
    tag1[u] = p1[u];
    tag0[u] = p0[u];
    son[fa] = s[fa];
    son[u] = s[u];

    */

    p1[fa] = tag1[fa];
    p0[fa] = tag0[fa];
    p1[u] = tag1[u];
    p0[u] = tag0[u];
    s[fa] = son[fa];
    c[fa] = p[fa];
    c[u] = p[u];

    if (p[u] == 1) tag1[fa] --;
    if (p[u] == 0) tag0[fa] --;
    if (f[fa] == 0 && son[fa] == son[u] + 1)
    {
        p[fa] = 1;
        son[fa] = 1;
    }
    else
    {
        if (tag0[fa] && !tag1[fa]) p[fa] = 1;
        if (tag1[fa]) p[fa] = 0;
    }

    if (p[fa] == 1 && fa != 0) tag1[u]++;
    if (p[fa] == 0 && fa != 0) tag0[u]++;

    if (son[u] == 1) p[u] = 0;
    if (tag0[u] && !tag1[u]) p[u] = 1;
    if (tag1[u]) p[u] = 0;
    if (p[u] == 1) ans = 1;


    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].v;
        if (v == fa) continue;
        find(v, u);
    }

    tag1[fa] = p1[fa];
    tag0[fa] = p0[fa];
    tag1[u] = p1[u];
    tag0[u] = p0[u];
    son[fa] = s[fa];
    p[fa] = c[fa];
    p[u] = c[u];


}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;
    cin >> n;
    if (n == 1)
    {
        cout << "Alice";
        return 0;
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        build(u, v);
        build(v, u);
    }
    dfs(1, 0);
    find(1, 0);
    if (ans == 0) puts("Bob");
    else puts("Alice");
    return 0;
}
