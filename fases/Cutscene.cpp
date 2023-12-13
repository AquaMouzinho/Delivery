#include "Cutscene.hpp"

void Cutscene::init(){
    fstream fin(urlCenas+"/speechs_first_row.txt", ios::in);
    fstream fin2(urlCenas+"/speechs_second_row.txt", ios::in);
    std::string linha = "";
    while(getline(fin, linha)){
        falas.push_back(linha);
    }
    while(getline(fin2, linha)){
        falasSegunda.push_back(linha);
    }
    fin.close();
    fin2.close();

    iterador_cenas = 1;
    objs.push_back(new ObjetoDeJogo("Banner", Sprite(urlCenas+"/screens/scene"+to_string(iterador_cenas)+".img"), 6, 25));
    imgCutscene = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("ChatBox", Sprite("src/sprites/cutscenes/chatBox.img"), 28, 25));

    objs.push_back(new ObjetoDeJogo("NomePersonagem", TextSprite(falas.front().substr(0, falas.front().find(':'))), 29, 27));
    txtNomePersonagem = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("PrimeiraLinha", TextSprite(falas.front().substr(falas.front().find(':')+1, falas.front().length())), 31, 27));
    txtPrimeiraLinha = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("SegundaLinha", TextSprite(falasSegunda.front()), 32, 27));
    txtSegundaLinha = objs.back()->getSprite();

    objs.push_back(new ObjetoDeJogo("AnimacaoSeta", SpriteAnimado("src/sprites/cutscenes/arrow.anm"), 32, 125));

    caixaDeTexto = new ObjetoDeJogo("CaixaContinuar", Sprite("src/sprites/itens/boxCenaConcluida.img"), 15, 50);
    caixaDeTexto->desativarObj();
    objs.push_back(caixaDeTexto);

    tela_state = Fase::PLAYING;
    scene_thread_ = thread(&Cutscene::runPlayerChannel, std::ref(*this));
}

unsigned Cutscene::run(SpriteBuffer &screen){
    system("clear");
    this->draw(screen);
    this->show(screen);
        
    while(true){
        if(isKeyPressed()){
            keyPressed = false;

            if(entrada == 'f'){
                falas.pop_front();
                falasSegunda.pop_front();
                if(falas.size() < 1) break;
                
                txtNomePersonagem->putAt(TextSprite(falas.front().substr(0, falas.front().find(':'))), 0, 0);
                txtPrimeiraLinha->putAt(TextSprite(falas.front().substr(falas.front().find(':')+1, falas.front().length())), 0, 0);
                txtSegundaLinha->putAt(TextSprite(falasSegunda.front()), 0, 0);
                imgCutscene->putAt(Sprite(urlCenas+"/screens/scene"+to_string(++iterador_cenas)+".img"),0,0);
            }
        }

        system("clear");
        this->update();
        this->draw(screen);
        this->show(screen);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    caixaDeTexto->ativarObj();

    system("clear");
    this->update();
    this->draw(screen);
    this->show(screen);
    tela_state = Fase::PAUSED;
    closeThreads();

    return true;
}

void Cutscene::closeThreads(){
    scene_thread_.join();
}

//métodos-membro
void Cutscene::runPlayerChannel(Cutscene &obj){
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