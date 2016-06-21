#ifndef VERTEXLIST_H
#define VERTEXLIST_H
#include <map>
#include <ostream>

using std::map;

class VertexList{
public:

    int& operator[](unsigned int);

    void add(unsigned int e, int w = 1);
    void remove(unsigned int e);
    void remove(unsigned int e, int w);
    map<unsigned int, int>::iterator begin();
    map<unsigned int, int>::iterator end();
    int size();

    friend std::ostream& operator<<(std::ostream& out, VertexList& vlist);
    friend class AdjList;
private:
    map<unsigned int, int> _list;
};

#endif // VERTEXLIST_H
