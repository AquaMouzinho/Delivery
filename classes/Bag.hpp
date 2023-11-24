#ifndef BAG_HPP
#define BAG_HPP

#include <map>
#include "Item.hpp"

class Bag {
public:
    Bag() {}
    ~Bag() {}

private:
    std::map<std::string, Item*> itens;
};
#endif