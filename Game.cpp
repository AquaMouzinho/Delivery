#include "ASCII_Engine/Sprite.hpp"
#include "ASCII_Engine/SpriteBuffer.hpp"
#include "ASCII_Engine/Fase.hpp"

#include "fases/FaseMenu.hpp"
#include "fases/FaseCriador.hpp"
#include "Game.hpp"

SpriteBuffer Game::screen(161, 40);

void Game::run(){
    FaseMenu fase("FaseMenu", Sprite("src/sprites/telas/menuBackground.img"));
    fase.init();
    unsigned state = Fase::MENU;
    unsigned level = Fase::LEVEL_1;
    while(state != Fase::END_GAME){
        switch (state)
        {
        case Fase::MENU:
            state = fase.run(screen);
            level = Fase::LEVEL_1;
            break;
        
        case Fase::OP_1:
            {
				if (level == Fase::LEVEL_1)
				{
					FaseCriador createPersona("CriadorPersona",Sprite("src/sprites/telas/telaPersonagem.img"));
					createPersona.init();
					state = createPersona.run(screen);
				} 
				else
					state = Fase::MENU;
			}
			break;
        case Fase::OP_2:
			system("clear");
			std::cout << "Saindo...\n";
			system("sleep 1");
			state = Fase::END_GAME;
			break;
        case Fase::LEVEL_COMPLETE:
            state = Fase::MENU;
            break;
		
        }
    }
    fase.closeThreads();
}