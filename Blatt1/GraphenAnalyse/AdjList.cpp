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
unsigned int AdjList::inDegree(char vertex){
    unsigned int c = 0;
    for(std::list<std::pair<char, std::list<char>>>::iterator v = list.begin(); v != list.end(); ++v)
        for(std::list<char>::iterator e = v->second.begin(); e != v->second.end(); ++e)
            if(*e == vertex)
                ++c;
    return c;
}
unsigned int AdjList::minInDegree(){
    std::map<char, unsigned int> c;
    for(std::list<std::pair<char, std::list<char>>>::iterator v = list.begin(); v != list.end(); ++v)
        c.emplace(v->first, 0);
    for(std::list<std::pair<char, std::list<char>>>::iterator v = list.begin(); v != list.end(); ++v)
        for(std::list<char>::iterator e = v->second.begin(); e != v->second.end(); ++e)
            ++c[*e];
    unsigned int min = c[list.front().first];
    for(std::map<char, unsigned int>::iterator v = c.begin(); v != c.end(); ++v)
        if(v->second < min)
            min = v->second;
    return min;
}
unsigned int AdjList::maxInDegree(){
    std::map<char, unsigned int> c;
    for(std::list<std::pair<char, std::list<char>>>::iterator v = list.begin(); v != list.end(); ++v)
        c.emplace(v->first, 0);
    for(std::list<std::pair<char, std::list<char>>>::iterator v = list.begin(); v != list.end(); ++v)
        for(std::list<char>::iterator e = v->second.begin(); e != v->second.end(); ++e)
            ++c[*e];
    unsigned int max = 0;
    for(std::map<char, unsigned int>::iterator v = c.begin(); v != c.end(); ++v)
        if(v->second > max)
            max = v->second;
    return max;
}
unsigned int AdjList::outDegree(char vertex){
    for(std::list<std::pair<char, std::list<char>>>::iterator v = list.begin(); v != list.end(); ++v)
        if(v->first == vertex)
            return v->second.size();
    return 0;
}
unsigned int AdjList::minOutDegree(){
    unsigned int min = list.front().second.size();
    for(std::list<std::pair<char, std::list<char>>>::iterator v = list.begin(); v != list.end(); ++v)
        if(v->second.size() < min)
            min = v->second.size();
    return min;
}
unsigned int AdjList::maxOutDegree(){
    unsigned int max = 0;
    for(std::list<std::pair<char, std::list<char>>>::iterator v = list.begin(); v != list.end(); ++v)
        if(v->second.size() > max)
            max = v->second.size();
    return max;
}

void AdjList::undirect(){
    for(std::list<std::pair<char, std::list<char>>>::iterator it = list.begin(); it != list.end(); ++it)
        for(std::list<char>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            add(*it2, it->first);                                               //Adding all edges reverted
}
void AdjList::invert(){
    for(std::list<std::pair<char, std::list<char>>>::iterator v = list.begin(); v != list.end(); ++v){
        std::list<char>::iterator e = v->second.begin();
        for(std::list<std::pair<char, std::list<char>>>::iterator i = list.begin(); i != list.end(); ++i)
            if(v->first == i->first)
                continue;
            else if(*e == i->first)
                v->second.erase(e++);
            else
                v->second.insert(e, i->first);
    }
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
    out << "Vertices: " << adj.list.size() << '\n' << "Edges: " << counter << '\n';
    out << "Min indegree: " << adj.minInDegree() << '\n' << "Max indegree: " << adj.maxInDegree() << '\n';
    out << "Min outdegree: " << adj.minOutDegree() << '\n' << "Max outdegree: " << adj.maxOutDegree() << '\n';
    return out;
}
