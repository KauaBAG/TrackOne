#pragma once

#include <stdexcept>
#include <string>

class TipoDeComunicacao
{
protected:
    int tipo = -1;
    TipoDeComunicacao(int tipo) : tipo(tipo){}
public:
    virtual std::string getString() = 0;
    std::string getComunicacao() 
    {
        if(tipo==0) return "GSM";
        if(tipo==1) return "RFID";
        if(tipo==2) return "Satelital";
        throw std::runtime_error("Tipo inválido de comunicação: " + std::to_string(tipo) + 
            " (Somente 0(GSM), 1(RFID), 2(Satelital) são aceitos)");
    }
    virtual ~TipoDeComunicacao() {}
};

