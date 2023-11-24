#ifndef MONSTRO_HPP
#define MONSTRO_HPP

#include "Personagem.hpp"

class Monstro :public Personagem {
public:
    Monstro(const ObjetoDeJogo &obj) : Personagem(obj) {}
    virtual ~Monstro() {}
private:
    
};

#endif