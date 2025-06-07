#ifndef MOVIEMANAGER_H
#define MOVIEMANAGER_H

#include "Movie.h"
#include <vector>
#include <string>

class MovieManager {
private:
    std::vector<Movie> movies;

public:
    MovieManager();

    void viewMovies();
    void addMovieToCsv(const std::string& id,
                   const std::string& title,
                   const std::string& url,
                   float rating,
                   int runtime,
                   int year,
                   const std::string& genres,
                   int numVotes,
                   const std::string& directors);
    void searchMoviesByField(const std::string& field, const std::string& query, const std::string& mode);

    const std::vector<Movie>& getMovies() const;
};

#endif