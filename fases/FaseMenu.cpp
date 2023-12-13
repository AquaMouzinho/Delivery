#include "FaseMenu.hpp"
#include <iostream>
#include <termios.h>
#include <unistd.h>

void FaseMenu::init(){
    objs.push_back(new ObjetoDeJogo("Titulo", SpriteAnimado("src/sprites/telas/deliveryMenuTitle.anm"),5, 65));

    objs.push_back(new ObjetoDeJogo("OPMenu1", TextSprite("NOVO JOGO"), 21, 80));
    txtOpNovo = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("OPMenu2", TextSprite("SOBRE"), 23, 80));

//    objs.push_back(new ObjetoDeJogo("OPMenu3", TextSprite("MAPA CIDADE"), 25, 70));

//    objs.push_back(new ObjetoDeJogo("OPMenu4", TextSprite("BATALHA"), 27, 70));

    objs.push_back(new ObjetoDeJogo("OPMenu5", TextSprite("SAIR"), 25, 80));

    objs.push_back(new ObjetoDeJogo("Seletor", TextSprite("→ "), 21, 75));
    pSel = objs.back();

    help = new ObjetoDeJogo("PainelHelp", Sprite("src/sprites/itens/help.img"), 4, 40);
    help->desativarObj();
    objs.push_back(help);

    op = Fase::OP_1;
    vezes = 0;
    gameState = Fase::PLAYING;
    tela = Fase::PLAYING;
    menu_thread_ = thread(&FaseMenu::runPlayerChannel, ref(*this));
}

unsigned FaseMenu::run(SpriteBuffer &screen){
    tela = Fase::PLAYING;
    vezesRodado();

    if(vezes > 1) txtOpNovo->putAt(TextSprite("CONTINUAR"), 0, 0);
    
    system("clear");
    this->draw(screen);
    this->show(screen);

    while(true){
        if(isKeyPressed()){
            keyPressed = false;
            
            switch (entrada)
            {
            case 'q':
                if(!helpAparecendo){
                    gameState = Fase::LEVEL_COMPLETE;
                    return Fase::OP_3;
                }
            
            case 's':
                {
                    if(!helpAparecendo){
                        op = Fase::OP_1 + (op - Fase::OP_1 +1) % 3;

                        pSel->moveTo(21 + (op - Fase::OP_1) * 2, 75);
                    }
                }
                break;
            case 'w':
                {
                    if(!helpAparecendo){
                        op = Fase::OP_1 + (3 + ((op - Fase::OP_1) -1)) % 3;

                        pSel->moveTo(21 + (op - Fase::OP_1) * 2, 75);
                    }
                }
                break;
            case 'f':
                {
                    if(helpAparecendo){
                        helpAparecendo = false;
                        help->desativarObj();
                    }else{
                        if( op == Fase::OP_2) {
                            helpAparecendo = true;
                            help->ativarObj();
                        }else {
                            if(op == Fase::OP_3){
                                gameState = Fase::LEVEL_COMPLETE;
                            }
                            tela = Fase::PAUSED;
                            return op;
                        }
                    }
                }
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        system("clear");
        this->update();
        this->draw(screen);
        this->show(screen);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    gameState = Fase::LEVEL_COMPLETE;
    return Fase::END_GAME;
}

void FaseMenu::closeThreads(){
    std::cout << "Pressione qualquer tecla para confirmar..." << std::endl;
    menu_thread_.join();
}

void FaseMenu::runPlayerChannel(FaseMenu &menu) {
    struct termios old_tio, new_tio;
    unsigned char c;

    /* get the terminal settings for stdin */
    tcgetattr(STDIN_FILENO,&old_tio);

    /* we want to keep the old setting to restore them a the end */
    new_tio=old_tio;

    /* disable canonical mode (buffered i/o) and local echo */
    new_tio.c_lflag &=(~ICANON & ~ECHO);

    /* set the new settings immediately */
    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

    while(menu.gameState != Fase::LEVEL_COMPLETE){
        if(menu.tela == Fase::PLAYING){
            menu.entrada = getchar();

            menu.keyPressed = true;
        }else{
            menu.keyPressed = false;
        }
    }
    /* restore the former settings */
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
}
