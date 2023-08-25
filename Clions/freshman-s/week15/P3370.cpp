#include "iostream"
#include "map"
#include "string"

using namespace std;

int cnt = 0;
map<string, int> shash;

int main()
{
    int t;
    string s;
    cin >> t;
    while (t--)
    {
        cin >> s;
        shash[s] = (shash[s] == 0 ? ++cnt : shash[s]);
    }
    cout << cnt;
    return 0;
}