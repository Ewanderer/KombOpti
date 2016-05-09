#include "AdjList.h"

AdjList::AdjList(){

}

void AdjList::add(unsigned int v){                                                      //Adding a vertex if it doesn't exist
    std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator it(list.begin());
    for(; it != list.end() && it->first < v; ++it);//
    if(it == list.end()){
        list.push_back(std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>(v, std::list<std::pair<unsigned int, int>>())); //Place at the end
        return;
    }
    if(it->first > v)
        list.insert(it, std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>(v, std::list<std::pair<unsigned int, int>>()));//Place sorted
}
void AdjList::add(unsigned int v, unsigned int e, int w){                                              //Adding an edge if it doesn't exist
    std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator it(list.begin());     //Adding the beginning vertex if it dowsn't exist
    for(; it != list.end() && it->first < e; ++it);
    if(it == list.end())
        list.push_back(std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>(e, std::list<std::pair<unsigned int, int>>()));
    else if(it->first > e)
        list.insert(it, std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>(e, std::list<std::pair<unsigned int, int>>()));

    it = list.begin();                                                          //Adding the beginning vertex if it dowsn't exist
    for(; it != list.end() && it->first < v; ++it);
    if(it == list.end()){
        list.push_back(std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>(v, std::list<std::pair<unsigned int, int>>()));
        --it;
    }
    else if(it->first > v){
        list.insert(it, std::pair<char, std::list<std::pair<unsigned int, int>>>(v, std::list<std::pair<unsigned int, int>>()));
        --it;
    }

    std::list<std::pair<unsigned int, int>>::iterator it2(it->second.begin());
    for(; it2 != it->second.end() && it2->first < e; ++it2);
    if(it2 == it->second.end()){
        it->second.push_back(std::pair<unsigned int, int>(e, w));                                                //Place at the end
        return;
    }
    if(it2->first > e)
        it->second.insert(it2, std::pair<unsigned int, int>(e, w));                                              //Place sorted
}
void AdjList::remove(unsigned int v){
    for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator it = list.begin(); it != list.end(); ++it)
        it->second.remove_if([&](std::pair<unsigned int, int>& element)->bool{
            return element.first == v;
        });
    list.remove_if([&](std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>& element)->bool{
        return element.first == v;
    });
}
void AdjList::remove(unsigned int v, unsigned int e){
    std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator it = list.begin();
    while(it != list.end() && v < it->first)
        ++it;
    it->second.remove_if([&](std::pair<unsigned int, int>& element){
        return element.first == e;
    });
}
void AdjList::remove(unsigned int v, unsigned int e, int w){
    std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator it = list.begin();
    while(it != list.end() && v < it->first)
        ++it;
    it->second.remove_if([&](std::pair<unsigned int, int>& element){
        return element.first == e && element.second == w;
    });
}

unsigned int AdjList::vertices(){
    return list.size();
}
unsigned int AdjList::edges(){
    unsigned int counter = 0;
    for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator it = list.begin(); it != list.end(); ++it)
        counter += it->second.size();                                           //Sum of all lists
    return counter;
}
unsigned int AdjList::inDegree(unsigned int vertex){
    unsigned int c = 0;
    for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator v = list.begin(); v != list.end(); ++v)
        for(std::list<std::pair<unsigned int, int>>::iterator e = v->second.begin(); e != v->second.end(); ++e)
            if(e->first == vertex)
                ++c;
    return c;
}
unsigned int AdjList::minInDegree(){
    std::map<unsigned int, unsigned int> c;
    for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator v = list.begin(); v != list.end(); ++v)
        c.emplace(v->first, 0);
    for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator v = list.begin(); v != list.end(); ++v)
        for(std::list<std::pair<unsigned int, int>>::iterator e = v->second.begin(); e != v->second.end(); ++e)
            ++c[e->first];
    unsigned int min = c[list.front().first];
    for(std::map<unsigned int, unsigned int>::iterator v = c.begin(); v != c.end(); ++v)
        if(v->second < min)
            min = v->second;
    return min;
}
unsigned int AdjList::maxInDegree(){
    std::map<unsigned int, unsigned int> c;
    for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator v = list.begin(); v != list.end(); ++v)
        c.emplace(v->first, 0);
    for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator v = list.begin(); v != list.end(); ++v)
        for(std::list<std::pair<unsigned int, int>>::iterator e = v->second.begin(); e != v->second.end(); ++e)
            ++c[e->first];
    unsigned int max = 0;
    for(std::map<unsigned int, unsigned int>::iterator v = c.begin(); v != c.end(); ++v)
        if(v->second > max)
            max = v->second;
    return max;
}
unsigned int AdjList::outDegree(unsigned int vertex){
    for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator v = list.begin(); v != list.end(); ++v)
        if(v->first == vertex)
            return v->second.size();
    return 0;
}
unsigned int AdjList::minOutDegree(){
    unsigned int min = list.front().second.size();
    for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator v = list.begin(); v != list.end(); ++v)
        if(v->second.size() < min)
            min = v->second.size();
    return min;
}
unsigned int AdjList::maxOutDegree(){
    unsigned int max = 0;
    for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator v = list.begin(); v != list.end(); ++v)
        if(v->second.size() > max)
            max = v->second.size();
    return max;
}

void AdjList::undirect(){
    for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator it = list.begin(); it != list.end(); ++it)
        for(std::list<std::pair<unsigned int, int>>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            add(it2->first, it->first);                                               //Adding all edges reverted
}
void AdjList::invert(){
    for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator v = list.begin(); v != list.end(); ++v){
        std::list<std::pair<unsigned int, int>>::iterator e = v->second.begin();
        for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator i = list.begin(); i != list.end(); ++i)
            if(v->first == i->first)
                continue;
            else if(e->first == i->first)
                v->second.erase(e++);
            else
                v->second.insert(e, std::pair<unsigned int, int>(i->first, 0));
    }
}
AdjList AdjList::prim(){
    AdjList adj;
    adj.add(list.begin()->first);
    std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator begin = list.begin();
    while(begin != list.end() && begin->second.size() == 0)
        ++begin;
    if(begin == list.end())
        return adj;
    while(!verticesEqual(adj)){
        std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator vMin = begin;
        std::list<std::pair<unsigned int, int>>::iterator eMin = vMin->second.begin();
        for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator v = list.begin(); v != list.end(); ++v)
            for(std::list<std::pair<unsigned int, int>>::iterator e = v->second.begin(); e != v->second.end(); ++e)
                if(adj.exists(v->first) && (!adj.exists(e->first)) && (e->second < eMin->second || adj.exists(eMin->first))){
                    vMin = v;
                    eMin = e;
                }
        if(adj.exists(eMin->first))
            break;
        adj.add(vMin->first, eMin->first, eMin->second);
        adj.add(eMin->first, vMin->first, eMin->second);
    }
    return adj;
}
bool AdjList::verticesEqual(AdjList& adj){
    if(list.size() != adj.list.size())
        return false;
    for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator it = list.begin(), it2 = adj.list.begin(); it != list.end(); ++it, ++it2)
        if(it->first != it2->first)
            return false;
    return true;
}
bool AdjList::exists(unsigned int v){
    for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator it = list.begin(); it != list.end(); ++it)
        if(it->first == v)
            return true;
    return false;
}
void AdjList::read(const char* str){
    std::ifstream file(str, std::ios::binary | std::ios::in);
    while(file.good()){
        if(file.get() != 'E' || file.get() != ' '){
            while(file.good() && file.get() != '\n');
            continue;
        }
        unsigned int v = 0;
        unsigned int e = 0;
        int w = 0;
        for(char temp = file.get(); temp >= '0' && temp <= '9'; temp = file.get())
            v = v*10 + temp-'0';
        for(char temp = file.get(); temp >= '0' && temp <= '9'; temp = file.get())
            e = e*10 + temp-'0';
        for(char temp = file.get(); temp >= '0' && temp <= '9'; temp = file.get())
            w = w*10 + temp-'0';
        add(v, e, w);
        add(e, v, w);
    }
    file.close();
}

AdjList AdjList::dfsTree(){
    return list.empty() ? AdjList() : dfsTree(list.begin()->first);
}
AdjList AdjList::dfsTree(unsigned int v){
    AdjList adj;
    adj.add(v);
    std::vector<unsigned int> stack;
    stack.push_back(v);
    while(!stack.empty()){
        unsigned int temp = stack.back();
        stack.pop_back();
        std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator it = list.begin();
        while(it != list.end() && temp > it->first)
            ++it;
        for(std::list<std::pair<unsigned int, int>>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2){
            std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator it3 = adj.list.begin();
            while(it3 != adj.list.end() && it2->first > it3->first)
                ++it3;
            if(it2->first != it3->first){
                stack.push_back(it2->first);
                adj.add(it->first, it2->first, it2->second);
            }
        }
    }
    return adj;
}

std::ostream& operator<<(std::ostream& out, AdjList adj){
    unsigned int counter = 0;
    for(std::list<std::pair<unsigned int, std::list<std::pair<unsigned int, int>>>>::iterator it = adj.list.begin(); it != adj.list.end(); ++it){
        std::string str;
        str += std::to_string(it->first);
        str += ": ";
        counter += it->second.size();
        for(std::list<std::pair<unsigned int, int>>::iterator it2 = it->second.begin(); it2 != it->second.end();){
            str += std::to_string(it2->first);
            str += '(';
            str += std::to_string(it2->second);
            str += ')';
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
