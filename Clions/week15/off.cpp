#include "algorithm"
#include "cmath"
#include "fstream"
#include "iostream"
#include "string"
#include "vector"

#include "cstdio"

using namespace std;

template<typename T>
class polyhedron;

template<typename T>
class point
{
private:
    T x, y, z;
    friend class polyhedron<T>;

public:
    point(T xx = 0, T yy = 0, T zz = 0) : x(xx), y(yy), z(zz) {}
    T dis(point<T> *a) { return sqrt((x - a->x) * (x - a->x) + (y - a->y) * (y - a->y) + (z - a->z) * (z - a->z)); }
};

template<typename T>
class facet
{
private:
    vector<point<T> *> vertices;
    friend class polyhedron<T>;

public:
    void push_point(point<T> *p) { vertices.push_back(p); }
    T area();
};

template<typename T>
T facet<T>::area()
{
    if (vertices.size() < 3)
    {
        cout << "It's not a face!" << endl;
        return -1;
    }
    point<T> *p1 = vertices[0], *p2 = vertices[1], *p3 = vertices[2];
    int cntp = 3;
    T sumArea = 0;
    for (cntp; cntp <= vertices.size(); ++cntp)
    {
        T l1, l2, l3;
        l1 = p1->dis(p2);
        l2 = p1->dis(p3);
        l3 = p2->dis(p3);
        T p = (l1 + l2 + l3) / 2.0;
        sumArea += sqrt(p * (p - l1) * (p - l2) * (p - l3));
        swap(p2, p3);
        if (cntp < vertices.size())
            p3 = vertices[cntp];
    }
    return sumArea;
}

template<typename T>
class polyhedron
{
private:
    vector<point<T> *> vertices;
    vector<facet<T> *> facets;
    ifstream fin;

public:
    polyhedron(const char *path) : fin(path) {}
    void init();
    point<T> *new_point(T x = 0, T y = 0, T z = 0);
    facet<T> *new_facet(int n);
    point<T> get_low();
    point<T> get_high();
    void test();
    ~polyhedron();
    T area();
};

template<typename T>
T polyhedron<T>::area()
{
    T sumarea = 0;
    for (int i = 0; i < facets.size(); ++i)
        sumarea += facets[i]->area();
    cout << "sumArea is " << sumarea << endl;
    return sumarea;
}

template<typename T>
polyhedron<T>::~polyhedron()
{
    for (auto x: vertices)
        delete x;
    for (auto x: facets)
        delete x;
    vertices.clear();
    facets.clear();
    fin.close();
}

template<typename T>
void polyhedron<T>::test()
{
    point<T> lowP = get_low();
    point<T> highP = get_high();
    cout << "The Low Point:"
         << " " << lowP.x << " " << lowP.y << " " << lowP.z << endl;
    cout << "The High Point:"
         << " " << highP.x << " " << highP.y << " " << highP.z << endl;
    area();
    return;
}

template<typename T>
point<T> *polyhedron<T>::new_point(T x, T y, T z)
{
    point<T> *np = new point<T>(x, y, z);
    vertices.push_back(np);
    return np;
}

template<typename T>
facet<T> *polyhedron<T>::new_facet(int n)
{
    facet<T> *nf = new facet<T>;
    facets.push_back(nf);
    return nf;
}

template<typename T>
void polyhedron<T>::init()
{
    string check;
    fin >> check;
    if (check != "OFF")
    {
        cout << "invail input file" << endl;
        return;
    }
    int numOfPoints, numOfFacet, numOfEdge;
    fin >> numOfPoints >> numOfFacet >> numOfEdge;
    for (int i = 0; i < numOfPoints; ++i)
    {
        T x, y, z;
        fin >> x >> y >> z;
        new_point(x, y, z);
    }
    for (int i = 0; i < numOfFacet; ++i)
    {
        int includePoints;
        fin >> includePoints;
        facet<T> *nf = new_facet(includePoints);

        while (includePoints--)
        {
            int id;
            fin >> id;
            nf->push_point(vertices[id]);
        }
    }
}

template<typename T>
point<T> polyhedron<T>::get_high()
{
    if (vertices.size() == 0)
    {
        cout << "No Points" << endl;
        return point<T>(0, 0, 0);
    }
    T minX = vertices[0]->x, minY = vertices[0]->y, minZ = vertices[0]->z;
    for (auto p: vertices)
    {
        if (p->x > minX)
            minX = p->x;
        if (p->y > minY)
            minY = p->y;
        if (p->z > minZ)
            minZ = p->z;
    }
    return point<T>(minX, minY, minZ);
}

template<typename T>
point<T> polyhedron<T>::get_low()
{
    if (vertices.size() == 0)
    {
        cout << "No Points" << endl;
        return point<T>(0, 0, 0);
    }
    T minX = vertices[0]->x, minY = vertices[0]->y, minZ = vertices[0]->z;
    for (auto p: vertices)
    {
        if (p->x < minX)
            minX = p->x;
        if (p->y < minY)
            minY = p->y;
        if (p->z < minZ)
            minZ = p->z;
    }
    return point<T>(minX, minY, minZ);
}

int main()
{
    char path[1000];
    cin >> path;
    polyhedron<double> p(path);
    p.init();
    p.test();
    return 0;
}