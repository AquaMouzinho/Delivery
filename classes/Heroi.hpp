#ifndef HEROI_HPP
#define HEROI_HPP

#include "Arma.hpp"
#include "Bag.hpp"
#include "Personagem.hpp"

class Heroi : public Personagem {
public:
    Heroi(const ObjetoDeJogo &obj, const Bag &b) : Personagem(obj,10,5,5, {}), armaEquipada(nullptr), bagDoHeroi(b), yMapa(18), xMapa(17) {}
    ~Heroi() {
        delete armaEquipada;
    }
    
    int getXMapa() const { return xMapa; }
    int getYMapa() const { return yMapa; }
    void setXMapa(int x) { xMapa = x; }
    void setYMapa(int y) { yMapa = y; }

private:
    Arma *armaEquipada;
    Bag bagDoHeroi;
    int xMapa, yMapa;
};

#endif