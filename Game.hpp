#ifndef GAME_HPP
#define GAME_HPP

#include "ASCII_Engine/Sprite.hpp"
#include "ASCII_Engine/SpriteBuffer.hpp"
#include "ASCII_Engine/Fase.hpp"

#include "fases/FaseMenu.hpp"
#include "fases/FaseMundo.hpp"
#include "fases/FaseCriador.hpp"
#include "fases/FaseBatalha.hpp"
#include "fases/Cutscene.hpp"

#include "classes/Heroi.hpp"

#include <iomanip>

class Game
{
public:
    Game(){}

    static void run();
private:
    static SpriteBuffer screen;
};

#endif