#ifndef DOOR_HP
#define DOOR_HP

#include "../ASCII_Engine/ObjetoDeJogo.hpp"

class Door : public ObjetoDeJogo {
public:
    Door(const ObjetoDeJogo &obj, bool aberto = false) : ObjetoDeJogo(obj) { setIsAberto(aberto); }
    virtual ~Door() {}

    bool isAberto() const {return aberto;}
    void setIsAberto(bool situ) { aberto = situ; if(situ) ObjetoDeJogo::update();}

    virtual void update() {}
    
private:
    bool aberto;
};
#endif