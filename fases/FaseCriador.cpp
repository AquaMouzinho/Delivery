#include "FaseCriador.hpp"
#include <termios.h>
#include <unistd.h>
#include <ios>
#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;

void FaseCriador::init(){
    objs.push_back(new ObjetoDeJogo("OpEsquerdo", TextSprite("◄"), 17, 70));
    pSelOpE = objs.back();

    objs.push_back(new ObjetoDeJogo("OpDireito", TextSprite("►"), 17, 80));
    pSelOpD = objs.back();

    objs.push_back(new ObjetoDeJogo("TxtCabelo", TextSprite("01"), 17, 72));
    txtOpCabelo = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("TxtNariz", TextSprite("01"), 17, 90));
    txtOpNariz = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("TxtMarcas", TextSprite("01"), 17, 108));
    txtOpAdicional = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("TxtOlho", TextSprite("01"), 24, 72));
    txtOpOlho = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("TxtCorpo", TextSprite("01"), 24, 90));
    txtOpCorpo = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("SpriteP1",Sprite("src/sprites/heroi/partesHeroi/0/cabelo0.img"),15,57));
    sprtCabelo = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("SpriteP2",Sprite("src/sprites/heroi/partesHeroi/1/olho0.img"),18,57));
    sprtOlho = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("SpriteP3",Sprite("src/sprites/heroi/partesHeroi/2/nariz0.img"),19,60));
    sprtNariz = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("SpriteP4",Sprite("src/sprites/heroi/partesHeroi/4/detalhe0.img"),19,57));
    sprtAdicional = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("SpriteP4",Sprite("src/sprites/heroi/partesHeroi/3/corpo0.img"),20,57));
    sprtCorpo = objs.back()->getSprite();

    // objs.push_back(new ObjetoDeJogo("SpriteFront", Sprite("src/heroi_front.img"), 31, 30));
    // sprtFront = objs.back()->getSprite();

    linhaMenu = 0;
    colunaMenu = 0;
    listaTracos = {1,1,1,1,1};
    tela_state = Fase::PLAYING;
    tela_thread_ = thread(&FaseCriador::openPlayerChannel, ref(*this));
}

unsigned FaseCriador::run(SpriteBuffer &screen){
    system("clear");
    this->draw(screen);
    this->show(screen);

    while(true){
        if(isKeyPressed()){
            keyPressed = false;
            switch(entrada){
                case 'q':
                    tela_state = Fase::LEVEL_COMPLETE;
                    return Fase::LEVEL_COMPLETE;
                case 'w':
                    {
                        if(!isMudarTraco()){
                            linhaMenu = 0;
                            pSelOpE->moveTo((17+(7*linhaMenu)), pSelOpE->getPosC());
                            pSelOpD->moveTo((17+(7*linhaMenu)), pSelOpD->getPosC());
                            //txtOpOlho->putAt(TextSprite(std::to_string(linhaMenu+(colunaMenu*2))),0,0);
                        }
                    }
                    break;
                case 's':
                    {
                        if(!isMudarTraco()){
                            linhaMenu = 1;
                            pSelOpE->moveTo((17+(7*linhaMenu)), pSelOpE->getPosC());
                            pSelOpD->moveTo((17+(7*linhaMenu)), pSelOpD->getPosC());
                            //txtOpOlho->putAt(TextSprite(std::to_string(linhaMenu+(colunaMenu*2))),0,0);
                        }
                    }
                    break;
                case 'a':
                    {
                        if(!isMudarTraco()){
                            if(colunaMenu != 0){
                                colunaMenu--;
                            }
                            pSelOpE->moveTo(pSelOpE->getPosL(), (70+(18*colunaMenu)));
                            pSelOpD->moveTo(pSelOpD->getPosL(), (80+(18*colunaMenu)));
                            //txtOpOlho->putAt(TextSprite(std::to_string(linhaMenu+(colunaMenu*2))),0,0);

                        } else {
                            int i = linhaMenu+(colunaMenu*2);
                            if(listaTracos[i]>1){
                                listaTracos[i]--;
                            }

                            switch (i)
                            {
                            case 0:
                                txtOpCabelo->putAt(TextSprite((listaTracos[i]<10 ? "0" : "")+std::to_string(listaTracos[i])),0,0);
                                sprtCabelo->putAt(Sprite("src/sprites/heroi/partesHeroi/0/cabelo"+std::to_string(listaTracos[i]-1)+".img"),0,0);
                                break;
                            case 1:
                                txtOpOlho->putAt(TextSprite((listaTracos[i]<10 ? "0" : "")+std::to_string(listaTracos[i])),0,0);
                                sprtOlho->putAt(Sprite("src/sprites/heroi/partesHeroi/1/olho"+std::to_string(listaTracos[i]-1)+".img"),0,0);
                                break;
                            case 2:
                                txtOpNariz->putAt(TextSprite((listaTracos[i]<10 ? "0" : "")+std::to_string(listaTracos[i])),0,0);
                                sprtNariz->putAt(Sprite("src/sprites/heroi/partesHeroi/2/nariz"+std::to_string(listaTracos[i]-1)+".img"),0,0);
                                break;
                            case 3:
                                txtOpCorpo->putAt(TextSprite((listaTracos[i]<10 ? "0" : "")+std::to_string(listaTracos[i])),0,0);
                                sprtCorpo->putAt(Sprite("src/sprites/heroi/partesHeroi/3/corpo"+std::to_string(listaTracos[i]-1)+".img"),0,0);
                                break;
                            case 4:
                                txtOpAdicional->putAt(TextSprite("0"+std::to_string(listaTracos[i])),0,0);
                                sprtAdicional->putAt(Sprite("src/sprites/heroi/partesHeroi/4/detalhe"+std::to_string(listaTracos[i]-1)+".img"),0,0);
                                break;
                            
                            }
                        }
                    }
                    break;
                case 'd':
                    {
                        if(!isMudarTraco()){
                            
                            if(colunaMenu < 2){
                                colunaMenu++;
                            }
                             
                            pSelOpE->moveTo(pSelOpE->getPosL(), (70+(18*colunaMenu)));
                            pSelOpD->moveTo(pSelOpD->getPosL(), (80+(18*colunaMenu)));
                            //txtOpOlho->putAt(TextSprite(std::to_string(linhaMenu+(colunaMenu*2))),0,0);
                        } else {
                            int i = linhaMenu+(colunaMenu*2);
                            switch(i){
                                case 0:
                                    if(listaTracos[i]<12) listaTracos[i]++;
                                    txtOpCabelo->putAt(TextSprite((listaTracos[i]<10 ? "0" : "")+std::to_string(listaTracos[i])),0,0);
                                    sprtCabelo->putAt(Sprite("src/sprites/heroi/partesHeroi/0/cabelo"+std::to_string(listaTracos[i]-1)+".img"),0,0);
                                    break;
                                case 1:
                                    if(listaTracos[i]<15) listaTracos[i]++;
                                    txtOpOlho->putAt(TextSprite((listaTracos[i]<10 ? "0" : "")+std::to_string(listaTracos[i])),0,0);
                                    sprtOlho->putAt(Sprite("src/sprites/heroi/partesHeroi/1/olho"+std::to_string(listaTracos[i]-1)+".img"),0,0);
                                    break;
                                case 2:
                                    if(listaTracos[i]<15) listaTracos[i]++;
                                    txtOpNariz->putAt(TextSprite((listaTracos[i]<10 ? "0" : "")+std::to_string(listaTracos[i])),0,0);
                                    sprtNariz->putAt(Sprite("src/sprites/heroi/partesHeroi/2/nariz"+std::to_string(listaTracos[i]-1)+".img"),0,0);
                                    break;
                                case 3:
                                    if(listaTracos[i]<10) listaTracos[i]++;
                                    txtOpCorpo->putAt(TextSprite((listaTracos[i]<10 ? "0" : "")+std::to_string(listaTracos[i])),0,0);
                                    sprtCorpo->putAt(Sprite("src/sprites/heroi/partesHeroi/3/corpo"+std::to_string(listaTracos[i]-1)+".img"),0,0);
                                    break;
                                case 4:
                                    if(listaTracos[i]<9) listaTracos[i]++;
                                    txtOpAdicional->putAt(TextSprite("0"+std::to_string(listaTracos[i])),0,0);
                                    sprtAdicional->putAt(Sprite("src/sprites/heroi/partesHeroi/4/detalhe"+std::to_string(listaTracos[i]-1)+".img"),0,0);
                                    break;
                            }
                        }
                    }
                    break;
                case 'f':
                    {
                        if(!(linhaMenu == 1 && colunaMenu == 2)){
                            mudarTraco = (mudarTraco ? false : true);
                        }else{
                            if(salvarSpriteHeroi()){
                                //sprtFront->putAt(Sprite("src/heroi_front.img"),0,0);
                                tela_state = Fase::LEVEL_COMPLETE;
                                return Fase::LEVEL_COMPLETE;
                            }
                        }
                    }
                    break;
            }
        }
        
        system("clear");
        this->update();
        this->draw(screen);
        this->show(screen);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    tela_state = Fase::LEVEL_COMPLETE;
    return Fase::OP_2;
}

void FaseCriador::openPlayerChannel(FaseCriador &obj){
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

void FaseCriador::closeThreads(){
    tela_thread_.join();
}

bool FaseCriador::salvarSpriteHeroi() {
    ofstream fout("src/sprites/heroi/heroi.img", std::ios::out);
    ofstream fout2("src/sprites/heroi/heroi_front.img", std::ios::out);
    ifstream fin1("src/sprites/heroi/partesHeroi/0/cabelo"+to_string(listaTracos[0]-1)+".img", ios::in);
    ifstream fin2("src/sprites/heroi/partesHeroi/1/olho"+to_string(listaTracos[1]-1)+".img", ios::in);
    ifstream fin3("src/sprites/heroi/partesHeroi/2/nariz"+to_string(listaTracos[2]-1)+".img", ios::in);
    ifstream fin4("src/sprites/heroi/partesHeroi/3/corpo"+to_string(listaTracos[3]-1)+".img", ios::in);
    ifstream fin5("src/sprites/heroi/partesHeroi/4/detalhe"+to_string(listaTracos[4]-1)+".img", ios::in);
    
    if (!fout && !fout2 && !fin1 && !fin2 && !fin3 && !fin4 && !fin5)
        return false;

    string linha;
    while(getline(fin1, linha)){
        fout << linha << endl;
        fout2 << linha << endl;
    }
    while(getline(fin2, linha)){
        fout << linha << endl;
        fout2 << linha << endl;
    }
    
    while(getline(fin5, linha)){
        fout << linha;
        fout2 << linha;
    }
    while(getline(fin3, linha)){
        fout << linha << endl;
        fout2 << linha;
    }

    while(getline(fin4, linha)){
        fout << linha << endl;
    }

    fin1.close();
    fin2.close();
    fin3.close();
    fin4.close();
    fin5.close();
    
    return true;
}