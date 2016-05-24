#include "adjlist.h"

void AdjList::add(unsigned int v){
    _list.emplace(v, VertexList());
}
void AdjList::add(unsigned int v, unsigned int e, int w){
    _list[v].add(e, w);
}
void AdjList::remove(unsigned int v){
    for(std::pair<unsigned int, VertexList> vlist : _list)
        vlist.second.remove(v);
    _list.erase(v);
}
void AdjList::remove(unsigned int v, unsigned int e){
    _list[v].remove(e);
}
void AdjList::remove(unsigned int v, unsigned int e, int w){
    _list[v].remove(e, w);
}

std::ostream& operator<<(std::ostream& out, AdjList& adj){
    for(auto element : adj._list)
        out << element.first << ": " << element.second << '\n';
    return out;
}
