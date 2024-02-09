#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore : public DataStore{

    public:
        MyDataStore();
        void addProduct(Product* p);
        void addUser(User* u);
        std::vector<Product*> search(std::vector<std::string>& terms, int type);
        void dump(std::ostream& ofile);
        bool invalidUser(std::string username);
        void addToCart(std::string username, Product* p);
        void viewCart(std::string username);
        void buyCart(std::string username);
        ~MyDataStore();

    private:
        std::vector<Product*> productsVector; 
        std::map<std::string, std::vector<Product*>> cartsMap;
		std::map<std::string, User*> usersMap;
        std::map<std::string, std::set<Product*>> keywordsMap;

};
#endif