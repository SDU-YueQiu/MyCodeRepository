#include <cmath>
#include <iostream>
using namespace std;
template<class H>
class minheap
{
private:
    H *heapdata;
    int number;
    int size;
    void push(int x,int pos)
    {
        heapdata[pos] = x;
        int i=pos;
        while(i>1&&heapdata[i]<heapdata[i/2])
        {
            swap(heapdata[i],heapdata[i/2]);
            i/=2;
        }
    }
    void Create()
    {
        cout << "元素数目\n";
        int a;
        cin >> a;
        number = a;
        cout << "请输入元素\n";
        for (int i = 0; i < a; i++)
        {
            H b;
            cin >> b;
            push(b,i);
        }
    }

public:
    minheap(int a)
    {
        if (a <= 0)
            return;
        number = 0;
        size = a;
        heapdata = new H[size];
        Create();
    }
    ~minheap()
    {
        delete[] heapdata;
    }
    void print()
    {
        for (int i = 0; i < number; i++)
            cout << heapdata[i] << " ";
    }
};


int main()
{
    minheap<int> x(INT_MAX);
    x.print();
    return 0;
}