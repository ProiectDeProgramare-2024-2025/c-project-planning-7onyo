#include <iostream>
#include <iomanip>
#include "..\include\utils.h"
#include "..\include\Movie.h"

Movie::Movie(const std::string& id,
             const std::string& title,
             const std::string& url,
             float rating,
             int runtime,
             int year,
             const std::string& genres,
             int numVotes,
             const std::string& directors)
    : id(id), title(title), url(url), rating(rating),
      runtime(runtime), year(year), genres(genres),
      numVotes(numVotes), directors(directors)
{}
std::string Movie::getId()const
{
  return this->id;    
}
std::string Movie::getTitle()const
{
  return this->title;    
}
std::string Movie::getUrl()const
{
  return this->url;    
}
float Movie::getRating()const
{
  return this->rating;
}
int Movie::getRuntime()const
{
  return this->runtime;
}
int Movie::getYear()const
{
  return this->year;
}
std::string Movie::getGenres()const
{
  return this->genres;
}
int Movie::getNumVotes()const
{
  return this->numVotes;
}
std::string Movie::getDirectors()const
{
  return this->directors;
}
#include <iostream>
#include <iomanip> // Required for setprecision

void Movie::print()
{
    std::cout 
        << colorText(this->id, "cyan") << " "
        << colorText(this->title, "green") << " "
        << colorText(this->url, "blue") << " "
        << colorText((std::ostringstream{} << std::fixed << std::setprecision(1) << this->rating).str(), "yellow") << " "
        << colorText(std::to_string(this->runtime), "magenta") << " "
        << colorText(std::to_string(this->year), "cyan") << " "
        << colorText(this->genres, "white") << " "
        << colorText(std::to_string(this->numVotes), "bright_black") << " "
        << colorText(this->directors, "bright_green") << std::endl;
}

