#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Student
{                // 学生信息结构体
    int num;     // 学号
    string name; // 姓名，字符串对象，将在第6章详细介绍
    char sex;    // 性别
    int age;     // 年龄
    int getscore()
    {
        return score;
    }

private:
    int score = 0; // 私有成员，不可直接访问
};
int main()
{
    Student stu;
    stu.num = 97001;
    stu.name= "Lin Lin";
    stu.sex = 'F';
    stu.age = 19;
    cout << "Num:  " << stu.num << endl;
    cout << "Name: " << stu.name << endl;
    cout << "Sex:  " << stu.sex << endl;
    cout << "Age:  " << stu.age << endl;
    cout << "Score: " << stu.getscore() << endl;
    return 0;
}
