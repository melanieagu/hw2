#include "book.h"
#include "util.h"
#include <sstream>
//added 
#include <iomanip>

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) 
 : Product (category, name, price, qty),
  isbn_ (isbn),
  author_ (author)


 {
 } 
 
std::set<std::string> Book::keywords() const {
 
    std::set<std::string> nameWords;
    nameWords = parseStringToWords(name_);

    std::set<std::string> authorWords;
    authorWords = parseStringToWords(author_);

    std::set<std::string> result = setUnion(nameWords, authorWords); //combine name & author keywords
    result.insert(isbn_);

    return result; 
}

std::string Book::displayString() const {
    std::stringstream ss;

    ss <<  name_ << "\n";
    ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";

    //added 
    ss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Book::dump(std::ostream& os) const {
    Product::dump(os); 

    os << isbn_ << "\n";
    os << author_ << "\n";
}



