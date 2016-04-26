#ifndef ADJLIST_H
#define ADJLIST_H
#include <list>
#include <map>
#include <iostream>

class AdjList{
    std::list<std::pair<char, std::list<char>>> list;
public:
    AdjList();

    void add(char v);
    void add(char v, char e);

    unsigned int vertices();
    unsigned int edges();
    unsigned int inDegree(char vertex);
    unsigned int maxInDegree();
    unsigned int outDegree(char vertex);
    unsigned int maxOutDegree();

    void undirect();
    void invert();

    friend std::ostream& operator<<(std::ostream& out, AdjList list);
};

#endif // ADJLIST_H
