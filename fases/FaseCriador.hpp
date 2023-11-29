#ifndef CRIADORPERSONA_HPP
#define CRIADORPERSONA_HPP

#include "../ASCII_Engine/Fase.hpp"
#include "../ASCII_Engine/Sprite.hpp"
#include "../ASCII_Engine/SpriteBase.hpp"
#include "../ASCII_Engine/SpriteBuffer.hpp"

#include "../classes/Heroi.hpp"

#include <string>
#include <array>
#include <thread>

class FaseCriador : public Fase {
public:
    FaseCriador(std::string name, const Sprite &obj) : Fase(name, obj), keyPressed(false) {}
    virtual ~FaseCriador() {}

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);

    void closeThreads();
    bool isKeyPressed() const {return keyPressed;}
    bool isMudarTraco() const {return mudarTraco;}

private:
    char entrada;
    bool keyPressed, mudarTraco;
    unsigned tela_state, linhaMenu, colunaMenu;
    std::array<int, 5> listaTracos;
    std::thread tela_thread_;

    ObjetoDeJogo *pSelOpE, *pSelOpD;

    SpriteBase *txtOpCabelo, *txtOpOlho, *txtOpNariz, *txtOpAdicional, *txtOpCorpo;
    SpriteBase *sprtCabelo, *sprtOlho, *sprtNariz, *sprtAdicional, *sprtCorpo, *sprtFront;

    static void openPlayerChannel(FaseCriador&);
    bool salvarSpriteHeroi();
};
#endif