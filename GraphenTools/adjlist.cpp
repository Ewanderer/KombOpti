#include "adjlist.h"
#include <iostream>

AdjList::AdjList(){

}
AdjList::AdjList(AdjList &adj){
//    for(auto v : adj._list)
//        _list[v.first] = VertexList(v.second);
}

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

vector<unsigned int> AdjList::bfs(unsigned int s, unsigned int t){
    vector<vector<unsigned int>> list;
    list.push_back(vector<unsigned int>());
    list[0].push_back(s);
    for(unsigned int i = 0; i < list.size(); ++i){
        for(auto v : _list[list[i].back()]._list){
            vector<unsigned int> vec(list[i]);
            vec.push_back(v.first);
            if(vec.back() == t)
                return vec;
            list.push_back(vec);
        }
    }
}

std::map<unsigned int, std::pair<unsigned int, int>> AdjList::dijkstra(unsigned int v){
    std::map<unsigned int, std::pair<unsigned int, int>> dijkstra;
    for(auto it : _list)
        dijkstra.emplace(it.first, std::pair<unsigned int, int>(it.first, std::numeric_limits<int>::max()));
    dijkstra[v].second = 0;
    std::vector<unsigned int> vec;
    for(auto it : _list)
        vec.push_back(it.first);
    while(!vec.empty()){
        unsigned int min = 0;
        for(unsigned int it = 0; it < vec.size(); ++it)
            if(dijkstra[vec[it]].second < dijkstra[vec[min]].second)
                min = it;
        for(auto it : _list[vec[min]]._list)
            if(dijkstra[vec[min]].second + it.second < dijkstra[it.first].second){
                dijkstra[it.first].second = dijkstra[vec[min]].second + it.second;
                dijkstra[it.first].first = vec[min];
            }
        vec.erase(vec.begin() + min);
    }
    return dijkstra;
}

AdjList AdjList::maxFlow(unsigned int s, unsigned int t){
    //AdjList adj(*this);

}

std::ostream& operator<<(std::ostream& out, AdjList& adj){
    for(auto element : adj._list)
        out << element.first << ": " << element.second << '\n';
    return out;
}
