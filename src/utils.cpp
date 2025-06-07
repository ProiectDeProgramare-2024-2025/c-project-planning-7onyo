#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "..\include\utils.h"



std::vector<std::string> parseCsvLine(const std::string& line) 
{
    std::vector<std::string> result;
    std::string current;
    bool insideQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) 
    {
        char c = line[i];

        if(c == '"') 
        {
            insideQuotes = !insideQuotes;
        } 
        
        else if(c == ',' && !insideQuotes) 
        {
            result.push_back(current);
            current.clear();
        } 
        
        else 
            current += c;
        
    }

    result.push_back(current); 
    return result;
}


std::vector<Movie> loadMoviesFromCsv()
{

    std::vector<Movie> movies;
    

    std::ifstream file("data/movies.csv");
    std::string line;

    std::getline(file, line);

    while(std::getline(file, line))
    {
        std::stringstream ss(line);
    
        std::vector<std::string> items = parseCsvLine(line);


        std::string id;
        std::string title;
        std::string url;
        float rating;
        int runtime;
        int year;
        std::string genres;
        int numVotes;
        std::string directors;
        

        id = items[1];
        title = items[2];
        url = items[3];
                
    
        try 
        {
            rating = std::stof(items[4]);
        } 
        catch(const std::invalid_argument& e) 
        {
            rating = 0.0f;
        }


        try 
        {
            runtime = std::stoi(items[5]);
        }
        catch (const std::invalid_argument& e) 
        {
            runtime = 0; 
        }
            
        
        try 
        {
            year = std::stoi(items[6]);
        }
        catch (const std::invalid_argument& e) 
        {
            year = 0; 
        }

        genres = items[7];

        try 
        {
            numVotes = std::stoi(items[8]);
        }
        catch (const std::invalid_argument& e) 
        {
            numVotes = 0; 
        }

               
        directors = items[9];


        Movie movie = Movie{id, title, url, rating, runtime, year, genres, numVotes, directors};
        movies.push_back(movie);

    }
    file.close();


    


    return movies;

}


std::vector<User> loadUsersFromCsv()
{   
    std::vector<User> users;
    std::ifstream userFile("data/users.csv");

    std::string username;
    while(std::getline(userFile, username)) 
    {
        if(username.empty()) 
            continue;

        User user(username);

        std::ifstream toWatchFile("data/" + username + "_toWatch.csv");
        std::string movieTitle;
        while(std::getline(toWatchFile, movieTitle)) 
        {
            if (!movieTitle.empty())
                user.addToWatch(movieTitle);
        }

        std::ifstream watchedFile("data/" + username + "_watched.csv");
        while (std::getline(watchedFile, movieTitle)) {
            if (!movieTitle.empty())
                user.addToWatched(movieTitle);
        }

        users.push_back(user);
    }
    return users;
}



std::string colorText(const std::string& text, const std::string& colorName) 
{
    static const std::unordered_map<std::string, std::string> colorMap = {
        {"black",   "\033[30m"},
        {"red",     "\033[31m"},
        {"green",   "\033[32m"},
        {"yellow",  "\033[33m"},
        {"blue",    "\033[34m"},
        {"magenta", "\033[35m"},
        {"cyan",    "\033[36m"},
        {"white",   "\033[37m"},
        {"reset",   "\033[0m"},
        {"bold_red", "\033[1;31m"},
        {"bold_green", "\033[1;32m"},
        {"bold_yellow", "\033[1;33m"},
        {"bold_blue", "\033[1;34m"},
    };

    auto it = colorMap.find(colorName);
    if(it != colorMap.end()) 
        return it->second + text + "\033[0m";
    else 
        return text;  // No color if name not found
    
}