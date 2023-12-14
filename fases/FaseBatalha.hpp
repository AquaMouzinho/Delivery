#ifndef FASEBATALHA_HPP
#define FASEBATALHA_HPP

#include "../ASCII_Engine/Fase.hpp"
#include "../classes/Monstro.hpp"
#include "../classes/Heroi.hpp"
#include "../classes/Pocao.hpp"
#include "../ASCII_Engine/Sound.hpp"

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
    std::list<ObjetoDeJogo*> ataques, pocoes;

    ObjetoDeJogo *qtdPocoesHP, *pSelE, *pSelD, *pSelPopUp, *popUp, *txtNomeAbaPopUp, *caixaContinuar;
    SpriteBase *txtNomeVilao, *txtQtdHPAtualVilao, *barraHPVilao, *txtQtdHPVilao, *txtQtdPPAtualVilao, *txtNomeGolpe;
    SpriteBase *txtNomeHeroi, *txtQtdHPAtualHeroi, *barraHPHeroi, *txtQtdHPMaxHeroi, *txtQtdSPAtualHeroi, *txtQtdSPMaxHeroi, *txtQtdPPAtualHeroi;

    // variáveis internas
    Ataque* ataqueEscolhido;
    Pocao* pocaoEscolhida;
    bool keyPressed, opTela;
    unsigned op, op2, tela_state, tela;

    char entrada;
    thread batalha_thread_;

    //métodos-membro
    static void runPlayerChannel(FaseBatalha &);
    Ataque* getAtaque(list<Ataque*> lista, unsigned i);
    void handleVillainAttack();
    std::string replicador(std::string caractere, int qtd);
};

#endif