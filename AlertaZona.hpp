#pragma once
#include "Alerta.hpp"
#include <string>

class AlertaZona : public Alerta 
{
private:
    bool inout;
    std::string zona;
public:
    AlertaZona(int tipo, int subid, Data dataDeEmissao, std::string localizacao, bool inout, std::string zona);
};

