#include "Personagem.hpp"

int Personagem::receberDano(int dano) {
    current_hp -= dano;
    if(current_hp <= 0) vivo = false; 
    return dano;
}