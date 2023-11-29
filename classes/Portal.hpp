#ifndef PORTAL_HPP
#define PORTAL_HPP

#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Portal : public ObjetoDeJogo {
public:
    Portal(const ObjetoDeJogo &obj, unsigned e) : ObjetoDeJogo(obj), enumeracao(e), completado(false) {}
    virtual ~Portal() {}

    unsigned getEnumeracao() const { return enumeracao; }
    bool getCompletado() const { return completado;}
    void setCompletado(bool c) { completado = c; }

    virtual void update() {}
private:
    bool completado;
    unsigned enumeracao;
};

#endif