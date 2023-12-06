#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include <list>

#include "../ASCII_Engine/ObjetoDeJogo.hpp"
#include "Dialog.hpp"

class Npc : public ObjetoDeJogo {
public:
    Npc(const ObjetoDeJogo &obj, std::string nome = "", std::string texto = "") : ObjetoDeJogo(obj), nome(nome), texto(texto) {}
    virtual ~Npc(){}

    //void apresentarTexto(const Dialog &) const;
private:
    std::string nome, texto;
};

#endif