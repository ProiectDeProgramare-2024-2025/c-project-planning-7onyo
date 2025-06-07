#ifndef LIST_H
#define LIST_H


#include <string>
#include <vector>


class List
{
    private:
        std::string name;
        std::vector<std::string> items;

    public:
        List(const std::string &name );
        void print();
        void add(const std::string& title); 
        void remove(const std::string& title); 

};


#endif

