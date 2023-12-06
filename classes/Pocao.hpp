#ifndef POCAO_HPP
#define POCAO_HPP

#include "Item.hpp"

class Pocao :public Item {
public:
    Pocao(const Item &obj, bool hpPP = true, int qtd = 1) : Item(obj), qtdDeCura(1), hpOuPP(hpPP) {}
    virtual ~Pocao() {}
    
private:
    bool hpOuPP; //hp = true | pp = false
    int qtdDeCura;

};
#endif