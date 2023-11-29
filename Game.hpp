#ifndef GAME_HPP
#define GAME_HPP

#include "ASCII_Engine/SpriteBuffer.hpp"
#include "classes/Heroi.hpp"

class Game
{
public:
    Game(){}

    static void run();
private:
    static SpriteBuffer screen;
};

#endif