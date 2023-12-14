#include "FaseBatalha.hpp"

void FaseBatalha::init(){
    //Heroi
    objs.push_back(new ObjetoDeJogo("TxtNomeHeroi", TextSprite(heroi->getNome()),25,23));
    objs.push_back(new ObjetoDeJogo("TxtMaxHPHeroi", TextSprite(to_string(heroi->getMAXHPValue())),27,43));
    objs.push_back(new ObjetoDeJogo("TxtMaxPPHeroi", TextSprite(to_string(heroi->getMAXPPValue())),28,43));
    objs.push_back(new ObjetoDeJogo("TxtAtPPHeroi", TextSprite(to_string(heroi->getCurrentPPValue())),28,38));
    objs.push_back(new ObjetoDeJogo("TxtHPHeroi", TextSprite(to_string(heroi->getCurrentHPValue())),27,37));
    txtQtdHPAtualHeroi = objs.back()->getSprite();
    objs.push_back(new ObjetoDeJogo("BarraHPHeroi", TextSprite(replicador("█", (heroi->getCurrentHPValue()/(heroi->getMAXHPValue()/10)))+std::string(10 - (heroi->getCurrentHPValue()/(heroi->getMAXHPValue()/10)), ' ')), 27, 26));
    barraHPHeroi = objs.back()->getSprite();
    objs.push_back(new ObjetoDeJogo("TxtSPHeroi", TextSprite(replicador("♦", heroi->getCurrentSPValue())+std::string(heroi->getMAXSPValue()-heroi->getCurrentSPValue(), ' ')),29,49));
    txtQtdSPAtualHeroi = objs.back()->getSprite();

    //Vilao
    objs.push_back(new ObjetoDeJogo("TxtNomeVilao", TextSprite(vilao->getNome()),3,26));
    objs.push_back(new ObjetoDeJogo("TxtMaxHPVilao", TextSprite(to_string(vilao->getMAXHPValue())), 5,43));
    objs.push_back(new ObjetoDeJogo("TxtHPVilao", TextSprite(to_string(vilao->getCurrentHPValue())), 5,38));
    txtQtdHPAtualVilao = objs.back()->getSprite();
    objs.push_back(new ObjetoDeJogo("BarraHPVilao", TextSprite(replicador("█", (vilao->getCurrentHPValue()/(vilao->getMAXHPValue()/10)))+std::string(10 - (vilao->getCurrentHPValue()/(vilao->getMAXHPValue()/10)), ' ')), 5, 27));
    barraHPVilao = objs.back()->getSprite();
    objs.push_back(new ObjetoDeJogo("TxtSPVilao", TextSprite(replicador("■", vilao->getCurrentSPValue())+std::string(vilao->getMAXSPValue()-vilao->getCurrentSPValue(), ' ')),6,51));
    txtQtdPPAtualVilao = objs.back()->getSprite();


    //Objetos de tela
    objs.push_back(new ObjetoDeJogo("TxtResultado", TextSprite(string(56, ' ')), 33, 26));
    txtNomeGolpe = objs.back()->getSprite();

    pSelE = new ObjetoDeJogo("SeletorEsquerdo", Sprite("src/sprites/battle/leftSel.img"), 33, 91);
    objs.push_back(pSelE);
    pSelD = new ObjetoDeJogo("SeletorDireito", Sprite("src/sprites/battle/rightSel.img"), 33, 105);
    objs.push_back(pSelD);
    
    popUp = new ObjetoDeJogo("PopUp", Sprite("src/sprites/battle/popUp.img"), 21, 116);
    objs.push_back(popUp);
    popUp->desativarObj();

    int i = 0;
    for(auto &ataque : heroi->getAtaques()){
        ataques.push_back(new ObjetoDeJogo("Ataque"+to_string(i), TextSprite(ataque->getNome()), 24+(2*i), 120));
        ataques.back()->desativarObj();
        objs.push_back(ataques.back());
        ataques.push_back(new ObjetoDeJogo("Custo"+to_string(i), TextSprite(to_string(ataque->getCusto())), 24+(2*i), 132));
        ataques.back()->desativarObj();
        objs.push_back(ataques.back());
        ++i;
    }

    pocoes.push_back(new ObjetoDeJogo("PocaoHP", TextSprite("Poção HP"), 24, 120));
    pocoes.back()->desativarObj();
    objs.push_back(pocoes.back());

    qtdPocoesHP = new ObjetoDeJogo("QTDPocaoHP", TextSprite(to_string(heroi->getBag()->quantidadeDoItem("PocaoHP"))), 24, 132);
    pocoes.push_back(qtdPocoesHP);
    pocoes.back()->desativarObj();
    objs.push_back(pocoes.back());
    pocoes.push_back(new ObjetoDeJogo("PocaoSP", TextSprite("Poção SP"), 26, 120));
    pocoes.back()->desativarObj();
    objs.push_back(pocoes.back());
    pocoes.push_back(new ObjetoDeJogo("QTDPocaoSP", TextSprite(to_string(heroi->getBag()->quantidadeDoItem("PocaoSP"))), 26, 132));
    pocoes.back()->desativarObj();
    objs.push_back(pocoes.back());

    pSelPopUp = new ObjetoDeJogo("SeletorPopUp", TextSprite("►"), 24, 116);
    objs.push_back(pSelPopUp);
    pSelPopUp->desativarObj();

    txtNomeAbaPopUp = new ObjetoDeJogo("TextoAba", TextSprite("ATACK"), 22, 122);
    txtNomeAbaPopUp->desativarObj();
    objs.push_back(txtNomeAbaPopUp);

    objs.push_back(vilao);

    caixaContinuar = new ObjetoDeJogo("CaixaContinuar", Sprite("src/sprites/itens/boxBatalhaConcluida.img"), 15, 60);
    caixaContinuar->desativarObj();
    objs.push_back(caixaContinuar);

    op = Fase::OP_1;
    op2 = Fase::OP_1;
    tela_state = Fase::PLAYING;
    batalha_thread_ = thread(&FaseBatalha::runPlayerChannel, ref(*this));
}

unsigned FaseBatalha::run(SpriteBuffer &screen){     
    string linha = "";

    system("clear");
    this->update();
    this->draw(screen);
    this->show(screen);

    while(true){
        if(isKeyPressed()){
            keyPressed = false;
            switch (entrada)
            {
            case 'w':
                {
                    if(opTela){
                        if(pSelPopUp->getPosL() > 24){
                            op2--;
                            pSelPopUp->moveTo(pSelPopUp->getPosL()-2, pSelPopUp->getPosC());
                        }
                    }
                }
                break;
            case 's':
                {
                    if(opTela){
                        if(op == Fase::OP_1){
                            if(pSelPopUp->getPosL() < 28) {
                                op2++;
                                pSelPopUp->moveTo(pSelPopUp->getPosL()+2, pSelPopUp->getPosC());
                            }
                        } else {
                            if(pSelPopUp->getPosL() < 26) {
                                op2++;
                                pSelPopUp->moveTo(pSelPopUp->getPosL()+2, pSelPopUp->getPosC());
                            }
                        }
                    }
                }
                break;
            case 'a':
                {
                    if(!opTela){
                        if(op == Fase::OP_2) {
                            op = Fase::OP_1;
                            pSelE->moveTo(pSelE->getPosL(), pSelE->getPosC()-25);
                            pSelD->moveTo(pSelD->getPosL(), pSelD->getPosC()-25);
                        }
                    }
                }
                break;
            case 'd':
                {
                    if(!opTela){
                        if(op == Fase::OP_1) {
                            op = Fase::OP_2;
                            pSelE->moveTo(pSelE->getPosL(), pSelE->getPosC()+25);
                            pSelD->moveTo(pSelD->getPosL(), pSelD->getPosC()+25);
                        }
                    }
                }
                break;
            case 'f':
                {
                    if(opTela){ // TRATAMENTO POPUP ESCOLHA ATAQUE
                        if(op == Fase::OP_1){ // ESCOLHEU ATACAR
                            ataqueEscolhido = getAtaque(heroi->getAtaques(), (op2 - Fase::OP_1));
                            if(ataqueEscolhido->getCusto() <= heroi->getCurrentSPValue()){
                                /* TURNO HEROI */
                                    // fechar popUp
                                    opTela = false;
                                    popUp->desativarObj();
                                    txtNomeAbaPopUp->desativarObj();
                                    for(auto &ataque : ataques) ataque->desativarObj();
                                    pSelPopUp->desativarObj();

                                    // modificar heroi
                                    heroi->decrementSP(ataqueEscolhido->getCusto());
                                    if((ataqueEscolhido->getCusto() < 1) && (heroi->getCurrentSPValue() < 3)) heroi->incrementSP();
                                    txtQtdSPAtualHeroi->putAt(TextSprite(replicador("♦", heroi->getCurrentSPValue())+std::string(heroi->getMAXSPValue()-heroi->getCurrentSPValue(), ' ')),0,0);
                                    
                                    // vilao recebe dano
                                    int somaDano = heroi->getAtkValue() + ataqueEscolhido->getDano() + (heroi->getArma() != nullptr ? heroi->getArma()->getDanoFisico()*0.5 : 0) - (vilao->getDefValue()*0.5);
                                    vilao->receberDano(somaDano);

                                    if(!vilao->isAlive()) {

                                        int it = (this->getName().back() - '0');
                                        heroi->fasesConcluidas[it] = 1;
                                        heroi->salvarDados();
                                        tela_state = Fase::LEVEL_COMPLETE;
                                        caixaContinuar->ativarObj();

                                        system("clear");
                                        this->update();
                                        this->draw(screen);
                                        this->show(screen);
                                        std::this_thread::sleep_for(std::chrono::milliseconds(500));

                                        closeThreads();
                                        return Fase::LEVEL_COMPLETE;
                                    }

                                    //atualiza tela
                                    barraHPVilao->putAt(TextSprite(replicador("█", (vilao->getCurrentHPValue()/(vilao->getMAXHPValue()/10)))+std::string(10 - (vilao->getCurrentHPValue()/(vilao->getMAXHPValue()/10)), ' ')),0,0);
                                    txtQtdHPAtualVilao->putAt(TextSprite(string(txtQtdHPAtualVilao->getLargura() - to_string(vilao->getCurrentHPValue()).length(), '0')+to_string(vilao->getCurrentHPValue())), 0, 0);
                                    linha = "VOCE ATACOU "+vilao->getNome()+" COM " + ataqueEscolhido->getNome()+" E CAUSOU "+to_string(somaDano)+"pts";
                                    txtNomeGolpe->putAt(TextSprite(linha+string(56-linha.length(), ' ')), 0, 0);

                                    system("clear");
                                    this->update();
                                    this->draw(screen);
                                    this->show(screen);
                                    std::this_thread::sleep_for(std::chrono::seconds(2));

                                /* TURNO VILAO */
                                    handleVillainAttack();

                                    if(!heroi->isAlive()){
                                        caixaContinuar->ativarObj();
                                        tela_state = Fase::GAME_OVER;
                                        closeThreads();
                                        return Fase::GAME_OVER;
                                    }
                                  
                                    barraHPHeroi->putAt(TextSprite(replicador("█", (heroi->getCurrentHPValue()/(heroi->getMAXHPValue()/10)))+std::string(10 - (heroi->getCurrentHPValue()/(heroi->getMAXHPValue()/10)), ' ')),0,0);
                                    txtQtdHPAtualHeroi->putAt(TextSprite(string(txtQtdHPAtualHeroi->getLargura() - to_string(heroi->getCurrentHPValue()).length(), '0')+to_string(heroi->getCurrentHPValue())),0,0);
                                              
                            }else {
                                txtNomeGolpe->putAt(TextSprite("Sem PP suficiente"+string(40, ' ')), 0, 0);
                            }
                        }else { // ESCOLHEU SE CURAR
                            if(op2 == Fase::OP_1){
                                if(heroi->getBag()->quantidadeDoItem("PocaoHP") > 0){
                                    heroi->getBag()->removerItem("PocaoHP");
                                    heroi->curarHP(15);
                                    txtNomeGolpe->putAt(TextSprite("VOCE USOU UMA POCAO E CUROU 15pts DE HP"+string(16,' ')),0,0);
                                    barraHPHeroi->putAt(TextSprite(replicador("█", (heroi->getCurrentHPValue()/(heroi->getMAXHPValue()/10)))+std::string(10 - (heroi->getCurrentHPValue()/(heroi->getMAXHPValue()/10)), ' ')),0,0);
                                    txtQtdHPAtualHeroi->putAt(TextSprite(to_string(heroi->getCurrentHPValue())),0,0);
                                    qtdPocoesHP->getSprite()->putAt(TextSprite(to_string(heroi->getBag()->quantidadeDoItem("PocaoHP"))), 0,0);

                                    opTela = false;
                                    popUp->desativarObj();
                                    txtNomeAbaPopUp->desativarObj();
                                    for(auto &pocao : pocoes) pocao->desativarObj();
                                    pSelPopUp->desativarObj();
                                }else{
                                    txtNomeGolpe->putAt(TextSprite("VOCE NAO TEM POCAO HP"+string(34,' ')),0,0);
                                }
                            }else {
                                if(heroi->getBag()->quantidadeDoItem("PocaoSP") > 0){
                                    heroi->getBag()->removerItem("PocaoSP");
                                    heroi->incrementSP();

                                    opTela = false;
                                    popUp->desativarObj();
                                    txtNomeAbaPopUp->desativarObj();
                                    for(auto &pocao : pocoes) pocao->desativarObj();
                                    pSelPopUp->desativarObj();
                                }else {
                                    txtNomeGolpe->putAt(TextSprite("VOCE NAO TEM POCAO SP"+string(34,' ')),0,0);
                                }
                            }
                        }

                    }else{ // TRATAMENTO ESCOLHA DE TELAS
                        opTela = true;
                        popUp->ativarObj();
                        if(op == Fase::OP_2){
                            txtNomeAbaPopUp->getSprite()->putAt(TextSprite("BOLSA"),0,0);
                            for(auto &pocao : pocoes) pocao->ativarObj();
                        } else {
                            txtNomeAbaPopUp->getSprite()->putAt(TextSprite("ATACK"),0,0);
                            for(auto &ataque : ataques) ataque->ativarObj();
                        }
                        txtNomeAbaPopUp->ativarObj();
                        pSelPopUp->ativarObj();
                    }
                }
                break;
            case 'q':
                {
                    if(opTela){
                        // fechar popUp
                        opTela = false;
                        popUp->desativarObj();
                        txtNomeAbaPopUp->desativarObj();
                        pSelPopUp->desativarObj();

                        if(op == Fase::OP_1){
                            for(auto &ataque : ataques) ataque->desativarObj();
                        }else{
                            for(auto &pocao : pocoes) pocao->desativarObj();
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
    return Fase::MENU;
}

void FaseBatalha::runPlayerChannel(FaseBatalha &obj){
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

void FaseBatalha::closeThreads(){
    batalha_thread_.join();
}

Ataque* FaseBatalha::getAtaque(list<Ataque*> lista, unsigned _i) {
    list<Ataque*>::iterator it = lista.begin();
    for(int i = 0; i < _i; ++i) ++it;
    return *it;
}

void FaseBatalha::handleVillainAttack() {
    int soma = 0;
    string l = vilao->getNome()+" TE ATACOU COM ";
    for(auto &ataque: vilao->getAtaques()){
        if(vilao->getCurrentSPValue() > 3){
            if(ataque->getCusto() == 4) {
                soma = (ataque->getDano() + (vilao->getAtkValue()*0.5)) - (heroi->getDefValue()*0.5);
                heroi->receberDano(soma);
                vilao->setCurrentSP(0);
                l+=ataque->getNome();
                txtQtdPPAtualVilao->putAt(TextSprite(replicador("■", vilao->getCurrentSPValue())+std::string(vilao->getMAXSPValue()-vilao->getCurrentSPValue(),' ')),0,0);
                break;
            }
        }else{
            if(ataque->getCusto() == 0){
                soma = (ataque->getDano() + (vilao->getAtkValue()*0.5))- (heroi->getDefValue()*0.5);
                heroi->receberDano(soma);
                vilao->incrementSP();
                l+=ataque->getNome();
                txtQtdPPAtualVilao->putAt(TextSprite(replicador("■", vilao->getCurrentSPValue())+std::string(vilao->getMAXSPValue()-vilao->getCurrentSPValue(),' ')),0,0);
                break;
            }
        }
    }
    l += " E CAUSOU "+to_string(soma)+"pts";
    txtNomeGolpe->putAt(TextSprite(l+string(56-l.length(), ' ')), 0, 0);
}

std::string FaseBatalha::replicador(std::string caractere, int qtd){
    unsigned it = 0;
    std::string pontos = "";

    for(; it < qtd; it++)
        pontos += caractere;
    
    return pontos;
}