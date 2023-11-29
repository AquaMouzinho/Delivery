#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <string>
#include <list>

#include "Ataque.hpp"
#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Personagem : public ObjetoDeJogo {
public:
    Personagem(const ObjetoDeJogo &obj) : ObjetoDeJogo(obj) {}
    Personagem(const ObjetoDeJogo &obj, int hp, int atk, int def, std::list<Ataque*> ataques) : ObjetoDeJogo(obj), nome("Nimbus"), money(0), max_hp(hp), current_hp(hp), atk(atk), def(def), sp(3), current_sp(0), pp(10), status(0), ataques(ataques) {}
    Personagem(const ObjetoDeJogo &obj, std::string n, int m, int hp, int atk, int def, int sp, int pp, std::list<Ataque*> ataques) : ObjetoDeJogo(obj), nome(n), money(m), max_hp(hp), current_hp(hp), atk(atk), def(def), sp(sp), current_sp(0), pp(pp), status(0), ataques(ataques) {}
    virtual ~Personagem(){}

    //virtual int receberDano();

    std::string getNome() const {return nome;}
    int getMoney() const {return money;}
    int getCurrentHPValue() const {return current_hp;}
    int getMAXHPValue() const {return max_hp;}
    int getAtkValue() const {return atk;}
    int getDefValue() const {return def;}
    int getCurrentSPValue() const {return current_sp;}
    int getSPValue() const {return sp;}
    int getPPValue() const {return pp;}
    int getStatusValue() const {return status;}

    void incrementMoney(int &value) {money += value;}
    void decrementMoney(int &value) {if(value <= money) money -= value;}

private:
    std::string nome;
    int money, current_hp, max_hp, atk, def, current_sp, sp, pp, status;
    std::list<Ataque*> ataques;
};

#endif