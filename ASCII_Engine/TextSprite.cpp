#include "TextSprite.hpp"
#include <iostream>

std::ostream &operator<<(std::ostream &out, const TextSprite &ts)
{
	out << ts.text << std::endl;
	return out;
}

std::string TextSprite::getLinha(unsigned l) const
{
	if (l == 0)
		return text;
	else 
		return "";
}

void TextSprite::putAt(const SpriteBase &sprt, unsigned l, unsigned c)
{
	if (l != 0 || c >= this->text.length())
		return;
		
	//std::cout << "Entrei..." << std::endl; //apagar
	
	std::string linha = sprt.getLinha(0);
	std::string alvo = this->text;
	
	//std::cout << linha << "-" << alvo << std::endl; //apagar
	//std::cout << this->largura << "-" << sprt.getLargura() << std::endl; //apagar
	
	// this->text = alvo.substr(0,c);
	// this->text += linha.substr(0,alvo.length()-c);
	// this->text += alvo.substr(c+linha.length(),alvo.length()-(c+linha.length()));

	int lenAlvo = contarCaracteres(alvo), lenLinha = contarCaracteres(linha);

	this->text = particionaString(alvo, 0, c);
	this->text += linha;
	this->text += particionaString(alvo, c+lenLinha, lenAlvo);
}


//Tratamento de caracteres
unsigned int TextSprite::contarCaracteres(const std::string &s) const {
	setlocale(LC_ALL, "en_US.utf8");
	unsigned int charCount = 0;

    unsigned int strLen = s.length();
    unsigned int u = 0;
    const char *c_str = s.c_str();

    while(u < strLen)
    {
        u += mblen(&c_str[u], strLen - u);
        charCount += 1;
    }

    return charCount;
}

std::string TextSprite::particionaString(std::string &obj, unsigned int inicio, unsigned int fim){
	//int inicio => numero do "indice" do caractere de inicio da nova string (incluso)
    //int inicio => numero do "indice" caractere que encerra a nova string (não-incluso)
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
