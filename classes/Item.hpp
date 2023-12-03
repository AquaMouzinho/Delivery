#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {
public:
    Item(std::string nome, std::string descricao) : nome(nome), descricao(descricao) {}
    ~Item(){}

private:
    std::string nome, descricao;
};

#endif