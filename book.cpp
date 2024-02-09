#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

Book::Book(std:: string category, std::string name, double price, int quantity, std::string isbn, std::string author) 
    : Product(category, name, price, quantity){
    isbn_ = isbn; 
    author_ = author;
}

std::set<std::string> Book::keywords() const{
    std::set<std::string> authors = parseStringToWords(convToLower(author_));
    std::set<std::string> names = parseStringToWords(convToLower(name_));
    std::set<std::string> keywords = setUnion(names, authors);
    return keywords;
}

std::string Book::displayString() const{
    std::stringstream display;
    display << name_ << "\n" << "ISBN: " << isbn_ << " Author: " << author_ << "\n";
    display << price_ << " " << qty_ << " left.\n";
    return display.str();
}

void Book::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << std::endl;
}

Book::~Book(){};