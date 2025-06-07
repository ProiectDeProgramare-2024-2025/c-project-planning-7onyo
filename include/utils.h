#include <vector>
#include <string>
#include "Movie.h"
#include "User.h"



std::vector<std::string> parseCsvLine(const std::string& line);
std::vector<Movie> loadMoviesFromCsv();
std::vector<User> loadUsersFromCsv();

std::string colorText(const std::string& text, const std::string& colorName);
