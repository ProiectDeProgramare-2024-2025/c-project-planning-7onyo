#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "List.h"

class User
{
    private:
        std::string name;
        List toWatch;
        List watched;

    public:
        User(const std::string& name);
        void print();

        void addToWatch(const std::string& movieTitle);
        void addToWatched(const std::string& movieTitle);

        std::string getName();
    
    
        
    
};


#endif

