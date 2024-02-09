#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

Movie::Movie(std::string category, std::string name, double price, int quantity, std::string genre, std::string rating)
    : Product(category, name, price, quantity){
    genre_ = genre;
    rating_ = rating;
}

std::set<std::string> Movie::keywords() const{
    std::set<std::string> genres = parseStringToWords(convToLower(genre_));
    std::set<std::string> names = parseStringToWords(convToLower(name_));
    std::set<std::string> keywords = setUnion(names, genres);
    return keywords;
}

std::string Movie::displayString() const{
    std::stringstream display;
    display << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    display << price_ << " " << qty_ << " left.\n";
    return display.str();
}

void Movie::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}

Movie::~Movie(){}
