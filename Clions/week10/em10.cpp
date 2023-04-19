#include <cstring>
#include <iostream>
#include <string>
using namespace std;
bool edges[30][30];
int in[30], out[30];
bool B[30];
void dfs(int oriu)
{
    int *u = (int *) malloc(30 * sizeof(int));
    int *i = (int *) malloc(30 * sizeof(int));
    int idx = 1;
    bool f = true;
    u[idx] = oriu;

    while (idx > 0)
    {
        B[u[idx]] = 0;
        if (f == 0)
            goto lab;
        for (i[idx] = 0; i[idx] <= 25; ++i[idx])
        {
            if (B[i[idx]] && edges[u[idx]][i[idx]])
            {
                f = 1;
                ++idx;
                u[idx] = i[idx-1];
                break;
            lab:;
            }
        }
        if (i[idx] > 25)
        {
            f = 0;
            --idx;
        }
    }
    free(u);
    free(i);
}
bool solve()
{
    int n;
    cin >> n;
    string s[1000 + 10];
    for (int i = 1; i <= n; ++i)
    {
        cin >> s[i];
        int c0 = s[i][0] - 'a', c1 = s[i][s[i].size() - 1] - 'a';
        B[c0] = B[c1] = 1;
        edges[c0][c1] = edges[c1][c0] = 1;
        ++in[c1];
        ++out[c0];
    }
    int j;
    for (int i = 0; i <= 25; ++i)
        if (B[i])
        {
            j = i;
            break;
        }
    dfs(j);
    for (int i = 0; i <= 25; ++i)
        if (B[i]) return 0;
    int cntin = 0, cntout = 0;
    for (int i = 0; i <= 25; ++i)
    {
        if (in[i] - out[i] == 1) ++cntout;
        else if (out[i] - in[i] == 1)
            ++cntin;
        else if (abs(in[i] - out[i]) > 1)
            return 0;
    }
    if ((cntin == 1 && cntout == 1) || (cntin == 0 && cntout == 0)) return 1;
    return 0;
}
int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        memset(edges, 0, sizeof(edges));
        memset(B, 0, sizeof(B));
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        if (solve()) cout << "Ordering is possible.\n";
        else
            cout << "The door cannot be opened.\n";
    }
    return 0;
}