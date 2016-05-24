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
    out << list;
}

