#ifndef FASEBANNER_HPP
#define FASEBANNER_HPP

#include "../ASCII_Engine/Fase.hpp"
#include "../ASCII_Engine/Sound.hpp"

#include <thread>
#include <unistd.h>
#include <termios.h>
using namespace std;

class FaseBanner : public Fase {
public:
    FaseBanner(std::string name, const Sprite &bkg) : Fase(name, bkg), keyPressed(false) {}
    FaseBanner(std::string name, const SpriteAnimado &bkg) : Fase(name, bkg), keyPressed(false) {}
    virtual ~FaseBanner() {}

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);

    bool isKeyPressed() const { return keyPressed; }
    void closeThreads();

private:
    ObjetoDeJogo *caixaDeTexto;
    
    bool keyPressed;
    unsigned tela_state;

    char entrada;
    thread banner_thread_;

    //métodos-membro
    static void runPlayerChannel(FaseBanner&);
};

#endif