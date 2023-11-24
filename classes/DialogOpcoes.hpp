#ifndef DIALOGOPCOES_HPP
#define DIALOGOPCOES_HPP

#include <string>
#include <list>
#include "Dialog.hpp"

class DialogComOpcoes : public Dialog {
public:
    DialogComOpcoes(const ObjetoDeJogo &obj) : Dialog(obj) {}
    virtual ~DialogComOpcoes(){}

    int showChoices() const; // Retorna int da opcao escolhida
private:
    std::list<std::string> opcoes;
};

#endif