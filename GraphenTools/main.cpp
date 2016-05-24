#include <iostream>
#include <fstream>
#include "adjlist.h"

//#define log
#ifdef log
std::ofstream file = std::ofstream("Log.txt", std::ios::binary|std::ios::out);
std::ostream& out = file;
#else
std::ostream& out = std::cout;
#endif

int main(){
    AdjList list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);
    list.add(1, 2, 1);
    list.add(1, 5, 4);
    list.add(2, 3, 1);
    list.add(2, 5, 2);
    list.add(4, 3, 3);
    list.add(5, 4, 1);
    out << list;

    const unsigned int start = 1;
    map<unsigned int, std::pair<unsigned int, int>> dijkstra = list.dijkstra(start);
    for(auto v : dijkstra){
        out << v.first << '(' << v.second.second << "): ";
        std::string str(std::to_string(v.first));
        unsigned int it = v.first;
        while(it != start){
            it = dijkstra[it].first;
            str = std::to_string(it) + "->" + str;
        }
        out << str << '\n';
    }
}

