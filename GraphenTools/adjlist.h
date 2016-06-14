#ifndef ADJLIST_H
#define ADJLIST_H
#include <map>
#include <ostream>
#include <utility>
#include <limits>
#include <vector>
#include "vertexlist.h"

using std::map;
using std::multimap;
using std::vector;

class AdjList{
public:
    AdjList();
    AdjList(AdjList& adj);

    void add(unsigned int v);
    void add(unsigned int v, unsigned int e, int w = 1);
    void remove(unsigned int v);
    void remove(unsigned int v, unsigned int e);
    void remove(unsigned int v, unsigned int e, int w);

    vector<unsigned int> bfs(unsigned int s, unsigned int t);

    map<unsigned int, std::pair<unsigned int, int>> dijkstra(unsigned int v);

    AdjList maxFlow(unsigned int s, unsigned int t);

    friend std::ostream& operator<<(std::ostream& out, AdjList& adj);
private:
    map<unsigned int, VertexList> _list;
};

#endif // ADJLIST_H
