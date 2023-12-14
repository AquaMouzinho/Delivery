#include "Game.hpp"

SpriteBuffer Game::screen(161, 40);

void Game::run(){
    Heroi *hero = new Heroi(ObjetoDeJogo("Heroi", Sprite("src/sprites/overworld/hero.img"),17,18), Bag());
    Pocao p(Item("PocaoHP","Pocao para HP"),true,1);
    FaseMenu fase("FaseMenu", SpriteAnimado("src/sprites/telas/menuAnimacao.anm"));
    fase.init();
    unsigned state = Fase::MENU;
    unsigned level = Fase::CRIADOR_PERSONA;
    while(state != Fase::END_GAME){
        switch (state)
        {
        case Fase::MENU:
            {
                state = fase.run(screen);
                level = Fase::CRIADOR_PERSONA;
            }
            break;
        
        case Fase::OP_1:
            {
                if(fase.getVezes() < 2){
                    if (level == Fase::CRIADOR_PERSONA)
                    {
                        Cutscene c1("Cutscene1", "src/sprites/cutscenes/scene_inicial", Sprite("src/sprites/telas/bkgCutscene.img"));
                        c1.init();
                        c1.run(screen);

                        FaseCriador createPersona("CriadorPersona",Sprite("src/sprites/telas/telaPersonagem.img"));
                        createPersona.init();
                        state = createPersona.run(screen);
                        level = Fase::LEVEL_1;

                        Cutscene c2("Cutscene2", "src/sprites/cutscenes/scene_inicial_2", Sprite("src/sprites/telas/bkgCutscene.img"));
                        c2.init();
                        c2.run(screen);
                    } 
                    else {
                        state = Fase::MENU;
                        level = Fase::CRIADOR_PERSONA;
                    }
                }else {
                    state = Fase::MAPA;
                }
			}
			break;
        case Fase::MAPA:
            {
                FaseMundo worldMap("MapaMundi", Sprite("src/sprites/telas/worldBackground.img"), *hero);
                worldMap.init();
                state = worldMap.run(screen);
                hero->atualizarDados();
            }
            break;
        case Fase::LEVEL_1:
            {
                FaseBatalha level1("Level0", Sprite("src/sprites/telas/battleBackground.img"), Monstro(ObjetoDeJogo("Vilao1",Sprite("src/sprites/viloes/Scorpion.img"), 7, 65), "Scorpion", 100, 30, 7, 4, 4, 1, {new Ataque("Ferroada", 1, 0), new Ataque("Chuva de Presas", 4, 4)}), *hero);
                level1.init();
                state = level1.run(screen);

                if(state == Fase::LEVEL_COMPLETE){
                    level = Fase::LEVEL_2;
                    //hero->equiparArma(new Arma("Espada", "Uma espada" , 20));
                    Cutscene c1Conc("Cutscene1Conc", "src/sprites/cutscenes/scene_inicial_final", Sprite("src/sprites/telas/bkgCutscene.img"));
                    c1Conc.init();
                    c1Conc.run(screen);
                }
            }
            break;
        case Fase::LEVEL_2:
            {
                hero->equiparArma(new Arma("Teste", "teste", 20));
                FaseBatalha level2("Level1", Sprite("src/sprites/telas/battleBackground.img"), Monstro(ObjetoDeJogo("Vilao2",Sprite("src/sprites/viloes/KillBee.img"), 5, 70), "Kill Bee", 100, 50, 10, 6, 4, 1, {new Ataque("Polén Queimante", 1, 0), new Ataque("Contra-Ataque", 6, 4)}), *hero);
                level2.init();
                state = level2.run(screen);
                hero->desequiparArma();
                if(state == Fase::LEVEL_COMPLETE) level = Fase::LEVEL_5;
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
                hero->equiparArma(new Arma("Teste", "teste", 20));
                FaseBatalha level3("Level2", Sprite("src/sprites/telas/battleBackground.img"), Monstro(ObjetoDeJogo("Vilao3",Sprite("src/sprites/viloes/KingBernatus.img"), 10, 60), "King Bern", 1000, 65, 6, 8, 4, 1, {new Ataque("Raio-Laser", 3, 0), new Ataque("Junta de Drones", 10, 4)}), *hero);
                level3.init();
                state = level3.run(screen);
                hero->desequiparArma();
                if(state == Fase::LEVEL_COMPLETE) level = Fase::LEVEL_6;
            }
            break;
        case Fase::LEVEL_6:
            {
                hero->equiparArma(new Arma("Teste", "teste", 30));
                FaseBatalha level4("Level3", Sprite("src/sprites/telas/battleBackground.img"), Monstro(ObjetoDeJogo("Vilao4",Sprite("src/sprites/viloes/Clowny.img"), 5, 80), "Fifaifi", 0, 80, 15, 10, 4, 1, {new Ataque("Cocegas", 2, 0), new Ataque("PingPong", 15, 4)}), *hero);
                level4.init();
                state = level4.run(screen);
                hero->desequiparArma();
                if(state == Fase::LEVEL_COMPLETE) level = Fase::LEVEL_7;
            }
            break;
        case Fase::LEVEL_7:
            {
                hero->equiparArma(new Arma("Teste", "teste", 30));
                FaseBatalha level5("Level4", Sprite("src/sprites/telas/battleBackground.img"), Monstro(ObjetoDeJogo("Vilao5",Sprite("src/sprites/viloes/Fear.img"), 5, 70), "Fiero", 0, 75, 20, 20, 4, 1, {new Ataque("Suspiro Lacerante", 2, 0), new Ataque("Entranhas", 10, 4)}), *hero);
                level5.init();
                state = level5.run(screen);
                hero->desequiparArma();
                if(state == Fase::LEVEL_COMPLETE) level = Fase::LEVEL_8;
            }
            break;
        case Fase::LEVEL_8:
            {
                hero->equiparArma(new Arma("Teste", "teste", 40));
                FaseBatalha level6("Level5", Sprite("src/sprites/telas/battleBackground.img"), Monstro(ObjetoDeJogo("Vilao6",Sprite("src/sprites/viloes/Horns.img"), 8, 70),"Horns", 0, 100, 30, 20, 4, 1, {new Ataque("Laceração", 5, 0), new Ataque("Tira-Olhos", 8, 0), new Ataque("Mal Súbito", 25, 4)}), *hero);
                level6.init();
                state = level6.run(screen);
                hero->desequiparArma();
                if(state == Fase::LEVEL_COMPLETE) level = Fase::END_GAME;
            }
            break;
        case Fase::OP_3:
			system("clear");
			std::cout << "Saindo...\n";
			system("sleep 1");
			state = Fase::END_GAME;
			break;
        case Fase::LEVEL_COMPLETE:
            hero->atualizarDados();
            if(level == Fase::END_GAME){
                FaseBanner endGame("EndGame", Sprite("src/sprites/telas/endGameBackground.img"));
                endGame.init();
                endGame.run(screen);
                state = Fase::MENU;
            }else{
                hero->getBag()->adicionarItem(p);
                // hero->getBag()->adicionarItem(p);
                state = Fase::MAPA;
            }
            break;
        case Fase::GAME_OVER:
            {
                FaseBanner gameOver("GameOver", Sprite("src/sprites/telas/gameOverBackground.img"));
                gameOver.init();
                gameOver.run(screen);
                state = Fase::MENU;
            }
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