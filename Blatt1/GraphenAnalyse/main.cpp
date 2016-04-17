#include <iostream>
#include "AdjList.h"

int main(int argc, char *argv[]){
    AdjList list;
    list.add('A');
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

}