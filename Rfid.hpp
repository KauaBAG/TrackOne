#pragma once

#include "TipoDeComunicacao.hpp"
#include <string>

class Rfid : public TipoDeComunicacao
{
private:
    float frequencia = -1;
    std::string tipo = "";
public:
    Rfid(float frequencia, std::string tipo) : TipoDeComunicacao(2)
    {
        setFrequencia(frequencia);
        setTipo(tipo);
    }
    std::string getString()
    {
        return "Comunicação RFID com de frequencia " + std::to_string(frequencia) + " do tipo " + tipo;
    }
    float getFrequencia() {return frequencia;}
    std::string getTipo() {return tipo;}

    void setFrequencia(float frequencia) {this->frequencia = frequencia;}
    void setTipo(std::string tipo) {this->tipo = tipo;}
};

