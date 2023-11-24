#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <string>
#include <list>

#include "Ataque.hpp"
#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Personagem : public ObjetoDeJogo {
public:
    Personagem(const ObjetoDeJogo &obj) : ObjetoDeJogo(obj) {}
    virtual ~Personagem(){}

    virtual int receberDano();

    std::string getNome() const {return nome;}
    int getMoney() const {return money;}
    int getCurrentHPValue() const {return current_hp;}
    int getMAXHPValue() const {return max_hp;}
    int getAtkValue() const {return atk;}
    int getDefValue() const {return def;}
    int getSPValue() const {return sp;}
    int getPPValue() const {return pp;}
    int getStatusValue() const {return status;}

    void incrementMoney(int &value) {money += value;}
    void decrementMoney(int &value) {if(value <= money) money -= value;}

private:
    std::string nome;
    int money, current_hp, max_hp, atk, def, current_sp, pp, status;
    std::list<Ataque*> ataques;
};

#endif