#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Item : public ObjetoDeJogo {
public:
    Item(const ObjetoDeJogo &obj) : ObjetoDeJogo(obj) {}
    virtual ~Item(){}
private:
    std::string nome, descricao;
};

#endif