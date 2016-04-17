#include "AdjList.h"

AdjList::AdjList(){

}

void AdjList::add(char v){                                                      //Adding a vertex if it doesn't exist
    std::list<std::pair<char, std::list<char>>>::iterator it(list.begin());
    for(; it != list.end() && it->first < v; ++it);//
    if(it == list.end()){
        list.push_back(std::pair<char, std::list<char>>(v, std::list<char>())); //Place at the end
        return;
    }
    if(it->first > v)
        list.insert(it, std::pair<char, std::list<char>>(v, std::list<char>()));//Place sorted
}
void AdjList::add(char v, char e){                                              //Adding an edge if it doesn't exist
    std::list<std::pair<char, std::list<char>>>::iterator it(list.begin());     //Adding the beginning vertex if it dowsn't exist
    for(; it != list.end() && it->first < e; ++it);
    if(it == list.end())
        list.push_back(std::pair<char, std::list<char>>(e, std::list<char>()));
    else if(it->first > e)
        list.insert(it, std::pair<char, std::list<char>>(e, std::list<char>()));

    it = list.begin();                                                          //Adding the beginning vertex if it dowsn't exist
    for(; it != list.end() && it->first < v; ++it);
    if(it == list.end()){
        list.push_back(std::pair<char, std::list<char>>(v, std::list<char>()));
        --it;
    }
    else if(it->first > v){
        list.insert(it, std::pair<char, std::list<char>>(v, std::list<char>()));
        --it;
    }

    std::list<char>::iterator it2(it->second.begin());
    for(; it2 != it->second.end() && *it2 < e; ++it2);
    if(it2 == it->second.end()){
        it->second.push_back(e);                                                //Place at the end
        return;
    }
    if(*it2 > e)
        it->second.insert(it2, e);                                              //Place sorted
}

unsigned int AdjList::vertices(){
    return list.size();
}
unsigned int AdjList::edges(){
    unsigned int counter = 0;
    for(std::list<std::pair<char, std::list<char>>>::iterator it = list.begin(); it != list.end(); ++it)
        counter += it->second.size();                                           //Sum of all lists
    return counter;
}

void AdjList::undirect(){
    for(std::list<std::pair<char, std::list<char>>>::iterator it = list.begin(); it != list.end(); ++it)
        for(std::list<char>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            add(*it2, it->first);                                               //Adding all edges reverted
}

std::ostream& operator<<(std::ostream& out, AdjList adj){
    unsigned int counter = 0;
    for(std::list<std::pair<char, std::list<char>>>::iterator it = adj.list.begin(); it != adj.list.end(); ++it){
        std::string str;
        str += it->first;
        str += ": ";
        counter += it->second.size();
        for(std::list<char>::iterator it2 = it->second.begin(); it2 != it->second.end();){
            str += *it2;
            if(++it2 != it->second.end())
                str += ", ";
        }
        out << str << '\n';
    }
    out << "Vertixes: " << adj.list.size() << '\n' << "Edges: " << counter << '\n';
    return out;
}
