#ifndef ADJLIST_H
#define ADJLIST_H
#include <list>
#include <map>
#include <iostream>
#include <fstream>

class AdjList{
    std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>> list;
public:
    AdjList();

    void add(unsigned int v);
    void add(unsigned int v, unsigned int e, int w = 0);

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

    friend std::ostream& operator<<(std::ostream& out, AdjList list);
};

#endif // ADJLIST_H
