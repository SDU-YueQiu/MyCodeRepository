#include "iostream"
using namespace std;
namespace ADT
{
    template<typename T>
    class linearList
    {
    public:
        virtual ~linearList(){};
        virtual bool empty() const = 0;
        virtual int size() const = 0;
        virtual T &get(int Idx) const = 0;
        virtual int idxOf(const T &Elmt) const = 0;
        virtual bool erase(int Idx) = 0;
        virtual bool inseart(int Idx, const T &Elmt) = 0;
        virtual bool output() = 0;
        virtual void clear() = 0;
        virtual void push_back(const T &) = 0;
    };
}// namespace ADT
//数组arr
namespace ARR
{
    template<typename T>
    class arr
    {
    public:
        arr(int n)
        {
            this->n = n;
            data = new T[n];
        }
        ~arr() { delete[] data; }
        T &operator[](int i) { return data[i]; }
        int size() { return n; }
        void full_init_cin();
        void full_print_cout();

    private:
        T *data;
        int n;
    };
    template<typename T>
    class mySort
    {
    public:
        void RankSort(arr<T> &a);
        void SelectSort(arr<T> &a);
        void BubbleSort(arr<T> &a);
        void InsertSort(arr<T> &a);
    };
    template<typename T>
    void arr<T>::full_init_cin()
    {
        for (int i = 0; i < n; i++)
            cin >> data[i];
    }
    template<typename T>
    void arr<T>::full_print_cout()
    {
        for (int i = 0; i < n; i++)
            cout << data[i] << " ";
        cout << endl;
    }
    template<typename T>
    void mySort<T>::RankSort(arr<T> &a)
    {
        int n = a.size();
        int *rk = new int[n];
        for (int i = 0; i < n; ++i) rk[i] = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++)
            {
                if (a[j] > a[i])
                    rk[j]++;
                else
                    rk[i]++;
            }
        for (int i = 0; i < n; i++)
        {
            while (rk[i] != i)
            {
                int t = rk[i];
                swap(a[i], a[t]);
                swap(rk[i], rk[t]);
            }
        }
        delete[] rk;
    }
    template<typename T>
    void mySort<T>::SelectSort(arr<T> &a)
    {
        bool f = false;
        for (int n = a.size(); (!f) && n > 1; --n)
        {
            f = true;
            int index = 0;
            for (int i = 0; i < n; ++i)
            {
                if (a[i] >= a[index])
                    index = i;
                else
                    f = false;
            }
            swap(a[index], a[n - 1]);
        }
    }
    template<typename T>
    void mySort<T>::BubbleSort(arr<T> &a)
    {
        bool f = true;
        for (int i = a.size(); i > 1 && f; --i)
        {
            f = false;
            for (int j = 0; j < i - 1; ++j)
            {
                if (a[j] > a[j + 1])
                {
                    swap(a[j], a[j + 1]);
                    f = true;
                }
            }
        }
    }
    template<typename T>
    void mySort<T>::InsertSort(arr<T> &a)
    {
        for (int i = 1; i < a.size(); ++i)
        {
            T t = a[i];
            int j;
            for (j = i - 1; j >= 0 && a[j] > t; --j)
                a[j + 1] = a[j];
            a[j + 1] = t;
        }
    }
}// namespace ARR
//可变数组vector
namespace VECTOR
{//线性表纯虚类linearList
    template<typename T>
    class myVector : public ADT::linearList<T>
    {
    private:
        T *parr;
        int N;
        int lenth;
        void copyTo(T *newParr);
        void multiplySize();
        bool checkIdx(int Idx) const;

    public:
        myVector(int n = 1) : N(n), lenth(0) { parr = new T[N]; }
        ~myVector() { delete[] parr; }
        bool empty() const { return lenth == 0; }
        int size() const { return lenth; }
        T &get(int Idx) const;
        int idxOf(const T &Elmt) const;
        bool erase(int Idx);
        bool inseart(int Idx, const T &Elmt);
        bool output();
        bool push_back(const T &Ele);
        void pop_back()
        {
            if (!empty()) lenth--;
        }
        void clear() { lenth = 0; }
        T &operator[](int &Idx) { return parr[Idx]; }
    };
    template<typename T>
    void myVector<T>::copyTo(T *newParr)
    {
        for (int i = 0; i < lenth; ++i)
            newParr[i] = parr[i];
    }
    template<typename T>
    bool myVector<T>::checkIdx(int Idx) const
    {
        if (Idx < 0 || Idx >= lenth)
        {
            string s;
            if (Idx < 0)
                s = "负数下标";
            if (Idx >= lenth)
                s = "数组越界";
            throw s;
        }
        return true;
    }
    template<typename T>
    void myVector<T>::multiplySize()
    {
        N *= 2;
        T *newParr = new T[N];
        copyTo(newParr);
        delete[] parr;
        parr = newParr;
    }
    template<typename T>
    T &myVector<T>::get(int Idx) const
    {
        checkIdx(Idx);
        return parr[Idx];
    }
    template<typename T>
    int myVector<T>::idxOf(const T &Elmt) const
    {
        for (int i = 0; i < lenth; ++i)
            if (parr[i] == Elmt)
                return i;
        return -1;
    }
    template<typename T>
    bool myVector<T>::erase(int Idx)
    {
        checkIdx(Idx);
        for (int i = Idx; i < lenth - 1; ++i)
            parr[i] = parr[i + 1];
        lenth--;
        return true;
    }
    template<typename T>
    bool myVector<T>::inseart(int Idx, const T &Elmt)
    {
        checkIdx(Idx);
        push_back(Elmt);
        for (int i = lenth - 1; i > Idx; --i)
            parr[i] = parr[i - 1];
        parr[Idx] = Elmt;
        return true;
    }
    template<typename T>
    bool myVector<T>::push_back(const T &Ele)
    {
        if (lenth == N)
            multiplySize();
        lenth++;
        parr[lenth - 1] = Ele;
        return true;
    }
    template<typename T>
    bool myVector<T>::output()
    {
        copy(parr, parr + lenth, ostream_iterator<T>(cout, " "));
        return true;
    }
}// namespace VECTOR
//双向链表chain
namespace CHAIN
{
    template<typename T>
    struct chainNode {
        T ele;
        chainNode<T> *next;
        chainNode<T> *pre;

        chainNode(T elemt, chainNode<T> *nx = NULL, chainNode<T> *pr = NULL) : ele(elemt), next(nx), pre(pr) {}
        chainNode() {}

        void nxlink(chainNode<T> &b)
        {
            next = &b;
            b.pre = this;
        }
        void prlink(chainNode<T> &b)
        {
            pre = &b;
            b.next = this;
        }
    };

    template<typename T>
    class chain : ADT::linearList<T>
    {
    public:
        chain();
        ~chain();
        chain(chain &b);

        class iterator;
        iterator begin() { return iterator(head); }
        iterator end() { return iterator(tail); }

        bool empty() { return lenth == 0; }
        int size() const { return lenth; };
        T &get(int Idx) const;
        int idxOf(const T &Elmt) const;
        bool erase(int Idx);
        bool erase(iterator it);
        bool inseart(int Idx, const T &Elmt);
        bool output();
        void clear();
        void push_back(const T &);
        void operator=(chain &b);

        class iterator
        {
        private:
            chainNode<T> *node;

        public:
            iterator() : node(NULL){};
            iterator(chainNode<T> &a) { node = &a; }

            T &operator*() { return node->ele; }
            chainNode<T>* getnode(){return node;}
            iterator &operator++()
            {
                node = node->next;
                return this;
            }
            iterator operator++(int)
            {
                iterator old = *this;
                node = node->next;
                return old;
            }
            bool operator==(iterator b) { return node == b.node; }
            bool operator!=(iterator b) { return node != b.node; }
        };

    private:
        chainNode<T> *head;
        chainNode<T> *tail;
        int lenth;
        void del(iterator);
        void del(chainNode<T>&);
        int seekIdx(iterator);
    };

    template<typename T>
    chain<T>::chain()
    {
        head = new chainNode<T>;
        tail = new chainNode<T>;
        head->pre = NULL;
        tail->next = NULL;
        head->nxlink(tail);
    }
    template<typename T>
    chain<T>::~chain()
    {
        while (head != NULL)
        {
            chainNode<T> *nx = head->next;
            delete head;
            head = nx;
        }
    }
    template<typename T>
    chain<T>::chain(chain<T> &b)
    {
        for (auto it = b.begin(); it != b.end(); ++it)
            push_back(*it);
    }
    template<typename T>
    void chain<T>::operator=(chain<T> &b)
    {
        clear();
        for (auto it = b.begin(); it != b.end(); ++it)
            push_back(*it);
    }
    template<typename T>
    void chain<T>::clear()
    {
        chainNode<T> *it = head->next;
        while (it != tail)
        {
            chainNode<T> *nx = it->next;
            erase(it);
            it = nx;
        }
    }
    template<typename T>
    void chain<T>::push_back(const T &x)
    {
        chainNode<T> *pt = new chainNode<T>;
        pt->ele = x;
        pt->prlink(tail->pre);
        pt->nxlink(tail);
        ++lenth;
    }
    template<typename T>
    bool chain<T>::erase(int Idx)
    {
        auto it = begin();
        for (int i = 1; i <= lenth; ++i)
        {
            ++it;
            if (i == Idx)
            {
                del(it);
                return true;
            }
        }
        return false;
    }
    template<typename T>
    void chain<T>::del(iterator it)
    {

    }
    template<typename T>
    bool chain<T>::erase(iterator it)
    {
        int id= seekIdx(it);
        return erase(id);
    }
    template<typename T>
    int chain<T>::seekIdx(iterator it)
    {
        auto cnt = begin();
        int i = 0;
        while (cnt != it && cnt != end())
        {
            ++i;
            ++cnt;
        }
        if(cnt==end()||cnt==begin())
            throw "不存在该迭代器";
        return i;
    }
    template<typename T>
    bool chain<T>::inseart(int Idx, const T &Elmt)
    {

        return true;
    }

}// namespace CHAIN