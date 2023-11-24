#include "Sprite.hpp"
#include <fstream>
#include <clocale>

std::ostream &operator<<(std::ostream &out, const Sprite &s)
{
	for (auto it = s.sprt.begin() ; it != s.sprt.end() ; ++it)
		std::cout << *it << std::endl;
	
	return out;
}


Sprite::Sprite(std::string nameFile) : SpriteBase()
{
	this->loadFromFile(nameFile);
}

Sprite::Sprite(std::ifstream &fsprt) : SpriteBase()
{
	this->loadFromFile(fsprt);
}

Sprite::Sprite(std::ifstream &fsprt, unsigned n) : SpriteBase()
{
	this->loadFromFile(fsprt, n);
}

void Sprite::loadFromFile(std::string nameFile)
{
	std::ifstream fsprt(nameFile.c_str(),std::ios::in);
	
	loadFromFile(fsprt);
	
	fsprt.close();
}

void Sprite::loadFromFile(std::ifstream &fsprt)
{
	this->sprt.clear();
	
	if (!fsprt.is_open())
	{	
		std::cout << "Erro ao ler arquivo..." << std::endl;
		return;
	}
	
	this->largura = 0;
	int tam = 0;
	std::string tmp;
	
	while(getline(fsprt,tmp))
	{
		sprt.push_back(tmp);
		tam = contarCaracteres(tmp);
		if (tam > this->largura)
			this->largura = tam;
		
	}
	
	this->alturaSprite = this->sprt.size();
}

void Sprite::loadFromFile(std::ifstream &fsprt, unsigned n)
{
	this->sprt.clear();
	
	if (!fsprt.is_open())
	{	
		std::cout << "Erro ao ler arquivo..." << std::endl;
		return;
	}
	
	this->largura = 0;
	
	std::string tmp;
	
	//std::cout << "Carregado Sprite..." << n << std::endl; //apagar
	
	while(getline(fsprt,tmp) && n--)
	{
		sprt.push_back(tmp);
		
		//std::cout << ">" << tmp << "<" << std::endl; //apagar
		
		if (tmp.length() > this->largura)
			this->largura = tmp.length();
	}
	
	this->alturaSprite = this->sprt.size();
}

std::string Sprite::getLinha(unsigned l) const
{
	if (l < sprt.size())
		return sprt[l];
	else 
		return "";
}

void Sprite::putAt(const SpriteBase &sprt, unsigned l, unsigned c)
{
	//std::cout << "Entrei..." << std::endl; //apagar
	if (c >= this->largura)
		return;
	
	//std::cout << "Passei da largura..." << std::endl; //apagar
	
	//std::cout << sprt.getAltura() << std::endl; //apagar
	for (int i = 0 ; i < sprt.getAltura() ; i++)
	{
		//std::cout << "No looop..." << std::endl; //apagar
		
		if (i + l >= this->sprt.size())
			break;
		
		//std::cout << "Passei do if da linha..." << std::endl; //apagar
			
		std::string linha = sprt.getLinha(i);
		std::string alvo = this->sprt[l+i];
		int lenAlvo = contarCaracteres(alvo), lenLinha = contarCaracteres(linha);

		this->sprt[l+i] = "";
		this->sprt[l+i] += particionaString(alvo, 0 , c);
		this->sprt[l+i] += linha;
		this->sprt[l+i] += particionaString(alvo, c+lenLinha, lenAlvo);

		// this->sprt[l+i] = alvo.substr(0,c);
		// this->sprt[l+i] += linha.substr(0,alvo.length()-c);
		// this->sprt[l+i] += alvo.substr(c+linha.length(),alvo.length()-(c+linha.length()));
		
		//if (c+linha.length() < alvo.length())
		//	this->sprt[l+i] += alvo.substr(c+linha.length(),alvo.length()-(c+linha.length()));
		
		
		//std::cout << this->sprt[l+i] << std::endl;
	}
	//std::cout << "Saindo..." << std::endl; //apagar
}

//Tratamento de caracteres
unsigned int Sprite::contarCaracteres(const std::string &s) const {
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



std::string Sprite::particionaString(std::string &obj, unsigned int inicio, unsigned int fim){
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
