#ifndef FASEBATALHA_HPP
#define FASEBATALHA_HPP

#include "../ASCII_Engine/Fase.hpp"
#include "../classes/Monstro.hpp"
#include "../classes/Heroi.hpp"

#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
using namespace std;

class FaseBatalha : public Fase {
public:
    FaseBatalha(std::string name, const Sprite &bkg, const Monstro &m, const Heroi &h) : Fase(name, bkg), vilao(new Monstro(m)), keyPressed(false), opTela(false), heroi(new Heroi(h)) {}
    virtual ~FaseBatalha() {}

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);

    bool isKeyPressed() const { return keyPressed; }
    void closeThreads();

private:
    // Objetos Aparentes na tela
    Heroi *heroi;
    Monstro *vilao;
    ObjetoDeJogo *pSelE, *pSelD, *pSelPopUp, *popUp;
    std::list<ObjetoDeJogo*> ataques;
    SpriteBase *txtNomeVilao, *txtQtdHPAtualVilao, *txtQtdHPVilao, *txtQtdPPAtualVilao, *txtNomeGolpe;
    SpriteBase *txtNomeHeroi, *txtQtdHPAtualHeroi, *txtQtdHPMaxHeroi, *txtQtdSPAtualHeroi, *txtQtdSPMaxHeroi, *txtQtdPPAtualHeroi;

    // variáveis internas
    Ataque* ataqueEscolhido;
    bool keyPressed, opTela;
    unsigned op, op2, tela_state, tela;

    char entrada;
    thread batalha_thread_;

    //métodos-membro
    static void runPlayerChannel(FaseBatalha &);
    Ataque* getAtaque(list<Ataque*> lista, unsigned i);
    void handleVillainAttack();
};

#endif