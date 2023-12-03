#ifndef MONSTRO_HPP
#define MONSTRO_HPP

#include "Personagem.hpp"

class Monstro :public Personagem {
public:
    Monstro(const ObjetoDeJogo &obj) : Personagem(obj) {}
    Monstro(const ObjetoDeJogo &obj, std::string nome, int m, int hp, int atk, int def, int sp, int pp, std::list<Ataque*> ataques) : Personagem(obj, nome, m, hp, atk, def, sp, pp, ataques) {}
    virtual ~Monstro() {}
private:
    
};

#endif