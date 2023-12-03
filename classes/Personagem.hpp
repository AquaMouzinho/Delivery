#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <string>
#include <list>

#include "Ataque.hpp"
#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Personagem : public ObjetoDeJogo {
public:
    Personagem(const ObjetoDeJogo &obj) : ObjetoDeJogo(obj) {}
    Personagem(std::string nome, const ObjetoDeJogo &obj, int hp, int atk, int def, std::list<Ataque*> ataques) : ObjetoDeJogo(obj), nome(nome), money(0), max_hp(hp), current_hp(hp), atk(atk), def(def), sp(3), current_sp(0), current_pp(15), pp(15), status(0), ataques(ataques), vivo(true) {}
    Personagem(const ObjetoDeJogo &obj, std::string n, int m, int hp, int atk, int def, int sp, int pp, std::list<Ataque*> ataques) : ObjetoDeJogo(obj), nome(n), money(m), max_hp(hp), current_hp(hp), atk(atk), def(def), sp(sp), current_sp(0), pp(pp), status(0), ataques(ataques), vivo(true) {}
    virtual ~Personagem(){}

    bool isAlive() const {return vivo;}
    std::string getNome() const {return nome;}
    int getMoney() const {return money;}
    int getCurrentHPValue() const {return current_hp;}
    int getMAXHPValue() const {return max_hp;}
    int getAtkValue() const {return atk;}
    int getDefValue() const {return def;}
    int getCurrentSPValue() const {return current_sp;}
    int getMAXSPValue() const {return sp;}
    int getCurrentPPValue() const {return pp;}
    int getMAXPPValue() const {return pp;}
    int getStatusValue() const {return status;}
    std::list<Ataque*> getAtaques() const { return ataques; }

    void curarHP(int qtd = 0) { current_hp += qtd; }
    int receberDano(int dano = 0);
    void incrementMoney(int &value) {money += value;}
    void decrementMoney(int &value) {if(value <= money) money -= value;}
    void incrementPP() { current_pp++; }
    void decrementPP(int  dec = 1) { current_pp -= dec; }
    void incrementSP() { current_sp++; }
    void decrementSP(int  dec = 1) { current_sp -= dec; }

    void setCurrentHP(int novohp) { current_hp = novohp; }
    void setCurrentSP(int novosp) { current_sp = novosp; }
    void setCurrentPP(int novopp) { current_pp = novopp; }

private:
    bool vivo;
    std::string nome;
    int money, current_hp, max_hp, atk, def, current_sp, sp, current_pp, pp, status;
    std::list<Ataque*> ataques;
};

#endif