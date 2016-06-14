#ifndef VERTEXLIST_H
#define VERTEXLIST_H
#include <map>
#include <ostream>

using std::multimap;

class VertexList{
public:
    VertexList();
    VertexList(VertexList& vl);

    void add(unsigned int e, int w = 1);
    void remove(unsigned int e);
    void remove(unsigned int e, int w);

    friend std::ostream& operator<<(std::ostream& out, VertexList& vlist);
    friend class AdjList;
private:
    multimap<unsigned int, int> _list;
};

#endif // VERTEXLIST_H
