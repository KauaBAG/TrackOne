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
        return (std::string)"Alerta de bateria: Violada - " + 
            (foiViolada?"sim":"nao") + " Descarregada - " + (foiDescarregada?"sim":"nao");
    }

    bool getFoiViolada() {return foiViolada;}
    bool getFoiDescarregada() {return foiDescarregada;}

    void setFoiViolada(bool foiViolada){this->foiViolada = foiViolada;};
    void setFoiDescarregada(bool foiDescarregada){this->foiDescarregada = foiDescarregada;};
    
};

