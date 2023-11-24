#ifndef FASEMENU_HPP
#define FASEMENU_HPP

#include "../ASCII_Engine/ObjetoDeJogo.hpp"
#include "../ASCII_Engine/Fase.hpp"
#include "../ASCII_Engine/Sprite.hpp"
#include "../ASCII_Engine/SpriteBuffer.hpp"

#include <chrono>
#include <thread>
using std::thread, std::ref;

class FaseMenu : public Fase {
public:
    FaseMenu(std::string name, const Sprite &bkg) : Fase(name, bkg), keyPressed(false){}
    virtual ~FaseMenu() {}

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);

    bool isKeyPressed() const { return keyPressed; }
    
    void closeThreads();

private:
    ObjetoDeJogo *pSel;
    unsigned op, gameState, tela;

    char entrada;
    bool keyPressed;
    thread menu_thread_;

    static void runPlayerChannel(FaseMenu &);
};

#endif