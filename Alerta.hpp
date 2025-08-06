#pragma once

#include <string>
#include "Data.hpp"

class Alerta 
{
protected:
    int tipo;
    int subid;
    Data dataDeEmissao;
    std::string localizacao;

    Alerta(int tipo, int subid, Data dataDeEmissao, std::string localizacao);
    virtual std::string getString();
};

