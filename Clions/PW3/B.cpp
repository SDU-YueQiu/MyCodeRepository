#include "algorithm"
#include "cmath"
#include "map"
#include "set"
#include "vector"
#include <iostream>

using namespace std;
#define int long long
typedef long long ll;
const int N = 1e5 + 10;
#define endl '\n'

inline int sgn(int x)
{
    if (x < 0)
        return -1;
    return x == 0 ? 0 : 1;
}
inline int dian(int x1, int y1, int x2, int y2)
{
    return x1 * x2 + y1 * y2;
}
inline int cha(int x1, int y1, int x2, int y2)
{
    return x1 * y2 - y1 * x2;
}

signed main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--)
    {
        int x11, y11, x12, y12, x21, y21, x22, y22, vx, vy;
        cin >> x11 >> y11 >> x12 >> y12 >> x21 >> y21 >> x22 >> y22 >> vx >> vy;
        int flag1 = 0, flag2 = 0;

        int dx11 = x21 - x11;
        int dy11 = y21 - y11;
        int dx12 = x22 - x11;
        int dy12 = y22 - y11;

        int cha1 = cha(vx, vy, dx11, dy11);
        int cha2 = cha(vx, vy, dx12, dy12);
        int dian1 = dian(vx, vy, dx11, dy11);
        int dian2 = dian(vx, vy, dx12, dy12);

        if (cha1 == 0 || cha2 == 0)
        {
            if (cha1 == 0 && sgn(dian1) == 1)
            {
                cout << "Yes" << endl;
                continue;
            }
            if (cha2 == 0 && sgn(dian2) == 1)
            {
                cout << "Yes" << endl;
                continue;
            }
            cout << "No" << endl;
            continue;
        }

        if (sgn(cha1) != sgn(cha2))
        {
            if (sgn(cha(dx11, dy11, dx12, dy12)) != sgn(cha1))
            {
                cout << "Yes" << endl;
                continue;
            } else
            {
                cout << "No" << endl;
                continue;
            }
        }
        int sng1 = sgn(cha1);

        int dx21 = x21 - x12;
        int dy21 = y21 - y12;
        int dx22 = x22 - x12;
        int dy22 = y22 - y12;

        cha1 = cha(vx, vy, dx21, dy21);
        cha2 = cha(vx, vy, dx22, dy22);
        dian1 = dian(vx, vy, dx21, dy21);
        dian2 = dian(vx, vy, dx22, dy22);

        if (cha1 == 0 || cha2 == 0)
        {
            if (cha1 == 0 && sgn(dian1) == 1)
            {
                cout << "Yes" << endl;
                continue;
            }
            if (cha2 == 0 && sgn(dian2) == 1)
            {
                cout << "Yes" << endl;
                continue;
            }
            cout << "No" << endl;
            continue;
        }

        if (sgn(cha1) != sgn(cha2))
        {
            if (sgn(cha(dx21, dy21, dx22, dy22)) != sgn(cha1))
            {
                cout << "Yes" << endl;
                continue;
            } else
            {
                cout << "No" << endl;
                continue;
            }
        }
        int sng2 = sgn(cha1);
        if (sng1 != sng2)
        {
            if (sgn(cha(dx11, dy11, dx21, dy21)) != sng1)
            {
                cout << "Yes" << endl;
                continue;
            }
        }
        cout << "No" << endl;
    }
    return 0;
}
