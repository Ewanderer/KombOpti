#include <iostream>
#include <fstream>
#include "AdjList.h"

int main(int argc, char *argv[]){
    std::ofstream out("Log.txt");
    AdjList list;
/*    list.add('A');
    list.add('B');
    list.add('C');
    list.add('D');
    list.add('A', 'B');
    list.add('A', 'C');
    list.add('B', 'C');
    list.add('B', 'D');
    list.add('C', 'D');
    std::cout << list;
    list.undirect();
    std::cout << list;
    list.invert();
    std::cout << list;*/
    list.read("graph.txt");
    std::cout << list;
//    list = list.prim();
//    std::cout << list;
    AdjList l = list.dfsTree();
    std::cout << list;
}
