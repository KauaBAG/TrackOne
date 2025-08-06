#pragma once

#include "TipoDeComunicacao.hpp"
#include <string>

class Rfid : public TipoDeComunicacao
{
private:
    float frequencia;
    std::string tipo;
public:
    Rfid(float frequencia, std::string tipo) : TipoDeComunicacao(2), frequencia(frequencia) {}
};

