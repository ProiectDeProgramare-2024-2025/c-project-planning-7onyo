#ifndef MOVIE_H
#define MOVIE_H

#include <string>

class Movie
{
    private:
        std::string id;
        std::string title;
        std::string url;
        float rating;
        int runtime;
        int year;
        std::string genres;
        int numVotes;
        std::string directors;


    public:
        Movie(const std::string& id,
          const std::string& title,
          const std::string& url,
          float rating,
          int runtime,
          int year,
          const std::string& genres,
          int numVotes,
          const std::string& directors);

        void print();

        std::string getId() const;
        std::string getTitle() const;
        std::string getUrl() const;
        float getRating() const;
        int getRuntime() const;
        int getYear() const;
        std::string getGenres() const;
        int getNumVotes() const;
        std::string getDirectors() const;

};


#endif

