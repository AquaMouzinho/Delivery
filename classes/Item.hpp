#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {
public:
    Item(std::string nome, std::string descricao) : nome(nome), descricao(descricao) {}
    ~Item(){}

    std::string getNome() const { return nome; }
    std::string getDescricao() const {return descricao; }  
    
private:
    std::string nome, descricao;
};

#endif