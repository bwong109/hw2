#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class Clothing : public Product{
    public:
        Clothing(std::string category, std::string name, double price, int quantity, std::string size, std::string brand);
        std::set<std::string> keywords() const;
        std::string displayString() const;
        void dump(std::ostream& os) const;
        ~Clothing();

    private:
        std::string size_;
        std::string brand_;

};
#endif