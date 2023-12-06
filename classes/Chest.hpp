#ifndef CHEST_HPP
#define CHEST_HPP

#include "../ASCII_Engine/ObjetoDeJogo.hpp"
#include "Item.hpp"

class Chest : public ObjetoDeJogo {
public:
    Chest(const ObjetoDeJogo &obj, const Item &item) : ObjetoDeJogo(obj), aberto(false), presente(new Item(item)){}
    virtual ~Chest() {}

    bool getAberto() const { return aberto; }
    void setAberto(bool situ) { aberto = situ; }

    Item* getItem() const { return presente; }

private:
    bool aberto;
    Item *presente;
};

#endif 