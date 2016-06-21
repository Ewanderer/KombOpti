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

    VertexList& operator[](unsigned int v);

    void add(unsigned int v);
    void add(unsigned int v, unsigned int e, int w = 1);
    void remove(unsigned int v);
    void remove(unsigned int v, unsigned int e);
    void remove(unsigned int v, unsigned int e, int w);
    map<unsigned int, VertexList>::iterator begin();
    map<unsigned int, VertexList>::iterator end();
    int size();

    vector<unsigned int> bfs(unsigned int s, unsigned int t);

    map<unsigned int, std::pair<unsigned int, int>> dijkstra(unsigned int v);

    void residual();
    void augmentation(unsigned int v, unsigned int w, int d);
    std::pair<unsigned int, int> active(unsigned int t);
    unsigned int admissible(std::map<unsigned int, int>& psi, unsigned int v);
    void push(std::pair<unsigned int, unsigned int> a, int d);
    void relabel(std::map<unsigned int, int>& psi, unsigned int v);
    void push_relabel(unsigned int s, unsigned int t);

    friend std::ostream& operator<<(std::ostream& out, AdjList& adj);
private:
    map<unsigned int, VertexList> _list;
};

#endif
