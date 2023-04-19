#include <bits/stdc++.h>
using namespace std;

#define LL long long

template<typename elemType>
inline void Read(elemType& T) {
    elemType X = 0, w = 0; char ch = 0;
    while (!isdigit(ch)) { w |= ch == '-'; ch = getchar(); }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    T = (w ? -X : X);
}

int a[100010], s[100010], ans[100010];
int n;

int main() {
    Read(n);
    for (int i = 1; i <= n; ++i)
        Read(a[i]);
    int top = 0;
    s[++top] = 1;
    for (int i = 2; i <= n; ++i) {
        while (top && a[s[top]] <= a[i]) {
            int L = s[top] + 1, R = i - 1;
            if (L <= R) {
                int mid = (L + R) >> 1;
                if ((R - L + 1) % 2 == 1) { ++ans[L]; --ans[mid]; }
                else { ++ans[L]; --ans[mid + 1]; }
            }
            --top;
        }
        int L = s[top] + 1, R = i - 1;
        int mid = (L + R) >> 1;
        if (L <= R) {
            if (!top) { ++ans[L]; --ans[R + 1]; }
            else { ++ans[mid + 1]; --ans[R + 1]; }
        }
        s[++top] = i;
    }
    while (top) {
        int L = s[top] + 1, R = n;
        if (L <= R) { ++ans[L]; --ans[R + 1]; }
        --top;
    }
    for (int i = 1; i <= n; ++i)
        ans[i] += ans[i - 1];
    for (int i = 1; i <= n; ++i)
        printf("%d ", ans[i]);
    printf("\n");

    return 0;
}
