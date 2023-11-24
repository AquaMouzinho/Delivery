#ifndef POCAO_HPP
#define POCAO_HPP

#include "Item.hpp"

class Pocao :public Item {
public:
    Pocao(const ObjetoDeJogo &obj) : Item(obj) {}
    virtual ~Pocao() {}
private:
    int qtdDeCura;
};
#endif