#ifndef ARMA_HPP
#define ARMA_HPP

#include "Item.hpp"

class Arma : public Item{
public:
    Arma(std::string nome, std::string descricao, int dano) : Item(nome, descricao), danoFisico(dano) {}
    ~Arma(){}

    int getDanoFisico() const {return danoFisico;}
    
private:
    std::string nome, descricao;
    int danoFisico;
};
#endif