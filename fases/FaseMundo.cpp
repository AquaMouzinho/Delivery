#include "FaseMundo.hpp"
#include <termios.h>
#include <unistd.h>
#include <iostream>
using namespace std;

void FaseMundo::init(){
    // Inicialização - objetos de texto "estaticos"
    // Dados Bloco Heroi
    objs.push_back(new ObjetoDeJogo("TxtNomeHeroi", TextSprite(hero.getNome()), 7, 136));
    objs.push_back(new ObjetoDeJogo("TxtHPAtHeroi", TextSprite(std::to_string(hero.getCurrentHPValue())), 13, 146));
    txtQtdHP = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("TxtHPMaxHeroi", TextSprite(std::to_string(hero.getMAXHPValue())), 13, 149));
    objs.push_back(new ObjetoDeJogo("TxtPPAtHeroi", TextSprite(std::to_string(hero.getMAXPPValue())), 15, 146));
    txtQtdPP = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("TxtPPMaxHeroi", TextSprite(std::to_string(hero.getCurrentPPValue())), 15, 149));
    objs.push_back(new ObjetoDeJogo("FrontHero", Sprite("src/sprites/heroi/heroi_front.img"), 17, 131));


    // Inicialização - objetos dinamicos

    leitorMapa("src/collisions/worldCollision.col", mapaColisao);

    // Objetos interativos
    caixa = new Chest(ObjetoDeJogo("Chest1", Sprite("src/sprites/overworld/chest.img"), 9, 40), Item("Chave", "Uma chave especial"));
    mapaColisao[caixa->getPosL()][caixa->getPosC()] = 0;
    objs.push_back(caixa);

    placa = new ObjetoDeJogo("Sign1", Sprite("src/sprites/overworld/sign.img"), 15, 29);
    mapaColisao[placa->getPosL()][placa->getPosC()] = 0;
    objs.push_back(placa);

    porta = new Door(ObjetoDeJogo("Gate", SpriteAnimado("src/sprites/overworld/gate.anm"),18, 44));
    mapaColisao[porta->getPosL()][porta->getPosC()] = 0;
    objs.push_back(porta);

    person = new Npc(ObjetoDeJogo("Person", Sprite("src/sprites/overworld/person.img"),22, 82));
    mapaColisao[person->getPosL()][person->getPosC()] = 0;
    objs.push_back(person);

    fases[0] = new Portal(ObjetoDeJogo("Meio do Nada", SpriteAnimado("src/sprites/overworld/level.anm"), 18, 17), Fase::LEVEL_1,(hero.fasesConcluidas[0] ? true : false));
    objs.push_back(fases[0]);
    
    fases[1] = new Portal(ObjetoDeJogo("Colmeia", SpriteAnimado("src/sprites/overworld/level.anm"), 11, 25), Fase::LEVEL_2, (hero.fasesConcluidas[1] ? true : false));
    objs.push_back(fases[1]);
    
    fases[2] = new Portal(ObjetoDeJogo("Cidadela", Sprite("src/sprites/overworld/level.img"), 11,40), Fase::LEVEL_3);
    objs.push_back(fases[2]);
    
    fases[3] = new Portal(ObjetoDeJogo("Lojinha", Sprite("src/sprites/overworld/level.img"), 27,54), Fase::SHOP);
    objs.push_back(fases[3]);
    
    fases[4] = new Portal(ObjetoDeJogo("Areia Roxa", Sprite("src/sprites/overworld/level.img"), 30,60), Fase::LEVEL_4);
    objs.push_back(fases[4]);
    
    fases[5] = new Portal(ObjetoDeJogo("Reino Bern", SpriteAnimado("src/sprites/overworld/level.anm"), 23,74), Fase::LEVEL_5,  (hero.fasesConcluidas[2] ? true : false));
    objs.push_back(fases[5]);
    
    fases[6] = new Portal(ObjetoDeJogo("Stupendus Circ", SpriteAnimado("src/sprites/overworld/level.anm"), 22,90), Fase::LEVEL_6,  (hero.fasesConcluidas[3] ? true : false));
    objs.push_back(fases[6]);
    
    fases[7] = new Portal(ObjetoDeJogo("Surpresa", SpriteAnimado("src/sprites/overworld/level.anm"), 15,113), Fase::LEVEL_7,  (hero.fasesConcluidas[4] ? true : false));
    objs.push_back(fases[7]);
    
    fases[8] = new Portal(ObjetoDeJogo("Batalha Final", SpriteAnimado("src/sprites/overworld/level.anm"), 11,113), Fase::LEVEL_8,  (hero.fasesConcluidas[5] ? true : false));
    objs.push_back(fases[8]);
    
    sprtHero = new ObjetoDeJogo("Heroi", Sprite("src/sprites/overworld/hero.img"), hero.getYMapa(), hero.getXMapa());
    objs.push_back(sprtHero);
    
    ObjetoDeJogo a("Dialog", Sprite("src/sprites/dialog.img"), 28, 5);
    caixaDeTexto = new Dialog(a, "teste", 10, 4);
    objs.push_back(caixaDeTexto);
    caixaDeTexto->desativarObj();

    // Placa Nome Fase
    objs.push_back(new ObjetoDeJogo("TxtNomeFase", TextSprite("              "), 28, 136));
    txtFaseNome = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("TxtPressione", TextSprite("PRESSIONE F"), 30, 138));
    objs.back()->desativarObj();

    tela_state = Fase::PLAYING;
    mundo_thread_ = std::thread(&FaseMundo::runPlayerChannel, ref(*this));
}

unsigned FaseMundo::run(SpriteBuffer &screen){
    bool colideComFase = false;
    tela_state = Fase::PLAYING;
    
    while(true){
        if(isKeyPressed()){
            keyPressed = false;
            switch (entrada)
            {
            case 'w':
                {
                    if(mapaColisao[sprtHero->getPosL()-1][sprtHero->getPosC()] == 1)
                        sprtHero->moveUp();
                }
                break;
            
            case 's':
                {
                    if(mapaColisao[sprtHero->getPosL()+1][sprtHero->getPosC()] == 1)
                        sprtHero->moveDown();
                }
                break;
            case 'a':
                {
                    if(mapaColisao[sprtHero->getPosL()][sprtHero->getPosC()-1] == 1)
                        sprtHero->moveLeft();
                }
                break;
            case 'd':
                {
                    if(mapaColisao[sprtHero->getPosL()][sprtHero->getPosC()+1] == 1)
                        sprtHero->moveRight();
                }
                break;
            case 'f':
                {
                    if(colideComFase){
                        for(auto &fase : fases){
                            if(fase->colideCom(*sprtHero)){
                                if(!fase->getCompletado()){
                                    tela_state = Fase::PAUSED;
                                    hero.setXMapa(sprtHero->getPosC());
                                    hero.setYMapa(sprtHero->getPosL());
                                    hero.salvarDados();
                                    this->closeThreads();
                                    return fase->getEnumeracao();
                                }
                            }
                        }
                    }

                    if(sprtHero->colideCom(*caixa)){
                        hero.getBag()->adicionarItem(*(caixa->getItem()));
                        mapaColisao[caixa->getPosL()][caixa->getPosC()] = 1;
                        caixa->desativarObj();
                    }
                }
                break;
            case 'q':
                tela_state = Fase::END_GAME;
                closeThreads();
                return Fase::MENU;
            }

        }

        if(sprtHero->colideCom(*placa)){
            if(!caixaDeTexto->isAtivado()){
                caixaDeTexto->ativarObj();
                caixaDeTexto->switchAtivado();
            }
        }else{
            if(caixaDeTexto->isAtivado()){
                caixaDeTexto->desativarObj();
                caixaDeTexto->switchAtivado();
            }
        }

        colideComFase = false;
        for(auto &fase : fases){
            if(fase->colideCom(*sprtHero)){
                if(fase->getPosC() == sprtHero->getPosC() && fase->getPosL() == sprtHero->getPosL()){
                    colideComFase = true;
                    if(fase->getCompletado()){
                        txtFaseNome->putAt(TextSprite("Fase Concluida"), 0 , 0);
                    }else{
                        objs.back()->ativarObj();
                        txtFaseNome->putAt(TextSprite(fase->getName()), 0, 0);
                    }
                }
            }
        }

        if(!colideComFase){
            objs.back()->desativarObj();
            txtFaseNome->putAt(TextSprite("              "),0,0);
        }

        if(sprtHero->colideCom(*porta)){
            if(hero.getBag()->temItem("Chave") && !porta->isAberto()){
                mapaColisao[porta->getPosL()][porta->getPosC()] = 1;
                hero.getBag()->removerItem("Chave");
                porta->setIsAberto(true);
            }
        }

        if(sprtHero->colideCom(*person)){
            if(hero.getBag()->temItem("Chave da Cidade")){
                mapaColisao[person->getPosL()][person->getPosC()] = 1;
                hero.getBag()->removerItem("Chave da Cidade");
                person->desativarObj();
            }
        }

        system("clear");
        this->update();
        this->draw(screen);
        this->show(screen);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

    }

    return Fase::LEVEL_COMPLETE;
}

void FaseMundo::runPlayerChannel(FaseMundo &obj){
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

    while(obj.tela_state == Fase::PLAYING){
        obj.entrada = getchar();
        obj.keyPressed = true;
    }

    /* restore the former settings */
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
}

void FaseMundo::closeThreads(){
    mundo_thread_.join();
}

bool FaseMundo::leitorMapa(std::string file, std::array<std::array<int, 160>, 40> &mapa) {
    //fstream fout("src/collisions/resultCollision.col", std::ofstream::out | std::ofstream::trunc);
    ifstream fin(file, std::ios::in);
    
    if(!fin)
        return false;

    int linah = 0;
    string linha, linha2;
    while(getline(fin,linha)){
        int j = 0;
        linha2 = "";
        for(auto &c : linha){
            mapa[linah][j] = c - '0';
            linha2 += to_string(mapa[linah][j]);
            j++;
        }
        //fout << linha2 << endl;
        linah++;
    }

    //mapa[this->placa->getPosL()][this->placa->getPosC()] = 0;

    fin.close();

    return true;
}