#include <iostream>
#include <fstream>
#include "AdjList.h"

//#define log
#ifdef log
#define output file
#else
#define output std::cout
#endif


int main(int argc, char *argv[]){
    std::ofstream file("Log.txt", std::ios::binary|std::ios::out);
    AdjList list;
//    list.add('A');
//    list.add('B');
//    list.add('C');
//    list.add('D');
//    list.add('A', 'B');
//    list.add('A', 'C');
//    list.add('B', 'C');
//    list.add('B', 'D');
//    list.add('C', 'D');
//    std::cout << list;
//    list.undirect();
//    std::cout << list;
//    list.invert();
//    std::cout << list;
//    list.read("graph.txt");
//    std::cout << list;
//    list = list.prim();
//    std::cout << list;
    list.read("findway.txt");
    AdjList l = list.dfsTree();
    output << l;
    l = list.bfsTree();
    output << l;
    std::deque<unsigned int> queue = list.findWay(1, 18);
    for(unsigned int i : queue)
        output << i << " ";
    output  << std::endl;
}
