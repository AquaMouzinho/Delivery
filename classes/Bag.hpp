#ifndef BAG_HPP
#define BAG_HPP

#include <map>
#include "Item.hpp"

class Bag {
public:
    Bag() {}
    ~Bag() {}

    void adicionarItem(Item &i) {
        itens.insert({i.getNome(), &i});
    }

    void removerItem(std::string key){
        itens.erase(key);
    }

    bool temItem(std::string key){
        return (itens.find(key) != itens.cend());
    }

    Item* getItem(std::string key) {
        return itens.find(key)->second;
    }

    int quantidadeDoItem(std::string key) {
        return itens.count(key);
    }
    
private:
    std::map<std::string, Item*> itens;
};
#endif