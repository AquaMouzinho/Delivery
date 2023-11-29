#ifndef ARMA_HPP
#define ARMA_HPP

#include "Item.hpp"

class Arma : public Item{
public:
    Arma(const ObjetoDeJogo &obj) : Item(obj) {}
    ~Arma(){}

    int getDanoFisico() const {return danoFisico;}
private:
    int danoFisico;
};
#endif