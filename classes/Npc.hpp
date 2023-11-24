#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include <list>

#include "../ASCII_Engine/ObjetoDeJogo.hpp"
#include "Dialog.hpp"

class Npc : public ObjetoDeJogo {
public:
    Npc(const ObjetoDeJogo &obj) : ObjetoDeJogo(obj) {}
    virtual ~Npc(){}

    void apresentarTexto(Dialog &) const;
private:
    std::string nome;
    std::list<std::string> texto;
};

#endif