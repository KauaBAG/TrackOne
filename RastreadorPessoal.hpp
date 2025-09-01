#pragma once

#include <string> 
#include "Rastreador.hpp"

class RastreadorPessoal : public Rastreador
{
private:
    std::string nome = "";
    std::string telefone = "";
    std::string documento = "";

public:
    std::string getString();
    std::string getStringSalvar();
    RastreadorPessoal(unsigned int id, std::string marca, std::string modelo, TipoDeComunicacao* comunicacao,
        EstadoDoRastreador estado, Data ativacao, std::string nome, std::string telefone, std::string documento);

    
    std::string getNome();
    std::string getTelefone();
    std::string getDocumento();

    void setNome(std::string nome);
    void setTelefone(std::string telefone);
    void setDocumento(std::string documento);
};

