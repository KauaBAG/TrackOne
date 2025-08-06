#pragma once

#include <string>
#include "Rastreador.hpp"

class RastreadorCarga : public Rastreador
{
private:
    std::string tipo;
    std::string remetente;
    std::string destinatario;
    bool eFragil;
public:
    std::string getString();
    RastreadorCarga(int id, std::string marca, std::string modelo, TipoDeComunicacao* comunicacao,
        EstadoDoRastreador estado, Data ativacao, std::string tipo, std::string remetente, std::string destinatario, bool eFragil);
};