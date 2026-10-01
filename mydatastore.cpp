#include "mydatastore.h"
#include "util.h"
#include <iostream>

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
    std::vector<Product*>::iterator it;
    //begin at the first product and iterate till the end but continue going thru each product 
    for (it = products_.begin(); it != products_.end(); ++it){
        delete *it;
    }

    //users is a map 
    std::map<std::string, User*>::iterator it2;
    for (it2 = users_.begin(); it2 != users_.end(); ++it2) {
        delete it2->second;
    }
}

    void MyDataStore::addProduct(Product* p) {
        products_.push_back(p);
        std::set<std::string> keys = p->keywords();

        std::set<std::string>::iterator it;

    for (it = keys.begin(); it != keys.end(); ++it)
    {
        keywordMap_[*it].insert(p);
    }

}

void MyDataStore::addUser(User* u) {
    std::string username = convToLower(u->getName());
    users_[username] = u; 
    carts_[username] = std::vector<Product*>();
}

std::vector<Product*>MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::set<Product*>result;
    std::vector<std::string>::iterator it3;
    for (it3=terms.begin(); it3 != terms.end(); ++it3) {
        std::string term = convToLower(*it3);

    if (keywordMap_.find(term) != keywordMap_.end()){
        if (it3 == terms.begin()){
            result = keywordMap_[term];
        }
    
    else {
        if (type==0) {
            result = setIntersection(result, keywordMap_[term]);
        }
    else if (type ==1) {
        result = setUnion(result,keywordMap_[term]);
        }
    }
    }
    else if(type==0){
        result.clear();
    }
    }

    std::vector<Product*> hits;
    std::set<Product*>::iterator it4;

    for (it4 = result.begin(); it4 != result.end(); ++it4){
        hits.push_back(*it4);
    }
    return hits;
}

void MyDataStore::dump(std::ostream& ofile){
        ofile << "<products>" << std::endl;

        std::vector<Product*>::iterator it5; 

        for (it5 = products_.begin(); it5 != products_.end();++it5) {
            (*it5)->dump(ofile);
        }
        ofile << "</products>" << std::endl;

        ofile << "<users>" << std::endl;
        std::map<std::string, User*>::iterator it6;
        //loop thru users and dump each user 

        for (it6 = users_.begin(); it6 != users_.end(); ++it6) {
            it6->second->dump(ofile);
        }
        ofile << "</users>" << std::endl;
        

    }

void MyDataStore::addToCart(std::string username, Product* p) {
        username = convToLower(username);

        //check whether user exists 
        if (users_.find(username) == users_.end()) {
            std::cout << "Invalid request" << std::endl; 
            return; 
        }
        carts_[username].push_back(p); //FIFO since each new product is placed at end of vector 

    }


void MyDataStore::viewCart(std::string username) { //check whether users exist 
    username = convToLower(username);

    if (users_.find(username) == users_.end()) {
        std::cout << "Invalid username" << std::endl; 
        return;
    } 

    std::vector<Product*>::iterator it7;
    int itemNumber = 1; 
    for (it7 = carts_[username].begin(); it7 != carts_[username].end();++it7) {
            std::cout << "Item " << itemNumber << std::endl;
            std::cout << (*it7)->displayString() << std::endl;
            itemNumber++;
    }

}

void MyDataStore::buyCart(std::string username) {
    username = convToLower(username);

    if (users_.find(username) == users_.end()) {
        std::cout << "Invalid username" << std::endl; 
        return;
    }
    User* user = users_[username];

    std::vector<Product*> left;
    std::vector<Product*>::iterator it8;

    for (it8 = carts_[username].begin(); it8 != carts_[username].end();++it8) {
            Product* product = *it8;

        if (product->getQty() > 0 && user->getBalance() >= product->getPrice()) {
          //purchase occurs so remove prod from inv and remove $ from users bal 
          product->subtractQty(1); 
          user->deductAmount(product->getPrice());
        }
        else {
            //purchase remains in cart 
            left.push_back(product); 
        }
        
    }
    carts_[username] = left; 

}










    

