#pragma once
#include "Alerta.hpp"
#include <string>

class AlertaBateria : public Alerta 
{
private:
    bool foiViolada;
    bool foiDescarregada;
public:
    AlertaBateria(int tipo, int subid, Data dataDeEmissao, std::string localizacao, 
        bool foiViolada, bool foiDescarregada);
    std::string getString();
};

