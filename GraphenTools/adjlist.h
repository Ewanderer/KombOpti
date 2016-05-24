#ifndef ADJLIST_H
#define ADJLIST_H
#include <map>
#include <ostream>
#include <utility>
#include "vertexlist.h"

using std::map;
using std::multimap;

class AdjList{
public:

    void add(unsigned int v);
    void add(unsigned int v, unsigned int e, int w = 1);
    void remove(unsigned int v);
    void remove(unsigned int v, unsigned int e);
    void remove(unsigned int v, unsigned int e, int w);

    map<unsigned int, std::pair<unsigned int, int>> dijkstra(unsigned int v);

    friend std::ostream& operator<<(std::ostream& out, AdjList& adj);
private:
    map<unsigned int, VertexList> _list;
};

#endif // ADJLIST_H
