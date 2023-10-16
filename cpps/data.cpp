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
#include <set>

using namespace std;
const int MAXN = 1e5 + 10;
const int INF = 0x3f3f3f3f;
typedef long long ll;
typedef pair<int, int> pii;
#define int long long

signed main()
{
    srand(time(NULL));
    int t = rand() % 20000 + 1;
    cout << t << endl;

    vector<int> name;
    vector<int> phone;
    vector<int> cls;
    vector<int> dom;
    while (t--)
    {
        int o = rand() % 4 + 1;
        if (name.empty())
            o = 0;
        cout << o << " ";
        if (o == 0)
        {
            int newname = rand() % 100000 + 1;
            while (find(name.begin(), name.end(), newname) != name.end())
                newname = rand() % 100000 + 1;
            int newphone = rand() % 100000 + 1;
            int newcls = rand() % 100000 + 1;
            int newdom = rand() % 100000 + 1;
            name.push_back(newname);
            phone.push_back(newphone);
            cls.push_back(newcls);
            dom.push_back(newdom);
            cout << newname << " " << newphone << " " << newcls << " " << newdom << endl;
        }
        if (o == 1)
        {
            int randname = rand() % name.size();
            cout << name[randname] << endl;
            name.erase(name.begin() + randname);
            phone.erase(phone.begin() + randname);
            cls.erase(cls.begin() + randname);
            dom.erase(dom.begin() + randname);
        }
        if (o == 2)
        {
            int randname = rand() % name.size();
            int no = rand() % 3 + 1;
            int newif = rand() % 100000 + 1;
            cout << name[randname] << " " << no << " " << newif << endl;
        }
        if (o == 3)
        {
            int randname = rand() % name.size();
            cout << name[randname] << endl;
        }
        if (o == 4)
        {
            int randcls = rand() % cls.size();
            cout << cls[randcls] << endl;
        }
    }
    return 0;
}