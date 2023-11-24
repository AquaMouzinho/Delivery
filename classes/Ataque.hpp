#ifndef ATAQUE_HPP
#define ATAQUE_HPP

#include <string>

class Ataque {
public:
    Ataque(std::string nome, int dano) : nomeAtaque(nome), danoFisico(dano) {}
    ~Ataque() {}
    
private:
    std::string nomeAtaque;
    int danoFisico;    
};
#endif