#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

#include "include/Movie.h"
#include "include/utils.h"


std::vector<User> users = loadUsersFromCsv();
std::vector<Movie> movies = loadMoviesFromCsv();



void viewAllUsers()
{
    std::cout << colorText("Viewing all users:", "green") << "\n\n";
    for(int i = 0; i < users.size(); i++)
        users[i].print();
    
    if(users.size() == 0)
        std::cout << colorText("No users registred", "red") << "\n";
}

void viewUser(const std::string &name)
{
    std::cout << colorText("Viewing user " + name + ":", "green") << "\n\n";
    for(int i = 0; i < users.size(); i++)
    {
        if(users[i].getName() == name)
        {
            users[i].print();
            return;
        }
    }
    std::cout << colorText("User '" + name + "' does not exist", "red") << "\n";
}



bool fileExists(const std::string& filename)
{
    return std::filesystem::exists(filename);
}


bool userExists(const std::string& username) 
{
    std::ifstream userFile("data/users.csv");
    if(!userFile.is_open())
        return false;  

    std::string line;
    while (std::getline(userFile, line)) 
    {
        if (line == username) 
        {
            userFile.close();
            return true;
        }
    }
    userFile.close();
    return false;
}





void registerUser(const std::string& username) 
{
    if(username.empty()) 
    {
        std::cout << colorText("Username cannot be empty", "red") << "\n";
        return;
    }

    if (!fileExists("data/users.csv")) 
    {
        std::ofstream createFile("data/users.csv");
        if(!createFile) 
        {
            std::cout << colorText("Failed to create users.csv", "red") << "\n";
            return;
        }
    }

    if (userExists(username)) 
    {
        std::cout << colorText("User '" + username + "' already exists", "red") << "\n";
        return;
    }


    std::ofstream userFile("data/users.csv", std::ios::app);
    if(!userFile.is_open()) 
    {
        std::cout << colorText("Failed to open users.csv for appending", "red") << "\n";
        return;
    }
    userFile << username << "\n";
    userFile.close();

    
    std::string toWatchFile = "data/" + username + "_toWatch.csv";
    std::string watchedFile = "data/" + username + "_watched.csv";

    if(!fileExists(toWatchFile)) 
    {
        std::ofstream toWatch(toWatchFile);
        toWatch.close();
    }
    if(!fileExists(watchedFile)) 
    {
        std::ofstream watched(watchedFile);
        watched.close();
    }

    std::cout << colorText("User '" + username + "' registered successfully", "green") << "\n";
}











bool movieExists(const std::string& title, const std::string& file) 
{
    std::ifstream listFile(file);
    if(!listFile.is_open())
        return false;  

    std::string line;
    while(std::getline(listFile, line)) 
    {
        if(line == title) 
        {
            listFile.close();
            return true;
        }
    }
    listFile.close();
    return false;
}


void addMovie(std::string title, std::string user, std::string list)
{
    bool validMovie = false;

    for(int i = 0; i < movies.size(); i++)
    {
        if(movies[i].getTitle() == title)
        {
            validMovie = true;
            break;
        }
    }

    if(list != "toWatch" && list != "watched")
    {
        std::cout << colorText("Not a valid list name", "red") << "\n"; 
        return;
    }

    if(validMovie)
    {
        std::string file = "data/" + user + "_" + list + ".csv";
        if(!movieExists(title, file))
        {
            std::ofstream listFile(file, std::ios::app);
        
            listFile << title << "\n";

            listFile.close();
        }
        else
        {
            std::cout << colorText("Movie is already in this list", "red") << "\n"; 
            return;
        }
            
    }
    else
    {
        std::cout << colorText("Not a valid movie", "red") << "\n"; 
        return;
    }
        


    std::cout << colorText("Movies '" + title + "' added successfully", "green") << "\n";
}


void deleteMovie(std::string title, std::string user, std::string list)
{

    if(list != "toWatch" && list != "watched")
    {
        std::cout << colorText("Not a valid list name", "red") << "\n"; 
        return;
    }

    std::vector<std::string> aux;

    std::string file = "data/" + user + "_" + list + ".csv";
    
    {
        std::ifstream listFile(file);
        std::string line;
        while(std::getline(listFile, line)) 
        {
            if (line == title)
                continue;
            aux.push_back(line);
        }
    } 

    
    {
        std::ofstream outFile(file);
        for(int i = 0; i < aux.size(); i++)
            outFile << aux[i] << "\n"; 
    } 

    std::cout << colorText("Movies '" + title + "' deleted successfully", "green") << "\n";
}





int main(int argc, char* argv[])
{
    std::string command = argv[1];

    if(argc < 2) 
    {
        std::cout << colorText("Use help command to see all possible commands", "red") << "\n";
        return 1;
    }
    else if(command == "help" && argc == 2)
    {
        std::cout << colorText("help", "green") << std::endl;
        std::cout << colorText("viewAllUsers", "green") << std::endl;
        std::cout << colorText("registerUser <userName>", "green") << std::endl;
        std::cout << colorText("viewUser <userName>", "green") << std::endl;
        std::cout << colorText("addMovie <title> <user> <list>", "green") << std::endl;
        std::cout << colorText("deleteMovie <title> <user> <list>", "green") << std::endl;
        std::cout << colorText("If strings with white spaces are used, put string between \" \"", "green") << std::endl;
        std::cout << std::endl;
    }
    else if(command == "viewAllUsers" && argc == 2)
    {
        viewAllUsers();
    }    
    else if(command == "registerUser" && argc == 3)
    {
        registerUser(argv[2]);
    }
    else if(command == "viewUser" && argc == 3)
    {
        std::string name = argv[2];
        viewUser(name);
    }
    else if(command == "addMovie" && argc == 5)
    {
        std::string title = argv[2];

        std::string user = argv[3];
        std::string list = argv[4];

        addMovie(title, user, list);
    } 
    else if(command == "deleteMovie" && argc == 5)
    {
        std::string title = argv[2];

        std::string user = argv[3];
        std::string list = argv[4];

        deleteMovie(title, user, list);
    } 
    else
        std::cout << colorText("Unknown command: " + command, "red") << std::endl;
    return 0;
}
