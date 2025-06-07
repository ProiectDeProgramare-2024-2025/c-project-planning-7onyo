#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "../include/MovieManager.h"
#include "../include/Movie.h"
#include "../include/utils.h"

MovieManager::MovieManager() {
    movies = loadMoviesFromCsv();
}

const std::vector<Movie>& MovieManager::getMovies() const {
    return movies;
}

void MovieManager::viewMovies()
{
    if (movies.empty()) {
        std::cout << colorText("No movies found.\n", "red");
        return;
    }

    std::cout << colorText("=== Movie List ===\n", "green");
    for(int i = 0; i < movies.size(); i++)
        movies[i].print();
}

void MovieManager::addMovieToCsv(const std::string& id,
        const std::string& title,
        const std::string& url,
        float rating,
        int runtime,
        int year,
        const std::string& genres,
        int numVotes,
        const std::string& directors)
{
    if (id.empty() || title.empty() || url.empty()|| genres.empty() || directors.empty()) 
    {
        std::cout << colorText("Error: All fields (id, title, url, rating, runtime, year, genres, numVotes, directors) are required.\n", "red");
        return;
    }
    if (rating <= 0.0 || runtime <= 0 || year <= 0 || numVotes <= 0) {
        std::cout << colorText("Error: All numeric fields must be positive.\n", "red");
        return;
    }


    int cnt = 0;

    {
        std::ifstream movieFile("data/movies.csv");
        std::string line;
        
        while(std::getline(movieFile, line)) 
        {
            cnt++;
        }
    }


    std::ofstream outFile("data/movies.csv", std::ios::app);
    if (!outFile) {
        std::cout << colorText("Error: Could not open movies.csv\n", "red");
        return;
    }

    outFile 
            << cnt << ","
            << id << "," 
            << title << "," 
            << url << "," 
            << rating << "," 
            << runtime << "," 
            << year << "," 
            << genres << "," 
            << numVotes << "," 
            << directors << "\n";
    
    outFile.close();

    std::cout << colorText("Movie added successfully!\n", "green");
}

void MovieManager::searchMoviesByField(const std::string& field, const std::string& query, const std::string& mode = "")
{
    std::vector<Movie> results;
    bool isNumeric = (field == "rating" || field == "runtime" || field == "year" || field == "numVotes");

    for (int i = 0; i < movies.size(); i++) {
        bool match = false;

        if (isNumeric && (mode == "less" || mode == "more")) {
            float queryValue = std::stof(query);

            if (field == "rating") {
                if (mode == "less") match = movies[i].getRating() < queryValue;
                else if (mode == "more") match = movies[i].getRating() > queryValue;
            }
            else if (field == "runtime") {
                if (mode == "less") match = movies[i].getRuntime() < queryValue;
                else if (mode == "more") match = movies[i].getRuntime() > queryValue;
            }
            else if (field == "year") {
                if (mode == "less") match = movies[i].getYear() < queryValue;
                else if (mode == "more") match = movies[i].getYear() > queryValue;
            }
            else if (field == "numVotes") {
                if (mode == "less") match = movies[i].getNumVotes() < queryValue;
                else if (mode == "more") match = movies[i].getNumVotes() > queryValue;
            }

            if (match) results.push_back(movies[i]);
        }
        else {
            if (field == "id" && movies[i].getId().find(query) != std::string::npos)
                results.push_back(movies[i]);
            else if (field == "title" && movies[i].getTitle().find(query) != std::string::npos)
                results.push_back(movies[i]);
            else if (field == "url" && movies[i].getUrl().find(query) != std::string::npos)
                results.push_back(movies[i]);
            else if (field == "genres" && movies[i].getGenres().find(query) != std::string::npos)
                results.push_back(movies[i]);
            else if (field == "directors" && movies[i].getDirectors().find(query) != std::string::npos)
                results.push_back(movies[i]);
            else if (field == "rating" && std::to_string(movies[i].getRating()).find(query) != std::string::npos)
                results.push_back(movies[i]);
            else if (field == "runtime" && std::to_string(movies[i].getRuntime()).find(query) != std::string::npos)
                results.push_back(movies[i]);
            else if (field == "year" && std::to_string(movies[i].getYear()).find(query) != std::string::npos)
                results.push_back(movies[i]);
            else if (field == "numVotes" && std::to_string(movies[i].getNumVotes()).find(query) != std::string::npos)
                results.push_back(movies[i]);
        }
    }

    auto compareMovies = [&](const Movie &a, const Movie &b) -> bool {
        if (field == "rating") {
            float aVal = a.getRating();
            float bVal = b.getRating();
            return (mode == "less") ? aVal > bVal : aVal < bVal;
        }

        if (field == "runtime") {
            int aVal = a.getRuntime();
            int bVal = b.getRuntime();
            return (mode == "less") ? aVal > bVal : aVal < bVal;
        }

        if (field == "year") {
            int aVal = a.getYear();
            int bVal = b.getYear();
            return (mode == "less") ? aVal > bVal : aVal < bVal;
        }

        if (field == "numVotes") {
            int aVal = a.getNumVotes();
            int bVal = b.getNumVotes();
            return (mode == "less") ? aVal > bVal : aVal < bVal;
        }

        return false;
    };

    if (isNumeric && (mode == "less" || mode == "more")) {
        std::sort(results.begin(), results.end(), compareMovies);
    }

    if (results.empty()) {
        std::cout << colorText("No matching movies found.\n", "red");
        return;
    }

    for (int i = 0; i < results.size(); i++)
        results[i].print();
}
