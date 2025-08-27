#pragma once
#include "Alerta.hpp"
#include <string>

class AlertaVelocidade : public Alerta {
private:
    float velocidadeExercida = -1;
    float velocidadeLimite = -1;
public:
    AlertaVelocidade(int subid, Data dataDeEmissao, std::string localizacao,
        float velocidadeExercida, float velocidadeLimite) 
        : Alerta(0, subid, dataDeEmissao, localizacao)
    {
        setVelocidadeLimite(velocidadeLimite);
        setVelocidadeExercida(velocidadeExercida);
    }
    std::string getString() 
    {
        return AlertaVelocidade::getString() + ", velocidade exercida: " + std::to_string(velocidadeExercida) +
        ", velocidade limite:" + std::to_string(velocidadeLimite);
    }

    float getVelocidadeExercida() {return velocidadeExercida;}
    float getVelocidadeLimite() {return velocidadeLimite;}

    void setVelocidadeExercida(float velocidadeExercida) 
    {
        if(velocidadeExercida < 0)
        {
            std::cerr<<"Atribuição de valor invalido de velocidade exercida bloqueada - valor: "<<
                velocidadeExercida<<std::endl;
        }
        else this->velocidadeExercida = velocidadeExercida;
    }
    void setVelocidadeLimite(float velocidadeLimite) 
    {

        if(velocidadeLimite < 0)
        {
            std::cerr<<"Atribuição de valor invalido de velocidade limite bloqueada - valor: "<<
                velocidadeLimite<<std::endl;
        }
        else this->velocidadeLimite = velocidadeLimite;
    }
};

