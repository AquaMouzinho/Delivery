#include "Heroi.hpp"

bool Heroi::atualizarDados(){
    fstream fin("src/herodata.dat", ifstream::in);

    if(!fin)
        return false;

    string linha;
    int  i = 0;
    while(getline(fin, linha)){
        switch (i)
        {
        case 2:
            this->setCurrentHP(stoi(linha.substr(0, linha.find("/"))));
            break;
        case 3:
            this->setCurrentSP(stoi(linha.substr(0, linha.find("/"))));
            break;
        case 4:
            this->setCurrentPP(stoi(linha.substr(0, linha.find("/"))));
            break;
        case 10:
            this->setXMapa(stoi(linha.substr(0, linha.find(","))));
            this->moveTo(this->yMapa, this->xMapa);
            //this->setYMapa(stoi(linha.substr(linha.find(","), *(linha.cend()))));
            break;
        case 11:
            this->fasesConcluidas = vector<int>{linha.at(0)-'0',linha.at(2)-'0',linha.at(4)-'0',linha.at(6)-'0',linha.at(8)-'0',linha.at(10)-'0'};
            break;
        }
        ++i;
    }
    return true;
}

bool Heroi::salvarDados() {
    fstream fout("src/herodata.dat", ofstream::out | ofstream::trunc );

    if(!fout)
        return false;
    
    fout << getNome() << endl;
    fout << getMoney() << endl;
    fout << getCurrentHPValue() << "/" << getMAXHPValue() << endl;
    fout << getCurrentPPValue() << "/" << getMAXPPValue() << endl;
    fout << getCurrentSPValue() << "/" << getMAXSPValue() << endl;
    fout << getAtkValue() << endl;
    fout << getDefValue() << endl;
    fout << (armaEquipada != nullptr ? "" : "not") << endl;
    fout << "{"<< "" << "}" << endl;
    fout << getStatusValue() << endl;
    fout << getXMapa() << ","<< getYMapa() << endl;
    for(int i  = 0; i < 6; i++) fout << to_string(fasesConcluidas[i])+",";

    return true;
}