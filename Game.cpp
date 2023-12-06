#include "Game.hpp"

SpriteBuffer Game::screen(161, 40);

void Game::run(){
    Heroi *hero = new Heroi(ObjetoDeJogo("Heroi", Sprite("src/sprites/overworld/hero.img"),17,18), Bag());
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
                    level = Fase::MAPA;
				} 
				else {
					state = Fase::MENU;
                    level = Fase::CRIADOR_PERSONA;
                }
			}
			break;
        case Fase::OP_2:
            {
                FaseMundo worldMap("MapaMundi", Sprite("src/sprites/telas/worldBackground.img"), *hero);
                worldMap.init();
                state = worldMap.run(screen);
            }
            break;
        case Fase::LEVEL_1:
            {
                FaseBatalha level1("Level0", Sprite("src/sprites/telas/battleBackground.img"), Monstro(ObjetoDeJogo("Vilao1",Sprite("src/sprites/viloes/Scorpion.img"), 5, 60), "Scorpion", 100, 30, 7, 4, 4, 1, {new Ataque("Ferroada", 1, 0), new Ataque("Chuva de Presas", 4, 4)}), *hero);
                level1.init();
                state = level1.run(screen);
                level = Fase::LEVEL_2;
            }
            break;
        case Fase::LEVEL_2:
            {
                FaseBatalha level2("Level1", Sprite("src/sprites/telas/battleBackground.img"), Monstro(ObjetoDeJogo("Vilao2",Sprite("src/sprites/viloes/KillBee.img"), 5, 70), "Kill Bee", 100, 50, 10, 6, 4, 1, {new Ataque("Polén Queimante", 1, 0), new Ataque("Contra-Ataque", 6, 4)}), *hero);
                level2.init();
                state = level2.run(screen);
                level = Fase::LEVEL_3;
            }
            break;
        // case Fase::LEVEL_3:
        //     {
        //         FaseBatalha level1("Level3", Sprite("src/sprites/telas/battleBackground.img"), Monstro(ObjetoDeJogo("Vilao1",Sprite("src/sprites/viloes/Scorpion.img"), 20, 80)), *hero);
        //         level1.init();
        //         state = level1.run(screen);
        //         level = Fase:: LEVEL_5;
        //     }
        //     break;
        // case Fase::LEVEL_4:
        //     {
        //         FaseBatalha level1("Level4", Sprite("src/sprites/telas/battleBackground.img"), Monstro(ObjetoDeJogo("Vilao1",Sprite("src/sprites/viloes/Scorpion.img"), 20, 80)), *hero);
        //         level1.init();
        //         state = level1.run(screen);
        //     }
        //     break;
        case Fase::LEVEL_5:
            {
                FaseBatalha level3("Level2", Sprite("src/sprites/telas/battleBackground.img"), Monstro(ObjetoDeJogo("Vilao3",Sprite("src/sprites/viloes/KingBernatus.img"), 10, 60), "King Bern", 1000, 65, 6, 8, 4, 1, {new Ataque("Raio-Laser", 3, 0), new Ataque("Junta de Drones", 10, 4)}), *hero);
                level3.init();
                state = level3.run(screen);
            }
            break;
        case Fase::LEVEL_6:
            {
                FaseBatalha level4("Level3", Sprite("src/sprites/telas/battleBackground.img"), Monstro(ObjetoDeJogo("Vilao4",Sprite("src/sprites/viloes/Clowny.img"), 8, 80), "Fifaifi", 0, 80, 15, 10, 4, 1, {new Ataque("Cócegas", 2, 0), new Ataque("Ping-Pong", 15, 4)}), *hero);
                level4.init();
                state = level4.run(screen);
            }
            break;
        case Fase::LEVEL_7:
            {
                FaseBatalha level5("Level4", Sprite("src/sprites/telas/battleBackground.img"), Monstro(ObjetoDeJogo("Vilao5",Sprite("src/sprites/viloes/Fear.img"), 5, 70), "Fiero", 0, 75, 20, 20, 4, 1, {new Ataque("Suspiro Lacerante", 2, 0), new Ataque("Entranhas", 10, 4)}), *hero);
                level5.init();
                state = level5.run(screen);
            }
            break;
        case Fase::LEVEL_8:
            {
                FaseBatalha level6("Level5", Sprite("src/sprites/telas/battleBackground.img"), Monstro(ObjetoDeJogo("Vilao6",Sprite("src/sprites/viloes/Horns.img"), 8, 70),"Horns", 0, 100, 30, 20, 4, 1, {new Ataque("Laceração", 5, 0), new Ataque("Tira-Olhos", 8, 0), new Ataque("Mal Súbito", 25, 4)}), *hero);
                level6.init();
                state = level6.run(screen);
            }
            break;
        case Fase::OP_5:
			system("clear");
			std::cout << "Saindo...\n";
			system("sleep 1");
			state = Fase::END_GAME;
			break;
        case Fase::LEVEL_COMPLETE:
            hero->atualizarDados();
            state = Fase::OP_2;
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