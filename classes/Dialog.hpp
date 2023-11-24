#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <string>
#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Dialog : public ObjetoDeJogo {
public:
    Dialog(const ObjetoDeJogo &obj) : ObjetoDeJogo(obj) {}
    virtual ~Dialog() {}

    void show() const;
private:
    int width, length, velocidadeTexto;
    std::string texto;
};

#endif