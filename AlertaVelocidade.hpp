#pragma once
#include "Alerta.hpp"
#include <string>

class AlertaVelocidade : public Alerta {
private:
    float velocidadeExercida;
    float velocidadeLimite;
public:
    AlertaVelocidade(int tipo, int subid, Data dataDeEmissao, std::string localizacao,
        float velocidadeExercida, float velocidadeLimite);
    std::string getString();
};

