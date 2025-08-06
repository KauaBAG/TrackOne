#pragma once

#include <string> 
#include "Rastreador.hpp"

class RastreadorPessoal : public Rastreador
{
private:
    std::string nome;
    std::string telefone;
    std::string documento;

public:
    std::string getString();
    RastreadorPessoal(int id, std::string marca, std::string modelo, TipoDeComunicacao* comunicacao,
        EstadoDoRastreador estado, Data ativacao, std::string nome, std::string telefone, std::string documento);
};

