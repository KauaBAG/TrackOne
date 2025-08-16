#pragma once
#include "Alerta.hpp"
#include <string>

class AlertaZona : public Alerta 
{
private:
    bool inout;
    std::string zona;
public:
    AlertaZona(int tipo, int subid, Data dataDeEmissao, std::string localizacao, bool inout, std::string zona)
    : Alerta(0, subid, dataDeEmissao, localizacao)
    {
        setInout(inout);
        setZona(zona);
    } 

    std::string getString()
    {
        return Alerta::getString() + ", rastreador " + (inout?"entrou":"saiu") + " de " + zona;
    }

    bool getInout() {return inout;};
    std::string getZona() {return zona;};

    void setInout(bool inout) {this->inout = inout;}
    void setZona(std::string zona) {this->zona = zona;}

};

