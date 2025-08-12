#pragma once

#include <string>
#include "Data.hpp"

class Alerta 
{
protected:
    unsigned int tipo;
    unsigned int subid;
    Data dataDeEmissao;
    std::string localizacao;

public:
    Alerta(int tipo, int subid, Data dataDeEmissao, std::string localizacao)
    : tipo(tipo), subid(subid), dataDeEmissao(dataDeEmissao), localizacao(localizacao) {}
    
    virtual std::string getString() = 0;
    
    std::string getTipo() 
    {
        if(tipo==0) return "Alerta de Velocidade";
        if(tipo==1) return "Alerta de Bateria";
        if(tipo==2) return "Alerta de Zona";
        throw std::runtime_error("Tipo inválido de comunicação: " + std::to_string(tipo) + 
            " (Somente 0(Velocidade), 1(Bateria), 2(Zona) são aceitos)");
    }
    unsigned int getSubid() {return subid;}
    Data getDataDeEmissao() {return dataDeEmissao;}
    std::string getLocalizacao() {return localizacao;}

    void setSubid(unsigned int subid) {this->subid = subid;}
    void setDataDeEmissao(Data dataDeEmissao) {this->dataDeEmissao = dataDeEmissao;}
    void setLocalizacao(std::string localizacao) {this->localizacao = localizacao;}
};

