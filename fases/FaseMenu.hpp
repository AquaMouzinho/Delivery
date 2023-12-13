#ifndef FASEMENU_HPP
#define FASEMENU_HPP

#include "../ASCII_Engine/ObjetoDeJogo.hpp"
#include "../ASCII_Engine/Fase.hpp"
#include "../ASCII_Engine/Sprite.hpp"
#include "../ASCII_Engine/SpriteAnimado.hpp"
#include "../ASCII_Engine/SpriteBuffer.hpp"

#include <chrono>
#include <thread>
using std::thread, std::ref;

class FaseMenu : public Fase {
public:
    FaseMenu(std::string name, const Sprite &bkg) : Fase(name, bkg), keyPressed(false), helpAparecendo(false) {}
    FaseMenu(std::string name, const SpriteAnimado &bkg) : Fase(name, bkg), keyPressed(false), helpAparecendo(false) {}
    virtual ~FaseMenu() {}

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);

    bool isKeyPressed() const { return keyPressed; }
    int getVezes() const { return vezes; }
    void closeThreads();

private:
    ObjetoDeJogo *pSel, *help;
    SpriteBase *txtOpNovo;
    unsigned op, gameState, tela;

    int vezes;
    char entrada;
    bool keyPressed, helpAparecendo;
    thread menu_thread_;

    static void runPlayerChannel(FaseMenu &);
    void vezesRodado() { ++vezes; }
};

#endif