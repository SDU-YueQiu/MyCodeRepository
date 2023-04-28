#include <iostream>
using namespace std;

struct tNode {
    int data;
    tNode *next;
};
tNode *head;
void createLink(int a[], int n);
int cnt();
void add(int n);

int cnt()
{
    int j = 0;
    tNode *p = head;
    while (p) {
        if (p->data % 2 == 1) {
            j++;
        }
        p = p->next;
    }
    return j;
}
void add(int n)
{
    tNode *p = head;
    /*label:
    for (int i = 0; i < 7; i++) {
        while (p) {
            if (p->data == i) {
                i++;
                goto label;
            }
            p = p->next;
        }*/
    //这样套两层循环只能处理七个节点，其他数据不一定是七个，而且这样跳出循环也有些不知所云
    while (p)
    {
        if (p->data == n)
            return;
        p = p->next;
    }
    //运行到这里说明没有n
    tNode *pre = head;
    while (pre->next)//下一个节点为null则说明这个节点是尾节点
        pre = pre->next;
    tNode *t = new tNode;
    t->next = NULL;
    t->data = n;
    pre->next = t;
}

void createLink(int a[], int n)
{
    tNode *node;
    head = NULL;

    for (int i = n - 1; i >= 0; i--)
    {
        node = new tNode;
        node->data = a[i];
        node->next = NULL;

        node->next = head;
        head = node;
        //这样是一直往前面加节点，有点别扭，习惯上是往后面加节点
    }
}

int last()
{
    tNode *p = head;
    int n;
    while (p)
    {
        n = p->data;
        p = p->next;
    }
    return n;
}

int main()
{
    int a[] = {1, 2, 3, 4, 5};

    createLink(a, 5);
    cout << cnt() << " ";// 链表中有5个节点，3个奇数
    int m;
    cin >> m;
    add(m);
    cout << last() << endl;// 最后一个节点的值应该是7

    return 0;
}