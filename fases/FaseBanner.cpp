#include "FaseBanner.hpp"


void FaseBanner::init(){
    caixaDeTexto = new ObjetoDeJogo("CaixaContinuar", Sprite("src/sprites/itens/boxEntrandoFase.img"), 15, 50);
    caixaDeTexto->desativarObj();
    objs.push_back(caixaDeTexto);

    tela_state = Fase::PLAYING;
    banner_thread_ = thread(&FaseBanner::runPlayerChannel, std::ref(*this));
}

unsigned FaseBanner::run(SpriteBuffer &screen){
    Sound backtrack("src/sounds/banner.mp3");
    backtrack.playloop();

    system("clear");
    this->draw(screen);
    this->show(screen);
        
    while(true){
        if(isKeyPressed()){
            keyPressed = false;

            if(entrada == 'f'){
                tela_state = Fase::PAUSED;
                caixaDeTexto->ativarObj();

                system("clear");
                this->update();
                this->draw(screen);
                this->show(screen);
                closeThreads();
                backtrack.pause();
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                return Fase::MENU;
            }
        }

        system("clear");
        this->update();
        this->draw(screen);
        this->show(screen);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    backtrack.pause();
    return true;
}

void FaseBanner::closeThreads(){
    banner_thread_.join();
}

//métodos-membro
void FaseBanner::runPlayerChannel(FaseBanner &obj){
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