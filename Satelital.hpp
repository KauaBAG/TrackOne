#pragma once

#include "TipoDeComunicacao.hpp"
#include <string>

class Satelital : public TipoDeComunicacao
{
private:
    unsigned int id;
public:
    Satelital(int id) : TipoDeComunicacao(1)
    {
        setId(id);
    }
    std::string getString()
    {
        return "Comunicação satelital com id " + std::to_string(id);
    }
    int getId(){return id;}
    void setId(int id){this->id = id;}
};

