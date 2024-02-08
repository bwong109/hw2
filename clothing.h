#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class Clothing : public Product{
    public:
        Clothing(std::string category, std::string name, double price, int quantity, std::string size, std::string brand);
        std::set<std::string> keywords();
        std::string displayString();
        void dump(std::ostream& os);
        ~Clothing();

    private:
        std::string size_;
        std::string brand_;

};
#endif