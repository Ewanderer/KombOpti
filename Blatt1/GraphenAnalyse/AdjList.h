#ifndef ADJLIST_H
#define ADJLIST_H
#include <list>
#include <utility>
#include <iostream>

class AdjList{
    std::list<std::pair<char, std::list<char>>> list;
public:
    AdjList();

    void add(char v);
    void add(char v, char e);

    unsigned int vertices();
    unsigned int edges();

    void undirect();

    friend std::ostream& operator<<(std::ostream& out, AdjList list);
};

#endif // ADJLIST_H
