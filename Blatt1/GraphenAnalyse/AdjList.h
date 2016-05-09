#ifndef ADJLIST_H
#define ADJLIST_H
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cassert>

class AdjList{
    std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>> list;
public:
    void add(unsigned int v);
    void add(unsigned int v, unsigned int e, int w = 0);
    void remove(unsigned int v);
    void remove(unsigned int v, unsigned int e);
    void remove(unsigned int v, unsigned int e, int w);

    unsigned int vertices();
    unsigned int edges();
    unsigned int inDegree(unsigned int vertex);
    unsigned int minInDegree();
    unsigned int maxInDegree();
    unsigned int outDegree(unsigned int vertex);
    unsigned int minOutDegree();
    unsigned int maxOutDegree();

    void undirect();
    void invert();
    AdjList prim();
    bool verticesEqual(AdjList& adj);
    bool exists(unsigned int v);
    void read(const char* str);

    AdjList dfsTree();
    AdjList dfsTree(unsigned int v);
    AdjList bfsTree();
    AdjList bfsTree(unsigned int v);

    std::deque<unsigned int> findWay(unsigned int s, unsigned int f);

    friend std::ostream& operator<<(std::ostream& out, AdjList list);
};

#endif // ADJLIST_H
