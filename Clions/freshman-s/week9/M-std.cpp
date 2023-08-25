#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int maxn = 1e6 + 10;
int dp[maxn];
int sa[maxn], ht[maxn];
string s;
int n, k;
int rk[maxn];
int x[maxn], y[maxn], c[maxn];
struct node
{
    int l, r;
    int minn_dp;
    int minn_ht;
} tree[maxn << 2];
void maintain(int rt)
{
    tree[rt].minn_dp = min(tree[rt << 1].minn_dp, tree[rt << 1 | 1].minn_dp);
    tree[rt].minn_ht = min(tree[rt << 1].minn_ht, tree[rt << 1 | 1].minn_ht);
}
void build(int rt, int l, int r)
{
    tree[rt].l = l, tree[rt].r = r;
    if (l == r)
    {
        tree[rt].minn_dp = tree[rt].minn_ht = 1e18;
        tree[rt].minn_ht = ht[l];
        return;
    }
    int mid = l + r >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    maintain(rt);
}
void update(int rt, int l, int r, int pos, int val, int cx) // cx=1 update dp
{
    if (l == r)
    {
        if (cx)
            tree[rt].minn_dp = val;
        else
            tree[rt].minn_ht = val;
        return;
    }
    int mid = l + r >> 1;
    if (pos <= mid)
        update(rt << 1, l, mid, pos, val, cx);
    else
        update(rt << 1 | 1, mid + 1, r, pos, val, cx);
    maintain(rt);
}
int query_dp(int rt, int l, int r, int ql, int qr)
{
    if (l == ql && r == qr)
        return tree[rt].minn_dp;
    int mid = l + r >> 1;
    if (qr <= mid)
        return query_dp(rt << 1, l, mid, ql, qr);
    else if (ql > mid)
        return query_dp(rt << 1 | 1, mid + 1, r, ql, qr);
    else
    {
        return min(query_dp(rt << 1, l, mid, ql, mid), query_dp(rt << 1 | 1, mid + 1, r, mid + 1, qr));
    }
}
int query_lcp(int rt, int l, int r, int ql, int qr)
{
    if (ql > qr)
        return 0;
    if (l == ql && r == qr)
        return tree[rt].minn_ht;
    int mid = l + r >> 1;
    if (qr <= mid)
        return query_lcp(rt << 1, l, mid, ql, qr);
    else if (ql > mid)
        return query_lcp(rt << 1 | 1, mid + 1, r, ql, qr);
    else
    {
        return min(query_lcp(rt << 1, l, mid, ql, mid), query_lcp(rt << 1 | 1, mid + 1, r, mid + 1, qr));
    }
}
void buildsa(string s, int *sa, int *rk, int *ht, int n, int m = 200) // nlogn
{

    s[n] = 0; //*鐢ㄦ潵澶勭悊婧㈠嚭闂
    for (register int i = 0; i < m; i++)
        c[i] = 0;
    for (register int i = 0; i < n; i++)
        c[x[i] = s[i]]++;
    for (register int i = 1; i < m; i++)
        c[i] += c[i - 1];
    for (register int i = n - 1; i >= 0; i--)
        sa[--c[x[i]]] = i;
    // 鍒╃敤鍩烘暟鎺掑簭绂绘暎鍖?
    for (int k = 1; k < n; k <<= 1)
    {
        int p = 0;
        for (int i = n - 1; i >= n - k; i--)
            y[p++] = i;
        for (int i = 0; i < n; i++)
            if (sa[i] >= k)
                y[p++] = sa[i] - k;
        // 鍏堝埄鐢ㄧ浜屼綅鍏抽敭瀛楁帓搴?
        for (int i = 0; i < m; i++)
            c[i] = 0;
        for (int i = 0; i < n; i++)
            c[x[y[i]]]++;
        for (int i = 1; i < m; i++)
            c[i] += c[i - 1];
        for (int i = n - 1; i >= 0; i--)
            sa[--c[x[y[i]]]] = y[i];
        // 浠ヤ笂涓哄熀鏁版帓搴?
        for (int j = 0; j <= n; j++)
        {
            swap(x[j], y[j]);
        }
        p = 1;
        x[sa[0]] = 0;
        y[n] = -1;
        for (int i = 1; i < n; i++)
            if (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k])
            {
                x[sa[i]] = p - 1;
            }
            else
                x[sa[i]] = p++;
        if (p == n)
            break;
        m = p;
    }
    for (int i = 0; i < n; i++)
        rk[sa[i]] = i;
    int k = 0;
    for (int i = 0; i < n; i++) // O(n)
    {                           // ht[i]=lcp(sa[i],sa[i-1]); 鍙?-n-1
        k = max(k - 1, 0ll);
        if (rk[i] == 0)
            continue;
        int j = sa[rk[i] - 1];
        while (s[i + k] == s[j + k])
            k++;
        ht[rk[i]] = k; // 鍜屽墠鍓嶉潰鐨刲ca
    }
}
signed main()
{

    ios::sync_with_stdio(false);
    //    cin.tie(0), cout.tie(0);
    //    freopen("1.in","r",stdin);
    //	freopen("1.out","w",stdout);
    cin >> s;
    string s3;
    s3 = s;
    int len1 = s3.length();
    for (int i = 0; i < s3.length() / 2; i++)
        swap(s3[i], s3[s3.length() - 1 - i]);

    s.push_back('&');
    s += s3;
    n = s.length();
    cin >> k;
    buildsa(s, sa, rk, ht, n);
    ht[0] = 1e18;
    for (int i = 0; i < len1; i++)
    {
        dp[i] = 1e18;
    }
    build(1, 0, n - 1);
    update(1, 0, n - 1, rk[0], 0, 1);
    for (int i = k; i < len1; i++)
    {
        int ans1 = rk[2 * len1 - i] + 1, ans2 = rk[2 * len1 - i];
        int l = 0, r = rk[2 * len1 - i];
        while (l <= r)
        {
            int mid = l + r >> 1;
            if (query_lcp(1, 0, n - 1, mid, rk[2 * len1 - i]) >= k)
            {
                ans1 = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }
        // ans1 鏄乏杈圭殑l+1浣嶇疆
        l = rk[2 * len1 - i] + 1;
        r = n - 1;
        while (l <= r)
        {
            int mid = l + r >> 1;
            if (query_lcp(1, 0, n - 1, rk[2 * len1 - i] + 1, mid) >= k)
            {
                ans2 = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }
        if (ans1 != 0 && ans2 != 0)
        {
            int ans3 = query_dp(1, 0, n - 1, ans1 - 1, ans2); // 21 22
            dp[i] = ans3 + 1;
            //           cout << rk[i + 1] << endl;
        }
        update(1, 0, n - 1, rk[i + 1 - k], dp[i - k], 1);
        //     cout << ans1 << ' ' << ans2 << endl;
        //    cout << i << ' ' << s[i] << ' ';
        //     cout << dp[i] << endl;
    }
    if (dp[len1 - 1] < 1e18)
    {
        cout << dp[len1 - 1];
    }
    else
        cout << -1;
}