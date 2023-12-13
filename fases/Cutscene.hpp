#ifndef CUTSCENE_HPP
#define CUTSCENE_HPP

#include "../ASCII_Engine/Fase.hpp"
#include "../ASCII_Engine/Sprite.hpp"
#include "../ASCII_Engine/SpriteAnimado.hpp"

#include <unistd.h>
#include <termios.h>
#include <thread>
#include <fstream>
#include <ios>
using namespace std;

class Cutscene : public Fase {
public:
    Cutscene(std::string name, std::string pastaCenas, const Sprite &bkg) : Fase(name, bkg), keyPressed(false), urlCenas(pastaCenas) {}
    Cutscene(std::string name, std::string pastaCenas, const SpriteAnimado &bkg) : Fase(name, bkg), keyPressed(false), urlCenas(pastaCenas) {}
    virtual ~Cutscene() {}

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);

    bool isKeyPressed() const { return keyPressed; }
    void closeThreads();

private:
    std::string urlCenas;
    std::list<std::string> falas, falasSegunda;
    
    ObjetoDeJogo *caixaDeTexto;
    SpriteBase *imgCutscene, *txtNomePersonagem, *txtPrimeiraLinha, *txtSegundaLinha;

    bool keyPressed;
    unsigned tela_state, iterador_cenas;

    char entrada;
    thread scene_thread_;

    //métodos-membro
    static void runPlayerChannel(Cutscene&);
};

#endif