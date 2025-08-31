#pragma once
#include "Alerta.hpp"
#include <string>

class AlertaBateria : public Alerta 
{
private:
    bool foiViolada = false;
    bool foiDescarregada = false;
public:
    AlertaBateria(int subid, Data dataDeEmissao, std::string localizacao, 
        bool foiViolada, bool foiDescarregada) : Alerta(1,subid,dataDeEmissao,localizacao)
        {
            setFoiDescarregada(foiDescarregada);
            setFoiViolada(foiViolada);
        }
    std::string getString() 
    {
        return AlertaBateria::getString() + ",\n    Violada: " + 
            (foiViolada?"Sim":"Nao") + ",\n    Descarregada: " + (foiDescarregada?"Sim":"Nao");
    }

    bool getFoiViolada() {return foiViolada;}
    bool getFoiDescarregada() {return foiDescarregada;}

    void setFoiViolada(bool foiViolada){this->foiViolada = foiViolada;};
    void setFoiDescarregada(bool foiDescarregada){this->foiDescarregada = foiDescarregada;};
    
};

