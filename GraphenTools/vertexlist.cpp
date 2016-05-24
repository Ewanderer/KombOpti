#include "vertexlist.h"

void VertexList::add(unsigned int e, int w){
    _list.emplace(e, w);
}
void VertexList::remove(unsigned int e){
    _list.erase(e);
}
void VertexList::remove(unsigned int e, int w){
    auto it = _list.begin();
    while(it != _list.end())
        if(it->first == e && it->second == w)
            _list.erase(it++);
        else
            ++it;
}

std::ostream& operator<<(std::ostream& out, VertexList& vlist){
    for(auto element : vlist._list)
        out << element.first << '(' << element.second << ") ";
    return out;
}
