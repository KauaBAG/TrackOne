#pragma once

#include "TipoDeComunicacao.hpp"
#include <string>

class Satelital : public TipoDeComunicacao
{
private:
    unsigned int id = -1;
public:
    Satelital(unsigned int id) : TipoDeComunicacao(1)
    {
        setId(id);
    }
    std::string getString()
    {
        return "Comunicação satelital com id " + std::to_string(id);
    }
    unsigned int getId(){return id;}
    void setId(unsigned int id){this->id = id;}
};

