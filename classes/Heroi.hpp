#ifndef HEROI_HPP
#define HEROI_HPP

#include "Arma.hpp"
#include "Bag.hpp"
#include "Personagem.hpp"

class Heroi : public Personagem {
public:
    Heroi(const ObjetoDeJogo &obj, const Bag &b) : Personagem(obj), armaEquipada(nullptr), bagDoHeroi(b) {}
    ~Heroi() {
        delete armaEquipada;
    }
    
private:
    Arma *armaEquipada;
    Bag bagDoHeroi;
};

#endif