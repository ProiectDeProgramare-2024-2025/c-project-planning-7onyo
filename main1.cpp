#include <iostream>
#include <string>
#include "include/utils.h"
#include "include/MovieManager.h"

int main(int argc, char* argv[])
{
    MovieManager Manager;

    if (argc < 2) 
    {
        std::cout << colorText("Use help command to see all possible commands", "red") << "\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "help" && argc == 2)
    {
        std::cout << colorText("viewMovies", "green") << std::endl;
        std::cout << colorText("searchMovies <field> <value> [mode]", "green") << std::endl;
        std::cout << "Fields: id, title, url, rating, runtime, year, genres, numVotes, directors\n";
        std::cout << "Modes (only for rating, runtime, year, numVotes): less, more, any other mode results in a normal search\n";
        std::cout << colorText("addMovieToCsv <id> <title> <url> <rating> <runtime> <year> <genres> <numVotes> <directors>", "green") << std::endl;
        std::cout << colorText("Note:", "yellow") << " If an argument contains spaces, enclose them in double quotes (e.g. \"The Dark Knight\")\n";
        std::cout << std::endl;
    }
    else if (command == "viewMovies") 
    {
        Manager.viewMovies();
    }
    else if (command == "searchMovies")
    {
        if (argc < 4) {
            std::cout << colorText("Usage: searchMovies <field> <value> [mode]\n", "red");
            return 1;
        }

        std::string field = argv[2];
        std::string query = argv[3];
        std::string mode = (argc > 4) ? argv[4] : "";

        Manager.searchMoviesByField(field, query, mode);
    }
    else if (command == "addMovieToCsv" && argc == 11)
    {
        std::string id = argv[2];
        std::string title = argv[3];
        std::string url = argv[4];

        float rating = std::stof(argv[5]);
        int runtime = std::stoi(argv[6]);
        int year = std::stoi(argv[7]);
        std::string genres = argv[8];
        int numVotes = std::stoi(argv[9]);
        std::string directors = argv[10];

        Manager.addMovieToCsv(id, title, url, rating, runtime, year, genres, numVotes, directors);
    }
    else 
    {
        std::cout << colorText("Unknown command: " + command + "\n", "red");
    }

    return 0;
}