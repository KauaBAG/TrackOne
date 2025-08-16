#pragma once

#include <string>
#include "Rastreador.hpp"

class RastreadorCarga : public Rastreador
{
private:
    std::string tipoDeCarga = "";
    std::string remetente = "";
    std::string destinatario = "";
    bool eFragil = false;
public:
    std::string getString();
    RastreadorCarga(unsigned int id, std::string marca, std::string modelo, TipoDeComunicacao* comunicacao,
        EstadoDoRastreador estado, Data ativacao, std::string tipo, std::string remetente, std::string destinatario, bool eFragil);

    std::string getTipoDeCarga();
    std::string getRemetente();
    std::string getDestinatario();
    bool getEFragil();

    void setTipoDeCarga(std::string tipoDeCarga);
    void setRemetente(std::string remetente);
    void setDestinatario(std::string destinatario);
    void setEFragil(bool eFragil);
};