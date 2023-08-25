#include <iostream>
using namespace std;
#define endl '\n'
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,m;
        cin>>n>>m;
        int x=1,y=1;
        cout<<"? "<<x<<" "<<y<<endl;
        cout.flush();
        int dx,dy,d;
        cin>>dx;
        x+=dx;
        if(x>n)
        {
            x-=dx;
            y+=dx;
            cout<<"? "<<x<<" "<<y<<endl;
            cout.flush();
            cin>>d;
            x+=d;
            cout<<"! "<<x<<" "<<y<<endl;
            cout.flush();
            continue ;
        }
        cout<<"? "<<x<<" "<<y<<endl;
        cout.flush();
        cin>>d;
        if(d!=dx)
        {
            y+=d;
            cout<<"! "<<x<<" "<<y<<endl;
            cout.flush();
            continue ;
        }
        else
        {
            x-=dx;
            y+=dx;
            cout<<"? "<<x<<" "<<y<<endl;
            cout.flush();
            cin>>d;
            x+=d;
            cout<<"! "<<x<<" "<<y<<endl;
            cout.flush();
        }
    }
    return 0;
}
