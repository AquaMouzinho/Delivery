#include "ASCII_Engine/Sprite.hpp"
#include "ASCII_Engine/SpriteBuffer.hpp"
#include "ASCII_Engine/Fase.hpp"

#include "fases/FaseMenu.hpp"
#include "fases/FaseMundo.hpp"
#include "fases/FaseCriador.hpp"
#include "classes/Heroi.hpp"
#include "Game.hpp"

SpriteBuffer Game::screen(161, 40);

void Game::run(){
    Heroi hero(ObjetoDeJogo("Heroi", Sprite("src/sprites/overworld/hero.img"),17,18), Bag());
    FaseMenu fase("FaseMenu", Sprite("src/sprites/telas/menuBackground.img"));
    fase.init();
    unsigned state = Fase::MENU;
    unsigned level = Fase::CRIADOR_PERSONA;
    while(state != Fase::END_GAME){
        switch (state)
        {
        case Fase::MENU:
            state = fase.run(screen);
            level = Fase::CRIADOR_PERSONA;
            break;
        
        case Fase::OP_1:
            {
				if (level == Fase::CRIADOR_PERSONA)
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
            {
                FaseMundo worldMap("MapaMundi", Sprite("src/sprites/telas/worldBackground.img"), hero);
                worldMap.init();
                state = worldMap.run(screen);
            }
            break;
        case Fase::OP_5:
			system("clear");
			std::cout << "Saindo...\n";
			system("sleep 1");
			state = Fase::END_GAME;
			break;
        case Fase::LEVEL_COMPLETE:
            state = Fase::MENU;
            break;
        default:
            {
                state = Fase::MENU;
            }
            break;
        }
    }
    fase.closeThreads();
}