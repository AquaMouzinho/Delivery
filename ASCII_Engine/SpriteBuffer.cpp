#include "SpriteBuffer.hpp"
#include <string>
#include <iostream>
#include <locale>

std::ostream &operator<<(std::ostream &out, const SpriteBuffer &s)
{
	setlocale(LC_ALL, "en_US.utf8");
	for(int i = 0; i < s.sprt.size(); i++){
		out << s.sprt.at(i).c_str() << std::endl;
	}

	// for (auto it = s.sprt.begin() ; it != s.sprt.end() ; ++it)
	// 	std::cout << *it << std::endl;
	return out;
}

SpriteBuffer::SpriteBuffer(unsigned largura, unsigned altura) : SpriteBase(largura,altura)
{
	clear();
}

void SpriteBuffer::clear()
{
	sprt.clear();
	for (unsigned i = 0 ; i < alturaSprite ; i++)
		sprt.push_back(std::string(largura,' '));
}

std::string SpriteBuffer::getLinha(unsigned l) const
{
	if (l < sprt.size())
		return sprt[l];
	else 
		return "";
}

void SpriteBuffer::putAt(const SpriteBase &sprt, unsigned l, unsigned c)
{
	
	if (c >= this->largura)
		return;
	
	for (int i = 0 ; i < sprt.getAltura() ; i++)
	{
		
		if (i + l >= this->sprt.size())
			break;
		
		std::string linha = sprt.getLinha(i);
		std::string alvo = this->sprt[l+i];
		int lenAlvo = contaCaracteres(alvo), lenLinha = contaCaracteres(linha);

		this->sprt[l+i] = "";
		this->sprt[l+i] += particionaString(alvo, 0 , c);
		this->sprt[l+i] += linha;
		this->sprt[l+i] += particionaString(alvo, c+lenLinha, lenAlvo);

		// this->sprt[l+i] = "";
		// for(int j = 0; j < c; j++){
		// 	this->sprt[l+i] += alvo.c_str()[j];
		// }
		// for(int j = 0; j < lenAlvo-c && j < lenLinha; j++){
		// 	this->sprt[l+i] += linha.c_str()[j];
		// }
		// for(int j = c+lenLinha; j < lenAlvo; j++){
		// 	this->sprt[l+i] += alvo.c_str()[j];
		// }

		// this->sprt[l+i] = alvo.substr(0,c);
		// this->sprt[l+i] += linha.substr(0,alvo.length()-c);
		// this->sprt[l+i] += alvo.substr(c+linha.length(),alvo.length()-(c+linha.length()));
		
	}
}

//Tratamento de caracteres

unsigned int SpriteBuffer::contaCaracteres(const std::string &s) const{
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

std::string SpriteBuffer::particionaString(std::string &obj, unsigned int inicio, unsigned int fim){
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
