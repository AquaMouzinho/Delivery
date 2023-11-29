#ifndef FASEMUNDO_HPP
#define FASEMUNDO_HPP

#include "../ASCII_Engine/Fase.hpp"
#include "../classes/Heroi.hpp"
#include "../classes/Portal.hpp"
#include "../classes/Dialog.hpp"

#include <thread>
#include <fstream>
#include <array>

class FaseMundo : public Fase {
public:
    FaseMundo(std::string name, const Sprite &bkg, const Heroi &heroi) : Fase(name, bkg), hero(heroi) {}
    virtual ~FaseMundo() {}

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);

    bool isKeyPressed() const { return keyPressed; }
    void closeThreads();

private:
    Heroi hero;
    ObjetoDeJogo *sprtHero, *placa;
    Dialog *caixaDeTexto;
    Portal *fases[9];
    SpriteBase *txtFaseNome, *txtQtdHP, *txtQtdPP;

    bool keyPressed;
    unsigned op, tela_state, tela;

    char entrada;
    std::thread mundo_thread_;

    std::array<std::array<int, 160>, 40> mapaColisao;

    bool leitorMapa(std::string file, std::array<std::array<int, 160>, 40> &mapa);
    static void runPlayerChannel(FaseMundo &);
};

#endif