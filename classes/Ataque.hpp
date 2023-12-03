#ifndef ATAQUE_HPP
#define ATAQUE_HPP

#include <string>

class Ataque {
public:
    Ataque(std::string nome, int dano, int custo) : nomeAtaque(nome), danoFisico(dano), custoSP(custo) {}
    ~Ataque() {}
    
    std::string getNome() const { return nomeAtaque; }
    int getDano() const { return danoFisico; }
    int getCusto() const { return custoSP; }

private:
    std::string nomeAtaque;
    int danoFisico, custoSP;    
};
#endif