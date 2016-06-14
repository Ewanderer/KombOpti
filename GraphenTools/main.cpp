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
    list.add(0);
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);
    list.add(6);
    list.add(0, 1, 10);
    list.add(0, 2, 20);
    list.add(0, 3, 15);
    list.add(1, 4, 8);
    list.add(2, 1, 4);
    list.add(2, 4, 5);
    list.add(2, 5, 9);
    list.add(3, 2, 4);
    list.add(3, 5, 6);
    list.add(4, 5, 25);
    list.add(4, 6, 10);
    list.add(5, 6, 30);
    out << list;
    auto p = list.bfs(0, 7);
    for(auto i : p)
        std::cout << i << std::endl;
}

