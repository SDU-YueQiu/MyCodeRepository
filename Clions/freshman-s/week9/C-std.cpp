#include <bits/stdc++.h>
using namespace std;

#define lint long long
#define rep(_, __, ___) for (int _ = __; _ <= ___; ++_)

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        lint a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        lint mul = a * b;
        lint l = 1, r = (c / 2);
        lint ans = -1;
        while (l <= r)
        {
            lint mid = (l + r) >> 1;
            if (mid * (c - mid) == mul)
            {
                ans = mid;
                break;
            }
            else if (mid * (c - mid) > mul)
            {
                r = mid - 1;
            }
            else
            {
                l = mid + 1;
            }
        }
        if (ans == -1)
        {
            printf("-1\n");
            continue;
        }
        if (__gcd(ans, (c - ans)) == a)
        {
            printf("%lld %lld\n", ans, c - ans);
        }
        else
        {
            printf("-1\n");
        }
    }
    return 0;
}