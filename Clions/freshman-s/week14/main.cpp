#include "fstream"
#include <iostream>
#include <string>
using namespace std;

class Dog
{
public:
    Dog(int weight, int age) : weight(weight), age(age) {}
    int getWeight()
    {
        return this->weight;
    }
    int getAge()
    {
        return this->age;
    }

private:
    int weight;
    int age;
};

int main()
{
    Dog dog1(5, 10);
    fstream fout("dog.txt");
    fout << dog1.getWeight() << endl;
    fout << dog1.getAge() << endl;
    fout.close();
    fstream fin("dog.txt");
    int weight, age;
    fin >> weight;
    fin >> age;
    cout<<weight<<" "<<age<<endl;
    return 0;
}
