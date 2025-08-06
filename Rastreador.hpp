#pragma once

#include <string> 
#include <vector>

#include "Data.hpp"
#include "Alerta.hpp"
#include "TipoDeComunicacao.hpp"

enum EstadoDoRastreador {ATIVO, INATIVO, MANUTENCAO, BLOQUEADO};

class Rastreador 
{
protected:
    int id;
    int tipo;
    std::string marca;
    std::string modelo;
    TipoDeComunicacao *comunicacao;
    Data ativacao;
    std::vector<Alerta> alertas;

    Rastreador(int id, int tipo, std::string marca, std::string modelo, TipoDeComunicacao* comunicacao,
        EstadoDoRastreador estado, Data ativacao);
public:
    virtual std::string getString();
};