#pragma once

#include <string>
#include "Data.hpp"

class Alerta 
{
private:
    void setTipo(short tipo)
    {
        if(tipo < 0 || tipo > 2) throw std::runtime_error("Tipo inválido de alerta: " + std::to_string(tipo) + 
            " (Somente 0(Velocidade), 1(Bateria), 2(Zona) são aceitos)");
        this->tipo = tipo;
    }
protected:
    short tipo = -1;
    unsigned int subid = -1;
    Data dataDeEmissao;
    std::string localizacao = "";

    Alerta(unsigned int tipo, unsigned int subid, Data dataDeEmissao, std::string localizacao)
    {
        setTipo(tipo);
        setSubid(subid);
        setDataDeEmissao(dataDeEmissao);
        setLocalizacao(localizacao);
    }

public:
    
    virtual std::string getString()
    {
        return std::to_string(subid)+", "+getTipo() + ", data: " + dataDeEmissao.getString() + ", localizacao "+ localizacao;
    }
    
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

