#pragma once

#include <stdexcept>
#include <string>

class TipoDeComunicacao
{
private:
    void setComunicacao(short tipo) 
    {
        if(tipo < 0 || tipo > 2) throw std::runtime_error("Tipo inválido de comunicação: " + std::to_string(tipo) + 
            " (Somente 0(GSM), 1(RFID), 2(Satelital) são aceitos)");
        this->tipo = tipo;
    }
protected:
    short tipo = -1;
    TipoDeComunicacao(short tipo) 
    {
        setComunicacao(tipo);
    }
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
    short getTipo() {return tipo;}
};

