#include "clothing.h"
#include "util.h"
#include <sstream>
//added 
#include <iomanip>

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) 
 : Product (category, name, price, qty),
  size_ (size),
  brand_ (brand)


 {
 } 
 
std::set<std::string> Clothing::keywords() const {
 
    std::set<std::string> nameWords;
    nameWords = parseStringToWords(name_);

    std::set<std::string> brandWords;
    brandWords = parseStringToWords(brand_);

    std::set<std::string> result = setUnion(nameWords, brandWords); //combine name & brand keywords

    return result; 
}

std::string Clothing::displayString() const {
    std::stringstream ss;

    ss <<  name_ << "\n";
    ss << "Size: " << size_ << " Brand: " << brand_ << "\n";

    //added 
    ss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";

    return ss.str();
}

void Clothing::dump(std::ostream& os) const {
    Product::dump(os); 

    os << size_ << "\n";
    os << brand_ << "\n";
}