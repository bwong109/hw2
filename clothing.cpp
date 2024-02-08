#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

Clothing::Clothing(std::string category, std::string name, double price, int quantity, std::string size, std::string brand)
        : Product(category, name, price, quantity){
    size_ = size;
    brand_ = brand;
}

std::set<std::string> Clothing::keywords(){
    std::set<std::string> names = parseStringToWords(convToLower(name_));
    std::set<std::string> brands = parseStringToWords(convToLower(brand_));
    std::set<std::string> keywords = setUnion(names, brands);
    return keywords;
}

std::string Clothing::displayString(){
    std::stringstream display;
    display << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n";
    display << price_ << " " << qty_ << " left.\n";
    return display.str();
}

void Clothing::dump(std::ostream& os){
    os << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_<< "\n" << brand_ << "\n";
}

Clothing::~Clothing(){}