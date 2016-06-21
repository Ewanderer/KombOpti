#include "adjlist.h"
#include <iostream>
#include <utility>

VertexList& AdjList::operator[](unsigned int v) {
    return _list[v];
}

void AdjList::add(unsigned int v) {
    _list.emplace(v, VertexList());
}
void AdjList::add(unsigned int v, unsigned int e, int w) {
    _list[v].add(e, w);
}
void AdjList::remove(unsigned int v){
    for(std::pair<unsigned int, VertexList> vlist : _list)
        vlist.second.remove(v);
    _list.erase(v);
}
void AdjList::remove(unsigned int v, unsigned int e) {
    _list[v].remove(e);
}
void AdjList::remove(unsigned int v, unsigned int e, int w) {
    _list[v].remove(e, w);
}
map<unsigned int, VertexList>::iterator AdjList::begin() {
    return _list.begin();
}
map<unsigned int, VertexList>::iterator AdjList::end() {
    return _list.end();
}
int AdjList::size() {
    return _list.size();
}

vector<unsigned int> AdjList::bfs(unsigned int s, unsigned int t) {
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

map<unsigned int, std::pair<unsigned int, int>> AdjList::dijkstra(unsigned int v) {
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

void AdjList::residual() {
    for (auto v : _list)
        for (auto e: v.second._list)
            add(e.first, v.first, 0);
}
void AdjList::augmentation(unsigned int v, unsigned int w, int d) {
    _list[v][w] -= d;
    _list[v][w] += d;
}
std::pair<unsigned int, int> AdjList::active(unsigned int t) {
    std::map<unsigned int, int> d;
    for (auto v : _list)
        d[v.first] = 0;
    for (auto v : _list)
        for (auto a : v.second) {
            d[v.first] -= a.second;
            d[a.first] += a.second;
        }
    for (auto v : d)
        if(v.second > 0 && v.second != t)
            return v;
    return std::make_pair<unsigned int, int>(0, 0);
}
unsigned int AdjList::admissible(std::map<unsigned int, int>& psi, unsigned int v) {
    for (auto a : _list[v])
        if (a.second > 0 && psi[v] > psi[a.first])
            return a.first;
    return std::numeric_limits<unsigned int>::max();
}
void AdjList::push(std::pair<unsigned int, unsigned int> a, int d) {
    d = std::min(d, _list[a.first][a.second]);
    augmentation(a.first, a.second, d);
}
void AdjList::relabel(std::map<unsigned int, int>& psi, unsigned int v) {
    int min = std::numeric_limits<int>::max();
    for (auto a : _list[v])
        if (psi[a.first] < min)
            min = psi[a.first];
    psi[v] = min + 1;
}
void AdjList::push_relabel(unsigned int s, unsigned int t) {
    for (auto a : _list[s]) {
        _list[a.first][s] = a.second;
        a.second = 0;
    }
    std::map<unsigned int, int> psi;
    for (auto v : _list)
        psi[v.first] = 0;
    psi[s] = psi.size();



    for (auto v = active(t); v.second > 0; v = active(t)) {
        unsigned int a;
        if ((a = admissible(psi, v.first)) == std::numeric_limits<unsigned int>::max())
            relabel(psi, v.first);
        else
            push(std::make_pair<unsigned int&, unsigned int&>(v.first, a), v.second);
    }
}

std::ostream& operator<<(std::ostream& out, AdjList& adj) {
    for(auto element : adj._list)
        out << element.first << ": " << element.second << '\n';
    return out;
}
