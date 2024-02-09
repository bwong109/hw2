#include <map>
#include <iostream>
#include <vector>
#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore(){}

void MyDataStore::addProduct(Product* p){

    productsVector.push_back(p);
    std::set<std::string> words = p->keywords();
    std::set<std::string>::iterator it;

    for (it = words.begin(); it != words.end(); ++it){
        
        // Set iterators and keywords
        const std::string& keyword = *it;
        std::map<std::string, std::set<Product*>>::iterator it2 = keywordsMap.find(keyword);

        // Create a new set and insert the product if doesn't exist
        if (it2 == keywordsMap.end()){
            std::set<Product*> temp;
            temp.insert(p);
            keywordsMap.insert(std::make_pair(keyword, temp));
        }

        // Insert the product if exists
        else{
            it2->second.insert(p);
        }
    }

}

void MyDataStore::addUser(User* u){
    usersMap[u->getName()] = u;
    cartsMap[u->getName()] = std::vector<Product*>();
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){

    // Set iterator and set to store products based on search type
    vector<std::string>::iterator it;
    set <Product*> resultSet;

    for (it = terms.begin(); it != terms.end(); ++it){

        set<Product*> tempSet = keywordsMap[*it];

        // If type is intersection
        if (type == 0){

            // If it is first term, set result to the set of products
            if (it == terms.begin()){
                resultSet = tempSet;
            }

            // If not, then intersect with resultSet
            else{
                resultSet = setIntersection(resultSet, tempSet);
            }
        }

        // If type is union, then union resultSet
        else if (type == 1){
            resultSet = setUnion(resultSet, tempSet);
        }
    }

    // Covnert resultSet into a vector and then return it
    std::vector<Product*> resultVector(resultSet.begin(), resultSet.end());
    return resultVector;

}

void MyDataStore::dump(std::ostream& ofile){

    // Output tag for products and iterators
    ofile << "<products>" << endl;
	vector<Product*>::iterator itProd;
	map<string, User*>::iterator itMap;

    // Dump product info into output
	for(itProd = productsVector.begin(); itProd != productsVector.end(); itProd++){
		(*itProd)->dump(ofile); 
	}

    // Closing tag for products, opening for users
	ofile << "</products>" << endl;
	ofile << "<users>" << endl;

    // Dump user info into output
	for(itMap = usersMap.begin(); itMap != usersMap.end(); itMap++){
		itMap->second->dump(ofile); 
	}

    // Output tag for users
	ofile << "</users>" << endl;

}

bool MyDataStore::invalidUser(std::string username){

    return (usersMap.find(username) != usersMap.end());

}

void MyDataStore::addToCart(std::string username, Product* p){

    // Checks if username is valid
    if (!invalidUser(username)){
        std::cout << "Invalid request" << std::endl;
        return;
    }
    
    // If valid, then add to the cart
    else{
        std::map<std::string, std::vector<Product*>>::iterator it = cartsMap.find(username);
        it->second.push_back(p);
    }

}

void MyDataStore::viewCart(std::string username){

    // Checks if username is valid
    if (!invalidUser(username)){
        std::cout << "Invalid request" << std::endl;
        return;
    }

    // Get cart associated with username
    std::vector<Product*>& cart = cartsMap[username];

    // Iterate over products in cart
    size_t index = 1;
    std::vector<Product*>::iterator it;
    for (it = cart.begin(); it != cart.end(); ++it){

        // Prints out item number and product details
        std::cout << "Items: " << index << ". \n" << (*it)->displayString() << std::endl;
        index++;
    }

}

void MyDataStore::buyCart(std::string username){

    // Find user in the usersMap
    map<string, User*>::iterator user = usersMap.find(username);

    // Find user's cart in the cartsMap
    map<string, vector<Product*>>::iterator cartIt = cartsMap.find(username);

    // If user and cart exist
    if (user != usersMap.end() && cartIt != cartsMap.end()) {
        
        // Retrieve user and cart
        User* currentUser = user->second;
        vector<Product*>& cart = cartIt->second;

        // Create a new cart for products
        vector<Product*> newCart;

        // Iterate through the products in the current cart
        for (vector<Product*>::iterator itProd = cart.begin(); itProd != cart.end(); ++itProd) {
          
            Product* product = *itProd;

            // Check if product in stock and user has enough balance
            if (product->getQty() > 0 && currentUser->getBalance() >= product->getPrice()) {

                // Deduct product's price from the user's balance and update quantity
                currentUser->deductAmount(product->getPrice());
                product->subtractQty(1);
            } 

            // Add product to new cart if it couldn't be bought
            else {
                newCart.push_back(product);
            }
        }

        // Update user's cart with new cart
        cartsMap[username] = newCart;
    }



}


MyDataStore::~MyDataStore(){

    std::map<std::string, User*>::iterator it;

    // Clean users memory
    for (it = usersMap.begin(); it != usersMap.end(); ++it){
        delete it->second;
    }

    // Clean products memory
    for (size_t i = 0; i < productsVector.size(); ++i){
        delete productsVector[i];
    }

}