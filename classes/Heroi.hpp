#ifndef HEROI_HPP
#define HEROI_HPP

#include "Arma.hpp"
#include "Bag.hpp"
#include "Personagem.hpp"

#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class Heroi : public Personagem {
public:
    Heroi(const ObjetoDeJogo &obj, const Bag &b, std::string nome = "Nimbus") : Personagem(nome, obj,50,5,5, {new Ataque("Ataque N", 0, 0), new Ataque("Ataque C", 2, 1), new Ataque("Supremo", 5, 3)}), armaEquipada(nullptr), bagDoHeroi(new Bag(b)), yMapa(18), xMapa(17), fasesConcluidas(6, 0) {}
    ~Heroi() {
        delete armaEquipada;
    }
    
    int getXMapa() const { return xMapa; }
    int getYMapa() const { return yMapa; }
    Bag* getBag() const { return bagDoHeroi; }
    Arma* getArma() const { return armaEquipada; }

    void setXMapa(int x) { xMapa = x; }
    void setYMapa(int y) { yMapa = y; }
    void equiparArma(Arma *pArma) { armaEquipada = pArma;}
    void desequiparArma() { armaEquipada = nullptr;}

    bool salvarDados();
    bool atualizarDados();

    vector<int> fasesConcluidas;

private:
    Arma *armaEquipada;
    Bag *bagDoHeroi;
    int xMapa, yMapa;
};

#endif