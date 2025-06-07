#include <iostream>
#include "..\include\User.h"
#include "..\include\utils.h"


User::User(const std::string& name) : toWatch{"toWatch"}, watched{"watched"}
{
    this->name = name;
}


void User::print()
{
    std::cout << colorText(this->name, "bold_yellow") << "\n";
    
    this->toWatch.print();
    this->watched.print();

    std::cout << "\n";
    std::cout << "\n";

}


void User::addToWatch(const std::string& movieTitle)
{
    this->toWatch.add(movieTitle);
}
void User::addToWatched(const std::string& movieTitle)
{
    this->watched.add(movieTitle);
}

std::string User::getName()
{
    return this->name;
}