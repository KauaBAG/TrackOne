#pragma once

#include "TipoDeComunicacao.hpp"

class Satelital : public TipoDeComunicacao
{
private:
    int id;
public:
    Satelital(int id) : TipoDeComunicacao(1){}
};

