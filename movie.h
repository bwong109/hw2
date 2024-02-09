#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"

class Movie : public Product{
    public:
        Movie(std::string category, std::string name, double price, int quantity, std::string genre, std::string rating);
        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;
        ~Movie();

    private:
        std::string genre_;
        std::string rating_;

};
#endif