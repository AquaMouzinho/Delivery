#include "Dialog.hpp"
#include <fstream>
#include <ios>
using namespace std;

Dialog::Dialog(ObjetoDeJogo &obj, std::string texto, unsigned width, unsigned length)  : ObjetoDeJogo(obj), texto(texto), width(width), length(length), velocidadeTexto(1), ativado(false){
    obj.getSprite()->setAltura(length);
    obj.getSprite()->setLargura(width);
    constroiDialog();
    obj.getSprite()->putAt(Sprite("src/sprites/dialog.img"), 0, 0);
}

bool Dialog::constroiDialog() {
    ofstream fout("src/sprites/dialog.img", std::ofstream::out | std::ofstream::trunc);

    if(!fout)
        return false;
    
    string arquivo[3], linhaDialog;
    
    // Construção topo
    linhaDialog = "Ṋ";
    for(int j = 0; j < this->width-2; j++) linhaDialog += "ṋ";
    linhaDialog += "Ṍ";
    fout << linhaDialog << endl;

    //Construção meio
    linhaDialog = "Ṛ";
    for(int j = 0; j < this->width-2; j++) linhaDialog += ' ';
    linhaDialog += "Ṝ";
    for(int k = 0; k < this->length-2; k++){
        fout << linhaDialog << endl;
    }

    //Construção final
    linhaDialog = "Ṫ";
    for(int j = 0; j < this->width-2; j++) linhaDialog += "ṫ";
    linhaDialog += "Ṭ";
    fout << linhaDialog << endl;

    return true;
}

std::string Dialog::particionaString(std::string &obj, unsigned int inicio, unsigned int fim){
	//int inicio => numero do "indice" do caractere de inicio da nova string (incluso)
    //int fim => numero do "indice" caractere que encerra a nova string (não-incluso)
    std::string novastr("");

    unsigned int charCount = 0;
    unsigned int strLen = obj.length();
    unsigned int u = 0, previous_u = u;
    const char *c_str = obj.c_str();

    //faz u chegar no inicio da particao da string
    while(charCount < inicio)
    {
        u += mblen(&c_str[u], strLen - u);
        previous_u = u;
        charCount++;
    }
    //vai de onde u parou até o fim
    while(charCount < fim)
    {
        u += mblen(&c_str[u], strLen - u);
        for(int i = previous_u; i < u; i++){
            novastr += obj[i];
        }
        previous_u = u;
        //cout << charCount << " nova_str: " << novastr << endl;
        charCount++;
    }


    //cout << "String atualmente :" << novastr.c_str() <<"fim"<<endl;
    return novastr;
}
