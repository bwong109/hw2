#ifndef BOOK_H
#define BOOK_H
#include "product.h"

class Book : public Product{
    public:
        Book(std::string name, double price, int quantity, std::string isbn, std::string author);
        std::set<std::string> keywords();
        std::string displayString();
        void dump(std::ostream& os);
        ~Book();

    private:
        std::string isbn_;
        std::string author_;
        
};
#endif