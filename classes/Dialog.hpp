#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <string>
#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Dialog : public ObjetoDeJogo {
public:
    Dialog(ObjetoDeJogo &obj, std::string texto = "", unsigned width = 3, unsigned length = 3);
    virtual ~Dialog() {}

    bool isAtivado() const { return ativado;}
    void switchAtivado() { ativado = !ativado;}
private:
    bool ativado;
    unsigned width, length, velocidadeTexto;
    std::string texto;

    bool constroiDialog();
    std::string particionaString(std::string &obj, unsigned int inicio, unsigned int fim);
};

#endif