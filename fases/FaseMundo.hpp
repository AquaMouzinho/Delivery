#ifndef FASEMUNDO_HPP
#define FASEMUNDO_HPP

#include "../ASCII_Engine/Fase.hpp"
#include "../classes/Heroi.hpp"
#include "../classes/Portal.hpp"
#include "../classes/Npc.hpp"
#include "../classes/Chest.hpp"
#include "../classes/Door.hpp"
#include "../classes/Dialog.hpp"

#include <thread>
#include <fstream>
#include <array>

class FaseMundo : public Fase {
public:
    FaseMundo(std::string name, const Sprite &bkg, Heroi &heroi) : Fase(name, bkg), hero(heroi){}
    virtual ~FaseMundo() {}

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);

    bool isKeyPressed() const { return keyPressed; }
    void closeThreads();

private:
    Heroi hero;
    ObjetoDeJogo *sprtHero, *placa, *caixaDeTexto, *caixaConfirmar;
    //Dialog ;
    Door *porta;
    Chest *caixa;
    Portal *fases[9];
    Npc *person;
    SpriteBase *txtFaseNome, *txtQtdHP, *txtQtdPP, *barraHP;

    bool keyPressed;
    unsigned op, tela_state, tela;
    char entrada;
    std::thread mundo_thread_;

    std::array<std::array<int, 160>, 40> mapaColisao;

    bool leitorMapa(std::string file, std::array<std::array<int, 160>, 40> &mapa);
    static void runPlayerChannel(FaseMundo &);
    std::string replicador(std::string carac, int qtd);
};

#endif