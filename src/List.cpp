#include <iostream>
#include "..\include\List.h"
#include "..\include\utils.h"


List::List(const std::string &name)
{
    this->name = name;
    this->items = {};
}

void List::print()
{
    std::cout << colorText(this->name, "cyan") + ":\n";

    for(int i = 0; i < this->items.size(); i++)
        std::cout << "    " << colorText(this->items[i], "magenta") << "\n";

    std::cout << "\n";    
}

void List::add(const std::string& title)
{
    this->items.push_back(title);
}

void List::remove(const std::string& title)
{
    for(int i = 0; i < this->items.size(); i++)
        if(this->items[i] == title)
        {
            this->items.erase(this->items.begin() + i);
            break;
        }
}

